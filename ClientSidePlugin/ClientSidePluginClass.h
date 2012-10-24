#ifndef CLIENTSIDEPLUGINCLASS_H
#define CLIENTSIDEPLUGINCLASS_H

#include <QtPlugin>
#include "ClientSidePlugin_global.h"
#include "IPlugin.h"
#include "INode.h"

class CLIENTSIDEPLUGINSHARED_EXPORT ClientSidePluginClass: public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)

private:
            QString mPluginName;
    QString mPluginVersion;
    QString mPluginAuthor;
    QString mPluginFilePath;

    INode *mINode;

public:
    void initializePlugin(INode *xINode);
    QString getPluginName() { return mPluginName;}
    QString getPluginVersion() { return mPluginVersion;}
    QString getPluginAuthor() { return mPluginAuthor;}
    void executeCommand(QString xConnectionUuid, QString xCommand);
    void receiveFile(QString xConnectionUuid, QString xPluginName, QString xFilePath);
    void closePlugin();

private:
    void collectInfo(QString xConnectionUuid);
    QString collectInfoToFile(QString xFilePath);
};

#endif // CLIENTSIDEPLUGINCLASS_H
