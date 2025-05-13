#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "clientnetwork.h"
#include "mapbutton.h"


namespace Ui {
class gamewindow;
}


class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    enum Player { Player1, Player2, Neutral };
    enum Terrain { Plain, Mountain, Castle, King };

    struct GameTile {
        Terrain terrain;
        Player owner;
        int armyCount;
    };

public slots:
    void onConnected();
    void onDisconnected();
    void onGameStateUpdated(const QByteArray &data);

private slots:
    void onMapButtonClicked(int x, int y);

private:
    void initializeMap();
    void updateMapUI();
    void updateTileUI(int x, int y);
    void sendMoveCommand(int fromX, int fromY, int toX, int toY);

    Ui::gamewindow *ui;
    ClientNetwork *m_network;
    QVector<QVector<GameTile>> m_map;
    QVector<QVector<MapButton*>> m_mapButtons;
    Player m_player;
    bool m_isMyTurn = false;
    QPoint m_selectedTile;
};

#endif // GAMEWINDOW_H
