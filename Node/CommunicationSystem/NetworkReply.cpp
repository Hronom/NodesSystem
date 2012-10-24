#include "NetworkReply.h"
#include <QDir>

NetworkReply::NetworkReply()
{
    mMessage = new Message();
    mCurrentState = 0;

    mBytesReceived = 0;
    mBytesTotal = 0;

    mTemporaryFile.setAutoRemove(false);
}

/*
--- PackageInfo ---
PackageSize

--- Header ---
Size
GroupUuid
SenderUuid
ReceiverUuid
PluginName
MessageType

--- MessageText ---
Size
Message

--- FileInfo ---
Size
FileName
FileSize
*/

void NetworkReply::addReceivedBytes(const QByteArray &xByteArray)
{
    mBytesReceived += xByteArray.size();
    mBuffer.append(xByteArray);

    //-1-PackageInfo
    if(mCurrentState == 0)
    {
        if(((qint64)mBuffer.size()) >= sizeof(qint64))
        {
            QDataStream xPackageInfoStream(&mBuffer, QIODevice::ReadOnly);
            xPackageInfoStream >> mBytesTotal;
            mBuffer.remove(0, sizeof(qint64));
            mCurrentState = 1;
        }
    }
    //-1-

    //-2-Header
    if(mCurrentState == 1)
    {
        if(((qint64)mBuffer.size()) >= sizeof(qint64))
        {
            QDataStream xPackageInfoStream(&mBuffer, QIODevice::ReadOnly);
            xPackageInfoStream >> mBlockSize;
            mBuffer.remove(0, sizeof(qint64));
            mCurrentState = 2;
        }
    }

    if(mCurrentState == 2)
    {
        if(((qint64)mBuffer.size()) >= mBlockSize)
        {
            QDataStream xHeaderStream(&mBuffer, QIODevice::ReadOnly);
            xHeaderStream >> mMessage->mGroupUuid;
            xHeaderStream >> mMessage->mMemberUuid;
            xHeaderStream >> mReceiverUuid;
            xHeaderStream >> mMessage->mPluginName;
            xHeaderStream >> mMessageType;
            mBuffer.remove(0, mBlockSize);
            emit this->newMessageRecived(mReceiverUuid, mMessageType, mMessage);
            mCurrentState = 3;
        }
    }
    //-2-

    //-3-MessageText
    if(mCurrentState == 3)
    {
        if(((qint64)mBuffer.size()) >= sizeof(qint64))
        {
            QDataStream xMessageTextStream(&mBuffer, QIODevice::ReadOnly);
            xMessageTextStream >> mBlockSize;
            mBuffer.remove(0, sizeof(qint64));
            mCurrentState = 4;
        }
    }

    if(mCurrentState == 4)
    {
        if(((qint64)mBuffer.size()) >= mBlockSize)
        {
            QDataStream xMessageTextStream(&mBuffer, QIODevice::ReadOnly);
            xMessageTextStream >> mMessage->mMessage;
            mBuffer.remove(0, mBlockSize);
            mCurrentState = 5;
        }
    }
    //-3-

    //-4-FileInfo
    if(mCurrentState == 5)
    {
        if(((qint64)mBuffer.size()) >= sizeof(qint64))
        {
            QDataStream xFileInfoStream(&mBuffer, QIODevice::ReadOnly);
            xFileInfoStream >> mBlockSize;
            mBuffer.remove(0, sizeof(qint64));
            mCurrentState = 6;
        }
    }

    if(mCurrentState == 6)
    {
        if(((qint64)mBuffer.size()) >= mBlockSize)
        {
            QDataStream xFileInfoStream(&mBuffer, QIODevice::ReadOnly);
            QString xFileName;
            xFileInfoStream >> xFileName;
            xFileInfoStream >> mBlockSize;
            mTemporaryFile.setFileName(QDir::tempPath() + QDir::separator() + "XXXXXX." + xFileName);// <----------------!!!!!!!!!!!!!!!!!!!!!!!!
            mTemporaryFile.open();
            mBuffer.remove(0, mBlockSize);
            mCurrentState = 7;
        }
    }
    //-4-

    //-5-File
    if(mCurrentState == 7)
    {
        if(mTemporaryFile.size() <= mBlockSize)
        {
            mTemporaryFile.write(mBuffer);
            mBuffer.clear();
        }
        else
        {
            mTemporaryFile.close();
            mMessage->mFilePath = mTemporaryFile.fileName();
            mCurrentState = 8;
        }
    }
    //-5-

    emit mMessage->downloadProgress(mBytesReceived, mBytesTotal);
}
