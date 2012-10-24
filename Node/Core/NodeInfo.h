#ifndef NODEINFO_H
#define NODEINFO_H

#include <QString>

struct NodeInfo
{
    QString ConnectionUuid;
    bool ConnectionStatus;
    QString Name;
    QString IPAddress;
    quint16 Port;
};

#endif // NODEINFO_H
