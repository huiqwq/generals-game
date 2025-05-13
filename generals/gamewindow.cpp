#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QMessageBox>
#include <QGridLayout>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gamewindow)
    , m_network(new ClientNetwork(this))
    , m_map(20, QVector<GameTile>(20))
{
    ui->setupUi(this);

    // 初始化网络连接
    connect(m_network, &ClientNetwork::connected, this, &GameWindow::onConnected);
    connect(m_network, &ClientNetwork::disconnected, this, &GameWindow::onDisconnected);
    connect(m_network, &ClientNetwork::gameStateReceived, this, &GameWindow::onGameStateUpdated);

    // 初始化地图UI
    initializeMap();

    // 连接服务器按钮
    QString Ip = "26.1.129.217";
    quint16 Port = 8010;
    m_network->connectToServer(Ip,Port);//直接进行连接，一个端口可以支持许多并发连接
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::initializeMap()
{
    QGridLayout *gridLayout = new QGridLayout(ui->mapWidget);
    gridLayout->setSpacing(1);
    gridLayout->setContentsMargins(0, 0, 0, 0);

    m_mapButtons.resize(20);
    for (int y = 0; y < 20; ++y) {
        m_mapButtons[y].resize(20);
        for (int x = 0; x < 20; ++x) {
            MapButton *button = new MapButton(x, y, this);
            button->setFixedSize(30, 30);
            gridLayout->addWidget(button, y, x);
            m_mapButtons[y][x] = button;

            connect(button, &MapButton::clickedWithPosition, this, &GameWindow::onMapButtonClicked);
        }
    }
}

void GameWindow::updateMapUI()
{
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            updateTileUI(x, y);
        }
    }
}

void GameWindow::updateTileUI(int x, int y)
{
    MapButton *button = m_mapButtons[y][x];
    const GameTile &tile = m_map[y][x];

    QString style;
    QString text = QString::number(tile.armyCount);
    QString currentImage;

    switch (tile.terrain) {
    case Mountain:
        style = "background-color: #555; color: white;";
        //text = "▲";
        break;
    case Castle:
        currentImage  = "C:\\Users\\HUiA1\\Desktop\\Generals-io-main\\img\\City.png";
        button->setButtonIcon(currentImage);
        //style = "background-color: #FFD700; color: black;";
        break;
    case Plain:
        switch (tile.owner) {
        case Player1: style = "background-color: #3498db; color: white;"; break;
        case Player2: style = "background-color: #e74c3c; color: white;"; break;
        case Neutral: style = "background-color: #f5f5f5; color: black;"; break;
        }
        break;
    case King:
        switch (tile.owner) {
        case Player1: style = "background-color: #3498db; color: white;"; break;
        case Player2: style = "background-color: #e74c3c; color: white;"; break;
        case Neutral: style = "background-color: #f5f5f5; color: black;"; break;
        }
        break;
    }

    button->setStyleSheet(QString(
                              "QPushButton { %1 border: 1px solid #999; font-weight: bold; }"
                              "QPushButton:hover { border: 2px solid black; }"
                              ).arg(style));

    if(tile.armyCount == 0){
        text = " ";
    }
    if(tile.terrain == Mountain){
        currentImage = "C:\\Users\\HUiA1\\Desktop\\Generals-io-main\\img\\Mountain.png";
        button->setButtonIcon(currentImage);
    }
    else if(tile.terrain == King){
        currentImage = "C:\\Users\\HUiA1\\Desktop\\Generals-io-main\\img\\General.png";
        button->setButtonIcon(currentImage);
    }
    else button->setText(text);
}

void GameWindow::onMapButtonClicked(int x, int y)
{
    if (!m_isMyTurn) return;

    if (m_selectedTile.isNull()) {
        // 选择起点
        if (m_map[y][x].owner == m_player && m_map[y][x].armyCount > 1) {
            m_selectedTile = QPoint(x, y);
            m_mapButtons[y][x]->setSelected(true);
        }
    } else {
        // 选择终点
        int fromX = m_selectedTile.x();
        int fromY = m_selectedTile.y();

        // 检查是否相邻
        if (abs(fromX - x) + abs(fromY - y) == 1) {
            sendMoveCommand(fromX, fromY, x, y);
        }

        // 重置选择
        m_mapButtons[fromY][fromX]->setSelected(false);
        m_selectedTile = QPoint();
    }
}

void GameWindow::sendMoveCommand(int fromX, int fromY, int toX, int toY)
{
    m_network->sendMoveCommand(fromX, fromY, toX, toY);
}

void GameWindow::onConnected()
{
    //ui->mapWidget->statusLabel->setText("已连接到服务器");
    qDebug()<<"已连接到服务器";
}

void GameWindow::onDisconnected()
{
   // ui->mapWidget->statusLabel->setText("与服务器断开连接");
    qDebug()<<"与服务器断开连接";
}

void GameWindow::onGameStateUpdated(const QByteArray &data)
{
    QDataStream stream(data);
    QString command;
    stream >> command;

    if (command == "INIT") {
        // 初始化游戏状态
        int player;
        stream >> player;
        m_player = static_cast<Player>(player);

        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                int terrain, owner;
                stream >> terrain >> owner >> m_map[y][x].armyCount;
                m_map[y][x].terrain = static_cast<Terrain>(terrain);
                m_map[y][x].owner = static_cast<Player>(owner);
            }
        }

        updateMapUI();
        m_isMyTurn = (m_player == Player1);

    } else if (command == "UPDATE") {
        // 更新游戏状态
        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                int terrain, owner;
                stream >> terrain >> owner >> m_map[y][x].armyCount;
                m_map[y][x].terrain = static_cast<Terrain>(terrain);
                m_map[y][x].owner = static_cast<Player>(owner);
            }
        }

        updateMapUI();
        m_isMyTurn = !m_isMyTurn; // 简单回合切换 回合切换的实现

    } else if (command == "GAMEOVER") {
        QString winner;
        stream >> winner;
        QMessageBox::information(this, "游戏结束", QString("游戏结束! 胜利者: %1").arg(winner));
    }
}
