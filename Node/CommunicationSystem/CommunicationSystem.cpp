#include "CommunicationSystem.h"
#include <QUuid>
#include <QNetworkInterface>
#include <QStringList>
#include <QDebug>

CommunicationSystem::CommunicationSystem()
{
    mGroupsController = new GroupsController(this);

    mNetworkController = new NetworkController(this);
    this->connect(mNetworkController,SIGNAL(newMessageRecived(QString,QString,Message*)),SLOT(newMessageRecived_SLOT(QString,QString,Message*)));
}

CommunicationSystem::~CommunicationSystem()
{
    if(mNetworkController != 0)
    {
        delete mNetworkController;
        mNetworkController = NULL;
    }

    if(mGroupsController != 0)
    {
        delete mGroupsController;
        mGroupsController = NULL;
    }
}

QStringList CommunicationSystem::getIPv4Addresses()
{
    QList<QHostAddress> xHostAddressList = QNetworkInterface::allAddresses();

    QStringList xAddressList;
    if(xHostAddressList.isEmpty() == false)
    {
        for(int i = 0; i < xHostAddressList.count(); i++)
        {
            if(xHostAddressList[i].protocol() == QAbstractSocket::IPv4Protocol)
                xAddressList.append(xHostAddressList[i].toString());
        }
    }

    return xAddressList;
}

void CommunicationSystem::initialize(const quint16 &xPort)
{
    mCurrentPort = xPort;
    mNetworkController->initialize(mCurrentPort);
}

void CommunicationSystem::loadGroup(const QString &xGroupUuid, const Group &xGroup)
{
    mGroupsController->addGroup(xGroupUuid, xGroup);
}

void CommunicationSystem::createGroup(const QString &xHostIP, const QString &xGroupName, const QString &xPassword, const bool &xVisible, const QString &xNameInGroup)
{
    QString xGroupUuid = QUuid::createUuid().toString();
    Group xGroup = Group(xGroupUuid, xGroupName, xPassword, xVisible);

    QString xCurrentMemberUuid = QUuid::createUuid().toString();
    Member xCurrentMember = Member(xCurrentMemberUuid, xNameInGroup, xHostIP, mCurrentPort);

    xGroup.setCurrentMember(xCurrentMemberUuid, xCurrentMember);
    xGroup.setOwnerMember(xCurrentMemberUuid, xCurrentMember);

    mGroupsController->addGroup(xGroupUuid, xGroup);
}

void CommunicationSystem::leaveGroup(const QString &xGroupUuid)
{
    mGroupsController->deleteGroup(xGroupUuid);
}

void CommunicationSystem::kickMember(const QString &xGroupUuid, const QString &xMemberUuid)
{
    mGroupsController->deleteMember(xGroupUuid, xMemberUuid);
}

void CommunicationSystem::joinGroup(const QString &xAddress, const quint16 &xPort, const QString &xGroupUuid, const QString &xPassword, const QString &xNameInGroup)
{

}

void CommunicationSystem::sendMessage(const QString &xMessageType, Message *xMessage)
{
    //Member xMember = mGroupsController->getCurrentMember(xMessage->getGroupUuid());
    //mNetworkController->sendMessage(xMember.getAddress(), xMember.getPort(), xMember.getMemberUuid(), "plugin", xMessage);
    mNetworkController->sendMessage("192.168.2.1", 9050, "lol", "plugin", xMessage);
}

 void CommunicationSystem::newMessageRecived_SLOT(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage)
 {
     qDebug()<<xReceiverUuid<<xMessageType<<xMessage;
 }
