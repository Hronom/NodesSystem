#include "Group.h"

Group::Group(const Group &xCopyGroup)
{
    mGroupUuid = xCopyGroup.mGroupUuid;
    mGroupName = xCopyGroup.mGroupName;
    mPassword = xCopyGroup.mPassword;
    mVisible = xCopyGroup.mVisible;

    mCurrentMember.first = xCopyGroup.mCurrentMember.first;
    mCurrentMember.second = xCopyGroup.mCurrentMember.second;
    mOwnerMember.first = xCopyGroup.mOwnerMember.first;
    mOwnerMember.second = xCopyGroup.mOwnerMember.second;
    mMembersList = xCopyGroup.mMembersList;
}

Group::Group(const QString &xGroupUuid, const QString &xGroupName, const QString &xPassword, const bool &xVisible)
{
    mGroupUuid = xGroupUuid;
    mGroupName = xGroupName;
    mPassword = xPassword;
    mVisible = xVisible;
}

Group::~Group()
{
    mMembersList.clear();
}

QString Group::getGroupUuid()
{
    return mGroupUuid;
}

void Group::setGroupName(const QString &xGroupName)
{
    mGroupName = xGroupName;
}

QString Group::getGroupName()
{
    return mGroupName;
}

void Group::setPassword(const QString &xPassword)
{
    mPassword = xPassword;
}

QString Group::getPassword()
{
    return mPassword;
}

void Group::setVisible(const bool &xVisible)
{
    mVisible = xVisible;
}

bool Group::isVisible()
{
    return mVisible;
}

void Group::setCurrentMember(const QString &xMemberUuid, const Member &xMember)
{
    mCurrentMember.first = xMemberUuid;
    mCurrentMember.second = xMember;
}

Member Group::getCurrentMember()
{
    return mCurrentMember.second;
}

void Group::setOwnerMember(const QString &xMemberUuid, const Member &xMember)
{
    mOwnerMember.first = xMemberUuid;
    mOwnerMember.second = xMember;
}

Member Group::getOwnerMember()
{
    return mOwnerMember.second;
}

bool Group::isCurrentMemberOwner()
{
    if(mCurrentMember.first == mOwnerMember.first)
        return true;
    else
        return false;
}

void Group::addMember(const QString &xMemberUuid, const Member &xMember)
{
    mMembersList.insert(xMemberUuid, xMember);
}

void Group::deleteMember(const QString &xMemberUuid)
{
    mMembersList.remove(xMemberUuid);
}

Member Group::getMember(const QString &xMemberUuid)
{
    return mMembersList.value(xMemberUuid);
}
