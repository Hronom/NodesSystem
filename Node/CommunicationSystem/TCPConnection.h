#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QTcpSocket>
#include <QFile>
#include "NetworkRequest.h"
#include "NetworkReply.h"

class TCPConnection : public QObject
{
    Q_OBJECT
private:
    QString mPeerAddress;
    quint16 mPeerPort;
    QTcpSocket *mTcpSocket;

    QList<NetworkRequest *> mRequestsList;
    NetworkReply *mReceivedReply;

public:
    //методы вызывающиеся из другого потока
    TCPConnection(QTcpSocket *xTcpSocket);
    TCPConnection(const QString &xPeerAddress, const quint16 &xPeerPort);
    TCPConnection(const TCPConnection &xOldTCPConnection, QTcpSocket *xTcpSocket);
    ~TCPConnection();

    Q_INVOKABLE void initialize();
    Q_INVOKABLE void sendMessage(const QString &xSenderUuid, const QString &xMessageType, Message *xMessage);

private slots:
    void connected();
    void readyRead();
    void readyWrite();

    void newMessageRecived_SLOT(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage);

    void socketStateChanged(QAbstractSocket::SocketState xSocketState);

signals:
    void newMessageRecived(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage);
};

#endif // TCPCONNECTION_H
