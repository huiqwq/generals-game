#ifndef GENERALSSERVER_H
#define GENERALSSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QMap>
#include <QTimer>
#include <QQueue>
#include <QTime>
#include <QRandomGenerator>

class GeneralsServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit GeneralsServer(QObject *parent = nullptr);
    ~GeneralsServer();

    bool startServer(quint16 port);
    void generateRandomMap();

    enum TerrainType {
        Plain,      // 普通地形
        Mountain,   // 山脉(障碍)
        Castle      // 城堡
    };

    enum PlayerType {
        Player1,
        Player2,
        Neutral
    };

    struct GameTile {
        TerrainType terrain;
        PlayerType owner;
        int armyCount;
    };

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onClientDisconnected();
    void processClientData();
    void gameTick();

private:
    void sendInitialGameState(QTcpSocket *client, PlayerType player);
    void broadcastGameState();
    bool isMapValid();
    bool canReachAllCastles(int startX, int startY);
    void floodFill(int x, int y, QSet<QPair<int, int>> &visited);
    void processMoveCommand(QTcpSocket *sender, const QByteArray &data);

    QMap<QTcpSocket*, PlayerType> m_clients;
    QTimer *m_gameTimer;
    GameTile m_map[20][20];
    QQueue<QPair<QPair<int, int>, QPair<int,int>>> m_moveQueue;
    bool m_gameStarted;
    int m_tickCounter;
};

#endif // GENERALSSERVER_H
