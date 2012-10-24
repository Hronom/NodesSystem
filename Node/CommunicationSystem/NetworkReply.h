#ifndef NETWORKREPLY_H
#define NETWORKREPLY_H

#include <QObject>
#include <QTemporaryFile>
#include <QBuffer>

#include "Message.h"

class NetworkReply : public QObject
{
    Q_OBJECT
private:
    int mCurrentState;

    QString mReceiverUuid;
    QString mMessageType;
    Message *mMessage;

    QByteArray mBuffer;
    qint64 mBlockSize;
    QTemporaryFile mTemporaryFile;

    qint64 mBytesReceived;
    qint64 mBytesTotal;
public:
    NetworkReply();

    void addReceivedBytes(const QByteArray &xByteArray);

signals:
    void newMessageRecived(const QString &xReceiverUuid, const QString &xMessageType, Message *xMessage);
};

#endif // NETWORKREPLY_H
