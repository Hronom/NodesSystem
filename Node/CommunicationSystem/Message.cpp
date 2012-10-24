#include "Message.h"

Message::Message(QObject *xParent): QObject(xParent)
{
    mGroupUuid = "";
    mMemberUuid = "";
    mPluginName = "";
    mMessage = "";
    mFilePath = "";
}

Message::Message(const Message &xOther)
{
}

Message::Message(const QString &xGroupUuid, const QString &xMemberUuid, const QString &xPluginName, const QString &xMessage) : QObject(0)
{
    mGroupUuid = xGroupUuid;
    mMemberUuid = xMemberUuid;
    mPluginName = xPluginName;
    mMessage = xMessage;
    mFilePath = "";
}

Message::Message(const QString &xGroupUuid, const QString &xMemberUuid, const QString &xPluginName, const QString &xMessage, const QString &xFilePath) : QObject(0)
{
    mGroupUuid = xGroupUuid;
    mMemberUuid = xMemberUuid;
    mPluginName = xPluginName;
    mMessage = xMessage;
    mFilePath = xFilePath;
}

QString Message::getGroupUuid()
{
    return mGroupUuid;
}

QString Message::getMemberUuid()
{
    return mMemberUuid;
}

QString Message::getPluginName()
{
    return mPluginName;
}

QString Message::getMessage()
{
    return mMessage;
}

QString Message::getFilePath()
{
    return mFilePath;
}

