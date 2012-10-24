#include "NetworkRequest.h"
#include <QDir>
#include <QFileInfo>

NetworkRequest::NetworkRequest()
{
    mMessage = 0;
    mCurrentState = 0;
}

NetworkRequest::NetworkRequest(const QString &xSenderUuid, const QString &xMessageType, Message *xMessage)
{
    mMessage = xMessage;
    mFile.setFileName(xMessage->getFilePath());

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


    //-1-PackageInfo
    QByteArray xPackageInfo;
    QDataStream xPackageInfoStream(&xPackageInfo, QIODevice::WriteOnly);
    xPackageInfoStream.setVersion(QDataStream::Qt_4_7);
    xPackageInfoStream << qint64(0);
    //-1-
    //-2-Header
    QByteArray xHeader;
    QDataStream xHeaderStream(&xHeader, QIODevice::WriteOnly);
    xHeaderStream.setVersion(QDataStream::Qt_4_7);
    xHeaderStream << qint64(0);
    xHeaderStream << xMessage->getGroupUuid();
    xHeaderStream << xSenderUuid;
    xHeaderStream << xMessage->getMemberUuid();
    xHeaderStream << xMessage->getPluginName();
    xHeaderStream << xMessageType;
    xHeaderStream.device()->seek(0);
    xHeaderStream << qint64(xHeader.size());
    //-2-
    //-3-MessageText
    QByteArray xMessageText;
    QDataStream xMessageTextStream(&xMessageText, QIODevice::WriteOnly);
    xMessageTextStream.setVersion(QDataStream::Qt_4_7);
    xMessageTextStream << qint64(0);
    xMessageTextStream << xMessage->getMessage();
    xMessageTextStream.device()->seek(0);
    xMessageTextStream << qint64(xMessageText.size());
    //-3-
    //-4-FileInfo
    QByteArray xFileInfo;
    QDataStream xFileInfoStream(&xFileInfo, QIODevice::WriteOnly);
    xFileInfoStream.setVersion(QDataStream::Qt_4_7);
    xFileInfoStream << qint64(0);
    xFileInfoStream << mFile.fileName();
    xFileInfoStream << qint64(mFile.size());
    xFileInfoStream.device()->seek(0);
    xFileInfoStream << qint64(xFileInfo.size());
    //-4-
    //-5-package info fill
    xPackageInfoStream.device()->seek(0);
    xPackageInfoStream << qint64(xHeader.size() + xMessageText.size() + xFileInfo.size() + mFile.size());
    //-5-

    mBytesSent = 0;
    mBytesTotal = qint64(xPackageInfo.size() + xHeader.size() + xMessageText.size() + xFileInfo.size() + mFile.size());

    mCurrentState = 0;

    mBuffer.open(QBuffer::WriteOnly);
    mBuffer.seek(0);
    mBuffer.write(xPackageInfo);
    mBuffer.write(xHeader);
    mBuffer.write(xMessageText);
    mBuffer.write(xFileInfo);
    mBuffer.close();
}

QByteArray NetworkRequest::getBytesToSend(qint64 xMaxSize)
{
    QByteArray xTemp;

    if(mCurrentState == 0)
    {
        mBuffer.open(QBuffer::ReadOnly);
        mBuffer.seek(0);
        mCurrentState = 1;
    }

    if(mCurrentState == 1)
    {
        if(mBuffer.atEnd() == false)
        {
            xTemp.append(mBuffer.read(xMaxSize));
            mBytesSent += xTemp.size();
        }

        mBuffer.close();
        mCurrentState = 2;
    }

    if(mCurrentState == 2)
    {
        if(mFile.exists() == false)
        {
            xTemp = 0;
            mCurrentState = 4;
        }
        else
        {
            mFile.open(QFile::ReadOnly);
            mFile.seek(0);
            mCurrentState = 3;
        }
    }

    if(mCurrentState == 3)
    {
        if(mFile.atEnd() == false)
        {
            xTemp = mFile.read(xMaxSize);
            mBytesSent += xTemp.size();
            emit mMessage->uploadProgress(mBytesSent, mBytesTotal);
        }

        mFile.close();
        mCurrentState = 4;
    }

    emit mMessage->uploadProgress(mBytesSent, mBytesTotal);
    return xTemp;
}

bool NetworkRequest::isTransferComplete()
{
    if(mBytesSent == mBytesTotal)
        return true;
    else
        return false;
}

void NetworkRequest::abortTransfer()
{
    mBuffer.close();
    mFile.close();
    mCurrentState = 0;
    emit mMessage->transferAborted();
}
