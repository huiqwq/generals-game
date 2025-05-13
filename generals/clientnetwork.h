#ifndef CLIENTNETWORK_H
#define CLIENTNETWORK_H

#include <QTcpSocket>
#include <QObject>

class ClientNetwork : public QObject
{
    Q_OBJECT

public:
    explicit ClientNetwork(QObject *parent = nullptr);
    void connectToServer(const QString &address, quint16 port);
    void sendMoveCommand(int fromX, int fromY, int toX, int toY);

signals:
    void connected();
    void disconnected();
    void gameStateReceived(const QByteArray &data);

private slots:
    void onReadyRead();

private:
    QTcpSocket *m_socket;
};

#endif // CLIENTNETWORK_H
