#ifndef GROUPSCONTROLLER_H
#define GROUPSCONTROLLER_H

#include <QObject>
#include <QHash>
#include "Group.h"

class GroupsController : public QObject
{
    Q_OBJECT
private:
    QHash<QString, Group*> mGroupsList;

public:
    GroupsController(QObject *xParent);
    ~GroupsController();

    void addGroup(const QString &xGroupUuid, const Group &xGroup);
    void deleteGroup(const QString &xGroupUuid);
    Group getGroup(const QString &xGroupUuid);

    void setCurrentMember(const QString &xGroupUuid, const Member &xCurrentMember);
    Member getCurrentMember(const QString &xGroupUuid);
    void setOwnerMember(const QString &xGroupUuid, const Member &xOwnerMember);
    Member getOwnerMember(const QString &xGroupUuid);

    void addMember(const QString &xGroupUuid, const QString &xMemberUuid, const Member &xMember);
    void deleteMember(const QString &xGroupUuid, const QString &xMemberUuid);
    Member getMember(const QString &xGroupUuid, const QString &xMemberUuid);

signals:

public slots:

};

#endif // GROUPSCONTROLLER_H
