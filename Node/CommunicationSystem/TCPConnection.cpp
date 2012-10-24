#include "TCPConnection.h"
#include <QHostAddress>
#include <QDir>
#include <QHostInfo>
#include <QDebug>

TCPConnection::TCPConnection(QTcpSocket *xTcpSocket)
{
    mPeerAddress = xTcpSocket->peerAddress().toString();
    mPeerPort = xTcpSocket->peerPort();

    mTcpSocket = xTcpSocket;
    mTcpSocket->setParent(this);//назначаем нового родителя)
}

TCPConnection::TCPConnection(const QString &xPeerAddress, const quint16 &xPeerPort)
{
    mPeerAddress = xPeerAddress;
    mPeerPort = xPeerPort;

    mTcpSocket = new QTcpSocket(this);
}

TCPConnection::TCPConnection(const TCPConnection &xOldTCPConnection, QTcpSocket *xTcpSocket)
{
    mPeerAddress = xTcpSocket->peerAddress().toString();
    mPeerPort = xTcpSocket->peerPort();

    mTcpSocket = xTcpSocket;
    mTcpSocket->setParent(this);//назначаем нового родителя)
}

TCPConnection::~TCPConnection()
{
    if(mTcpSocket != NULL)
    {
        delete mTcpSocket;
        mTcpSocket = NULL;
    }
}

void TCPConnection::initialize()
{
    this->connect(mTcpSocket, SIGNAL(connected()), SLOT(connected()));
    this->connect(mTcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    this->connect(mTcpSocket, SIGNAL(readyRead()), SLOT(readyRead()));
    this->connect(mTcpSocket, SIGNAL(bytesWritten(qint64)), SLOT(readyWrite()));
}

void TCPConnection::sendMessage(const QString &xSenderUuid, const QString &xMessageType, Message *xMessage)
{
    NetworkRequest *xNewNetworkRequest = new NetworkRequest(xSenderUuid, xMessageType, xMessage);
    mRequestsList.push_back(xNewNetworkRequest);

    if(mTcpSocket->state() != QAbstractSocket::ConnectedState)
        mTcpSocket->connectToHost(QHostAddress(mPeerAddress),mPeerPort);
    else
        if(mTcpSocket->state() == QAbstractSocket::ConnectedState && mTcpSocket->isWritable() == true)
            mTcpSocket->write(mRequestsList.first()->getBytesToSend(1500));
}

void TCPConnection::connected()
{
    readyWrite();
}

void TCPConnection::readyRead()
{
    qDebug()<<"readyRead";
    if(mReceivedReply == 0)
    {
        mReceivedReply = new NetworkReply();
        this->connect(mReceivedReply,SIGNAL(newMessageRecived(QString,QString,Message*)),SLOT(newMessageRecived_SLOT(QString,QString,Message*)));
        mReceivedReply->addReceivedBytes(mTcpSocket->readAll());
    }
    else
        mReceivedReply->addReceivedBytes(mTcpSocket->readAll());
}

void TCPConnection::readyWrite()
{
     qDebug()<<"readyWrite";
    if(mRequestsList.count() > 0)
    {
        if(mRequestsList.first()->isTransferComplete() == false)
            mTcpSocket->write(mRequestsList.first()->getBytesToSend(1500));
        else
            delete mRequestsList.takeFirst();
    }
}

void TCPConnection::newMessageRecived_SLOT(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage)
{
    emit this->newMessageRecived(xReceiverUuid, xMessageType, xMessage);

    delete mReceivedReply;
    mReceivedReply = 0;
}

void TCPConnection::socketStateChanged(QAbstractSocket::SocketState xSocketState)
{
    if(xSocketState == QAbstractSocket::UnconnectedState)
    {
        mRequestsList.last()->abortTransfer();
        delete mRequestsList.last();
    }

    if(xSocketState == QAbstractSocket::ConnectedState)
    {
        if(mRequestsList.count() > 0)
            mTcpSocket->write(mRequestsList.last()->getBytesToSend(1500));
    }
}
