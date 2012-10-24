#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QHash>
#include <QPair>
#include "Member.h"

class Group
{
private:
    QString mGroupUuid;
    QString mGroupName;
    QString mPassword;
    bool mVisible;

    QPair<QString, Member> mCurrentMember;
    QPair<QString, Member> mOwnerMember;
    QHash<QString, Member> mMembersList;

public:
    Group(const Group &xCopyGroup);
    Group(const QString &xGroupUuid, const QString &xGroupName, const QString &xPassword, const bool &xVisible);
    ~Group();

    QString getGroupUuid();
    void setGroupName(const QString &xGroupName);
    QString getGroupName();
    void setPassword(const QString &xPassword);
    QString getPassword();
    void setVisible(const bool &xVisible);
    bool isVisible();

    void setCurrentMember(const QString &xMemberUuid, const Member &xMember);
    Member getCurrentMember();
    void setOwnerMember(const QString &xMemberUuid, const Member &xMember);
    Member getOwnerMember();
    bool isCurrentMemberOwner();

    void addMember(const QString &xMemberUuid, const Member &xMember);
    void deleteMember(const QString &xMemberUuid);
    Member getMember(const QString &xMemberUuid);
};

#endif // GROUP_H
