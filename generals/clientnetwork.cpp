#include "clientnetwork.h"
#include <QDataStream>

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    connect(m_socket, &QTcpSocket::connected, this, &ClientNetwork::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientNetwork::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientNetwork::onReadyRead);
}

void ClientNetwork::connectToServer(const QString &address, quint16 port)
{
    m_socket->connectToHost(address, port);
}

void ClientNetwork::sendMoveCommand(int fromX, int fromY, int toX, int toY)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << QString("MOVE") << fromX << fromY << toX << toY;
    m_socket->write(data);
}

void ClientNetwork::onReadyRead()
{
    while (m_socket->bytesAvailable() > 0) {
        QByteArray data = m_socket->readAll();
        emit gameStateReceived(data);
    }
}
