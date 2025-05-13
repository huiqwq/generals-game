#include "GeneralsServer.h"
#include <QDebug>

GeneralsServer::GeneralsServer(QObject *parent) : QTcpServer(parent),
    m_gameStarted(false), m_tickCounter(0)
{
    m_gameTimer = new QTimer(this);
    connect(m_gameTimer, &QTimer::timeout, this, &GeneralsServer::gameTick);
    m_gameTimer->setInterval(1000); // 1秒的游戏tick
}

GeneralsServer::~GeneralsServer()
{
    if (m_gameTimer->isActive()) {
        m_gameTimer->stop();
    }
}

bool GeneralsServer::startServer(quint16 port)
{
    if (!listen(QHostAddress::Any, port)) {
        qWarning() << "Server could not start:" << errorString();
        return false;
    }

    qDebug() << "Server started on port" << port;
    generateRandomMap();
    return true;
}

void GeneralsServer::generateRandomMap()
{
    QRandomGenerator rand(QTime::currentTime().msec());

    // 初始化所有地块为普通地形
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            m_map[y][x] = {Plain, Neutral, 0};
        }
    }

    // 放置60个山脉(障碍)
    int mountainsPlaced = 0;
    while (mountainsPlaced < 60) {
        int x = rand.bounded(20);
        int y = rand.bounded(20);

        if (m_map[y][x].terrain == Plain) {
            m_map[y][x].terrain = Mountain;
            mountainsPlaced++;
        }
    }

    // 放置15个城堡
    int castlesPlaced = 0;
    while (castlesPlaced < 15) {
        int x = rand.bounded(20);
        int y = rand.bounded(20);

        if (m_map[y][x].terrain == Plain) {
            m_map[y][x].terrain = Castle;
            m_map[y][x].armyCount = 10; // 城堡初始兵力
            castlesPlaced++;
        }
    }

    // 为玩家1和玩家2设置起始位置
    bool validStartPositions = false;
    int attempts = 0;
    const int maxAttempts = 100;

    while (!validStartPositions && attempts < maxAttempts) {
        attempts++;

        // 随机选择玩家1位置
        int p1x = rand.bounded(20);
        int p1y = rand.bounded(20);

        if (m_map[p1y][p1x].terrain != Plain) continue;

        // 确保玩家2位置与玩家1有一定距离
        int p2x, p2y;
        bool foundP2 = false;

        for (int i = 0; i < 20; ++i) {
            p2x = rand.bounded(20);
            p2y = rand.bounded(20);

            // 确保至少10格距离
            if (m_map[p2y][p2x].terrain == Plain &&
                qAbs(p1x - p2x) + qAbs(p1y - p2y) >= 10) {
                foundP2 = true;
                break;
            }
        }

        if (!foundP2) continue;

        // 设置玩家领地
        m_map[p1y][p1x] = {Plain, Player1, 1};
        m_map[p2y][p2x] = {Plain, Player2, 1};

        // 验证地图有效性
        if (isMapValid()) {
            validStartPositions = true;
            qDebug() << "Valid map generated after" << attempts << "attempts";
            qDebug() << "Player 1 start:" << p1x << p1y;
            qDebug() << "Player 2 start:" << p2x << p2y;
        } else {
            // 重置玩家位置
            m_map[p1y][p1x] = {Plain, Neutral, 0};
            m_map[p2y][p2x] = {Plain, Neutral, 0};
        }
    }

    if (!validStartPositions) {
        qWarning() << "Failed to generate valid map after" << maxAttempts << "attempts";
        // 可以在这里实现后备方案，如使用固定地图
    }
}

bool GeneralsServer::isMapValid()
{
    // 找到玩家1和玩家2的位置
    QPair<int, int> p1Pos(-1, -1), p2Pos(-1, -1);

    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            if (m_map[y][x].owner == Player1) p1Pos = qMakePair(x, y);
            if (m_map[y][x].owner == Player2) p2Pos = qMakePair(x, y);
        }
    }

    if (p1Pos.first == -1 || p2Pos.first == -1) return false;

    // 检查玩家1能否到达所有城堡
    if (!canReachAllCastles(p1Pos.first, p1Pos.second)) return false;

    // 检查玩家2能否到达所有城堡
    if (!canReachAllCastles(p2Pos.first, p2Pos.second)) return false;

    return true;
}

bool GeneralsServer::canReachAllCastles(int startX, int startY)
{
    QSet<QPair<int, int>> visited;
    floodFill(startX, startY, visited);

    // 检查所有城堡是否都被访问过
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            if (m_map[y][x].terrain == Castle && !visited.contains(qMakePair(x, y))) {
                return false;
            }
        }
    }

    return true;
}

void GeneralsServer::floodFill(int x, int y, QSet<QPair<int, int>> &visited)
{
    if (x < 0 || x >= 20 || y < 0 || y >= 20) return;
    if (visited.contains(qMakePair(x, y))) return;
    if (m_map[y][x].terrain == Mountain) return;

    visited.insert(qMakePair(x, y));

    // 4方向填充
    floodFill(x+1, y, visited);
    floodFill(x-1, y, visited);
    floodFill(x, y+1, visited);
    floodFill(x, y-1, visited);
}

void GeneralsServer::incomingConnection(qintptr socketDescriptor)
{
    if (m_clients.size() >= 2) {
        qDebug() << "Refusing connection - already 2 players";
        QTcpSocket *socket = new QTcpSocket(this);
        socket->setSocketDescriptor(socketDescriptor);
        socket->write("Server is full\n");
        socket->disconnectFromHost();
        return;
    }

    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketDescriptor);

    connect(client, &QTcpSocket::disconnected, this, &GeneralsServer::onClientDisconnected);
    connect(client, &QTcpSocket::readyRead, this, &GeneralsServer::processClientData);

    // 分配玩家
    PlayerType player = m_clients.isEmpty() ? Player1 : Player2;
    m_clients.insert(client, player);

    qDebug() << "Player" << (player == Player1 ? "1" : "2") << "connected";

    // 发送初始游戏状态
    sendInitialGameState(client, player);

    // 如果两个玩家都连接了，开始游戏
    if (m_clients.size() == 2 && !m_gameStarted) {
        m_gameStarted = true;
        m_gameTimer->start();
        qDebug() << "Game started!";
    }
}

void GeneralsServer::onClientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    qDebug() << "Player" << (m_clients[client] == Player1 ? "1" : "2") << "disconnected";
    m_clients.remove(client);
    client->deleteLater();

    // 如果有玩家断开，结束游戏
    if (m_gameStarted) {
        m_gameTimer->stop();
        m_gameStarted = false;

        // 通知另一个玩家
        QTcpSocket *remainingPlayer = m_clients.isEmpty() ? nullptr : m_clients.firstKey();
        if (remainingPlayer) {
            remainingPlayer->write("Opponent disconnected\n");
        }
    }
}

void GeneralsServer::sendInitialGameState(QTcpSocket *client, PlayerType player)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << QString("INIT");
    stream << (player == Player1 ? 1 : 2);

    // 发送地图数据
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            stream << static_cast<int>(m_map[y][x].terrain);
            stream << static_cast<int>(m_map[y][x].owner);
            stream << m_map[y][x].armyCount;
        }
    }

    client->write(data);
}

void GeneralsServer::broadcastGameState()
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);//一个只能写入数据的流

    stream << QString("UPDATE");
    stream << m_tickCounter;

    // 发送地图数据
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            stream << static_cast<int>(m_map[y][x].terrain);
            stream << static_cast<int>(m_map[y][x].owner);
            stream << m_map[y][x].armyCount;
        }
    }

    // 广播给所有客户端
    for (QTcpSocket *client : m_clients.keys()) {
        client->write(data);
    }
}

void GeneralsServer::processClientData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client || !m_clients.contains(client)) return;

    while (client->bytesAvailable() > 0) {
        QByteArray data = client->readAll();

        // 简单的命令处理
        if (data.startsWith("MOVE")) {
            processMoveCommand(client, data);//没有处理分包粘包问题
        }
    }
}

void GeneralsServer::processMoveCommand(QTcpSocket *sender, const QByteArray &data)
{
    QDataStream stream(data);
    QString command;
    int fromX, fromY, toX, toY;

    stream >> command >> fromX >> fromY >> toX >> toY;

    // 验证移动是否合法
    if (fromX < 0 || fromX >= 20 || fromY < 0 || fromY >= 20 ||
        toX < 0 || toX >= 20 || toY < 0 || toY >= 20) {
        return;
    }

    PlayerType player = m_clients[sender];//map<Tcp,player>

    // 检查起始位置是否属于该玩家
    if (m_map[fromY][fromX].owner != player || m_map[fromY][fromX].armyCount <= 1) {
        return;
    }

    // 检查目标位置是否可移动
    if (m_map[toY][toX].terrain == Mountain) {
        return;
    }

    // 检查是否相邻
    if (qAbs(fromX - toX) + qAbs(fromY - toY) != 1) {
        return;
    }

    // 将移动命令加入队列，在游戏tick时处理
    m_moveQueue.enqueue(QPair(QPair(fromX,fromY),QPair(toX,toY)));
                      //QPair<QPair<QPair<fromX,fromY>,QPair<toX,toY>>,Player>
}

void GeneralsServer::gameTick()
{
    m_tickCounter++;

    // 处理所有移动命令
    while (!m_moveQueue.isEmpty()) {//考虑是否进行交替操作（？优点比较好写，缺点游戏进程慢
        auto move = m_moveQueue.dequeue();
        auto from = move.first;
        auto to = move.second;

        int fromX = from.first;
        int fromY = from.second;
        int toX = to.first;
        int toY = to.second;

        PlayerType attacker = m_map[fromY][fromX].owner;
        int attackingArmy = m_map[fromY][fromX].armyCount - 1; // 留1个在原地

        // 更新起始位置
        m_map[fromY][fromX].armyCount = 1;

        // 处理目标位置
        if (m_map[toY][toX].owner == attacker) {
            // 友方领地，增加兵力
            m_map[toY][toX].armyCount += attackingArmy;
        } else {
            // 敌方或中立领地，战斗
            if (m_map[toY][toX].armyCount < attackingArmy) {
                // 攻击者获胜
                m_map[toY][toX].owner = attacker;
                m_map[toY][toX].armyCount = attackingArmy - m_map[toY][toX].armyCount;
            } else {
                // 防御者获胜
                m_map[toY][toX].armyCount -= attackingArmy;
            }
        }
    }

    // 增加玩家兵力
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            if (m_map[y][x].owner != Neutral && m_map[y][x].terrain != Mountain) {
                m_map[y][x].armyCount++;

                // 城堡产生更多兵力
                if (m_map[y][x].terrain == Castle) {
                    m_map[y][x].armyCount++; // 城堡每回合+2
                }
            }
        }
    }

    // 广播游戏状态更新
    broadcastGameState();

    // 检查游戏结束条件
    bool p1Alive = false, p2Alive = false;
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            if (m_map[y][x].owner == Player1) p1Alive = true;
            if (m_map[y][x].owner == Player2) p2Alive = true;
        }
    }

    if (!p1Alive || !p2Alive) {
        m_gameTimer->stop();
        QString winner = !p1Alive ? "Player 2" : "Player 1";
        qDebug() << "Game over! Winner:" << winner;

        // 通知客户端
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << QString("GAMEOVER") << winner;

        for (QTcpSocket *client : m_clients.keys()) {
            client->write(data);
        }
    }
}
