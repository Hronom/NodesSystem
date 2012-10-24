#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QObject>
#include <QThread>

#include "TCPServer.h"
#include "TCPConnection.h"

class NetworkController: public QObject
{
    Q_OBJECT
private:
    QThread *mTCPServerThread;
    TCPServer *mTCPServer;

    QThread *mTCPConnThread;
    QHash<QString, TCPConnection*> mTCPConnList;
    QList<TCPConnection*> mUnknownTCPConnList;

public:
    NetworkController(QObject *xParent);
    ~NetworkController();

    void initialize(quint16 xBindPort);
    void sendMessage(const QString &xPeerAddress, const quint16 &xPeerPort, const QString &xSenderUuid, const QString &xMessageType, Message *xMessage);

    void setBindPort(quint16 xBindPort);

private slots:
    void newIncomingConnection(QTcpSocket *xTcpSocket);
    void newMessageRecived_SLOT(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage);

signals:
    void TCPBindStateChanged(bool xBindState);//������ ���������� ��������� ������������� TCP �����
    void newMessageRecived(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage);
};

#endif // NETWORKCONTROLLER_H
