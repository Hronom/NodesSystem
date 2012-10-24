#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class NetworkReply;
class NetworkRequest;

class Message : public QObject
{
    Q_OBJECT
private:
    QString mGroupUuid;
    QString mMemberUuid;
    QString mPluginName;
    QString mMessage;
    QString mFilePath;

public:
    Message(QObject *xParent = 0);
    Message(const Message &xOther);
    Message(const QString &xGroupUuid, const QString &xMemberUuid, const QString &xPluginName, const QString &xMessage);
    Message(const QString &xGroupUuid, const QString &xMemberUuid, const QString &xPluginName, const QString &xMessage, const QString &xFilePath);

    QString getGroupUuid();
    QString getMemberUuid();
    QString getPluginName();
    QString getMessage();
    QString getFilePath();

signals:
    void transferAborted();
    void downloadProgress(qint64 xBytesReceived, qint64 xBytesTotal);
    void uploadProgress(qint64 xBytesSent, qint64 xBytesTotal);

    friend class NetworkReply;
    friend class NetworkRequest;
};

#endif // MESSAGE_H
