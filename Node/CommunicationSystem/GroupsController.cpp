#include "GroupsController.h"

GroupsController::GroupsController(QObject *xParent) : QObject(xParent)
{

}

GroupsController::~GroupsController()
{
    QHashIterator<QString, Group*> xGroupsIterator(mGroupsList);
    while(xGroupsIterator.hasNext())
    {
        xGroupsIterator.next();
        delete xGroupsIterator.value();
    }
}

void GroupsController::addGroup(const QString &xGroupUuid, const Group &xGroup)
{
    Group *xNewGroup;
    xNewGroup = new Group(xGroup);
    mGroupsList.insert(xGroupUuid, xNewGroup);
}

void GroupsController::deleteGroup(const QString &xGroupUuid)
{
    Group *xGroup;
    xGroup = mGroupsList.take(xGroupUuid);
    delete xGroup;
}

Group GroupsController::getGroup(const QString &xGroupUuid)
{
    Group xGroup = *mGroupsList.value(xGroupUuid);
    return xGroup;
}

void GroupsController::setCurrentMember(const QString &xGroupUuid, const Member &xCurrentMember)
{
    Group *xGroup;
    xGroup = mGroupsList.value(xGroupUuid);
    xGroup->setCurrentMember(xGroupUuid, xCurrentMember);
}

Member GroupsController::getCurrentMember(const QString &xGroupUuid)
{
    Group *xGroup;
    xGroup = mGroupsList.value(xGroupUuid);
    return xGroup->getCurrentMember();
}

void GroupsController::setOwnerMember(const QString &xGroupUuid, const Member &xOwnerMember)
{
    Group *xGroup;
    xGroup = mGroupsList.value(xGroupUuid);
    xGroup->setOwnerMember(xGroupUuid, xOwnerMember);
}

Member GroupsController::getOwnerMember(const QString &xGroupUuid)
{
    Group *xGroup;
    xGroup = mGroupsList.value(xGroupUuid);
    return xGroup->getOwnerMember();
}

void GroupsController::addMember(const QString &xGroupUuid, const QString &xMemberUuid, const Member &xMember)
{
    Group *xGroup;
    xGroup = mGroupsList.value(xGroupUuid);
    xGroup->addMember(xMemberUuid, xMember);
}

void GroupsController::deleteMember(const QString &xGroupUuid, const QString &xMemberUuid)
{
    Group *xGroup;
    xGroup = mGroupsList.value(xGroupUuid);
    xGroup->deleteMember(xMemberUuid);
}

Member GroupsController::getMember(const QString &xGroupUuid, const QString &xMemberUuid)
{
    Group *xGroup;
    xGroup = mGroupsList.value(xGroupUuid);
    return xGroup->getMember(xMemberUuid);
}
