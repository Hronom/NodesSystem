#ifndef PLUGINSCONTROLLER_H
#define PLUGINSCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QPluginLoader>
#include "INode.h"
#include "IPlugin.h"
#include "PluginInfo.h"

class PluginsController : public QObject
{
    Q_OBJECT
private:
    INode* mINode;
    QMap<IPlugin*, QPluginLoader*> mIPluginMap;

public:
    PluginsController(INode* xINode);
    ~PluginsController();

    void loadPlugins();
    void unloadPlugins();

    void receivedCommand(QString xConnectionUuid, QString xPluginName, QString xCommand);
    void receivedFile(QString xConnectionUuid, QString xPluginName, QString xFilePath);
    QList<PluginInfo> getLoadedPluginsList();
};

#endif // PLUGINSCONTROLLER_H
