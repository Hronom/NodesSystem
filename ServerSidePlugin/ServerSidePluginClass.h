#ifndef SERVERSIDEPLUGINCLASS_H
#define SERVERSIDEPLUGINCLASS_H

#include <QtPlugin>
#include "ServerSidePlugin_global.h"
#include "IPlugin.h"
#include "INode.h"
#include "MainForm.h"

class SERVERSIDEPLUGINSHARED_EXPORT ServerSidePluginClass: public IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)

private:
    QString mPluginName;
    QString mPluginVersion;
    QString mPluginAuthor;
    QString mPluginFilePath;

    INode *mINode;

    MainForm *mMainForm;

public:
    void initializePlugin(INode *xINode);
    QString getPluginName() { return mPluginName;}
    QString getPluginVersion() { return mPluginVersion;}
    QString getPluginAuthor() { return mPluginAuthor;}
    void executeCommand(QString xConnectionUuid, QString xCommand);
    void receiveFile(QString xConnectionUuid, QString xPluginName, QString xFilePath);
    void closePlugin();
};

#endif // SERVERSIDEPLUGINCLASS_H
