#ifndef MEMBER_H
#define MEMBER_H

#include <QObject>

class Member
{
private:
    QString mMemberUuid;
    QString mMemberName;
    QString mAddress;
    quint16 mPort;

public:
    Member();
    Member(const Member &xCopyMember);
    Member(const QString &xMemberUuid, const QString &xMemberName, const QString &xAddress, const quint16 &xPort);

    QString getMemberUuid();
    QString getMemberName();
    QString getAddress();
    quint16 getPort();
};

#endif // MEMBER_H
