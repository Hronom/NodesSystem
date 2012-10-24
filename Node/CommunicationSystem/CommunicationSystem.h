#ifndef COMMUNICATIONSYSTEM_H
#define COMMUNICATIONSYSTEM_H

#include <QObject>

#include "GroupsController.h"
#include "NetworkController.h"
#include "Message.h"

class CommunicationSystem : public QObject
{
    Q_OBJECT
private:
    quint16 mCurrentPort;

    GroupsController *mGroupsController;
    NetworkController *mNetworkController;

public:
    CommunicationSystem();
    ~CommunicationSystem();

    QStringList getIPv4Addresses();
    void initialize(const quint16 &xPort);

    void loadGroup(const QString &xGroupUuid, const Group &xGroup);

    void createGroup(const QString &xHostIP, const QString &xGroupName, const QString &xPassword, const bool &xVisible, const QString &xNameInGroup);
    void leaveGroup(const QString &xGroupUuid);
    void kickMember(const QString &xGroupUuid, const QString &xMemberUuid);
    void joinGroup(const QString &xAddress, const quint16 &xPort, const QString &xGroupUuid, const QString &xPassword, const QString &xNameInGroup);

    void sendMessage(const QString &xMessageType, Message *xMessage);

signals:
    void groupCreated(QString xGroupUuid, QString xGroupName, QString xPassword, bool xVisible);
    void groupEntered(QString xGroupUuid, QString xGroupName);
    void groupLeaved(QString xGroupUuid);
    void memberJoined(QString xMemberUuid);
    void memberKicked(QString xMemberUuid);
    void memberInfoUpdated(QString xMemberUuid, QString xMemberName, QString xAddress, quint16 xPort);
    void memberStatusUpdated(QString xMemberUuid, bool xStatus);

    void messageRecived(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage);

private slots:
    void newMessageRecived_SLOT(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage);
};

#endif // COMMUNICATIONSYSTEM_H
