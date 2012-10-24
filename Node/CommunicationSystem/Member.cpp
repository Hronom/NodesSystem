#include "Member.h"

Member::Member()
{
}

Member::Member(const Member &xCopyMember)
{
    mMemberUuid = xCopyMember.mMemberUuid;
    mMemberName = xCopyMember.mMemberName;
    mAddress = xCopyMember.mAddress;
    mPort = xCopyMember.mPort;
}

Member::Member(const QString &xMemberUuid, const QString &xMemberName, const QString &xAddress, const quint16 &xPort)
{
    mMemberUuid = xMemberUuid;
    mMemberName = xMemberName;
    mAddress = xAddress;
    mPort = xPort;
}

QString Member::getMemberUuid()
{
    return mMemberUuid;
}

QString Member::getMemberName()
{
    return mMemberName;
}

QString Member::getAddress()
{
    return mAddress;
}

quint16 Member::getPort()
{
    return mPort;
}
