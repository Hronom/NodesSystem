#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QThread>
#include "INode.h"

class IPlugin: public QObject
{
public:
    virtual QString getPluginName() = 0;//��������� ����� �������
    virtual QString getPluginVersion() = 0;//��������� ������ �������
    virtual QString getPluginAuthor() = 0;//��������� ������ �������

    virtual void initializePlugin(INode* xINode) = 0;//������������ �������
    virtual void executeCommand(QString xConnectionUuid, QString xCommand) = 0;//���������� �������
    virtual void receiveFile(QString xConnectionUuid, QString xPluginName, QString xFilePath) = 0;
    virtual void closePlugin() = 0;//�������� �������
};

Q_DECLARE_INTERFACE(IPlugin,"IPlugin");

#endif // IPLUGIN_H
