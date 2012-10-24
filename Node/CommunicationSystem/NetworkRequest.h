#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include <QObject>
#include <QFile>
#include <QBuffer>

#include "Message.h"

class NetworkRequest : public QObject
{
    Q_OBJECT
private:
    int mCurrentState;

    Message *mMessage;

    QBuffer mBuffer;
    QFile mFile;

    qint64 mBytesSent;
    qint64 mBytesTotal;
public:
    NetworkRequest();
    NetworkRequest(const QString &xSenderUuid, const QString &xMessageType, Message *xMessage);

    QByteArray getBytesToSend(qint64 xMaxSize);

    bool isTransferComplete();
    void abortTransfer();
};

#endif // NETWORKREQUEST_H
