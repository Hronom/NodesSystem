#ifndef MAINBRIDGE_H
#define MAINBRIDGE_H

#include <QtGlobal>
#include <QMenu>
#include <QList>
#include <QAction>
#include <QString>

#include "INode.h"
#include "IPlugin.h"
#include "NodeInfo.h"
#include "PluginInfo.h"
#include "NetworkController.h"
#include "PluginsController.h"
#include "SettingsController.h"
#include "VisualController.h"

class MainBridge: public INode
{
    Q_OBJECT
    Q_INTERFACES(INode)

private:
    SettingsController *mSettingsController;
    VisualController *mVisualController;

    NetworkController *mNetworkController;
    PluginsController *mPluginsController;

    bool mUDPPortStatus;
    bool mTCPPortStatus;

public:
    void initialize();
    void setAutoStartProgram(bool xAutoStartProgram);
    bool isProgramAutoStart();
    void closeApp();//реализайция инетрфейса INode
    void findNodes(quint16 xNodePort);//реализайция инетрфейса INode
    void addNode(QString xNodeIP, quint16 xNodePort);//реализайция инетрфейса INode
    void removeNode(QString xConnectionUuid);//удаление нода по указанному уникальному номеру
    QList<NodeInfo> getHostAddresses();
    QList<NodeInfo> getFoundedNodes();
    NodeInfo getNodeInfo(QString xConnectionUuid);
    void sendCommand(QString xConnectionUuid, QString xMessageType, QString xCommand, QString xPluginName);
    void sendFile(QString xConnectionUuid, QString xPluginName, QString xFilePath);
    quint16 getBindPort();
    void setBindPort(quint16 xPort);
    bool getUDPPortStatus();
    bool getTCPPortStatus();
    QList<PluginInfo> getLoadedPluginsList();
    void reloadPlugins();
    void addContextMenuItem(QAction *xAction);

private slots:
    void VisualController_ProgramAutoStart(bool xAutoStart);
    void VisualController_ChangePort(quint16 xPort);
    void VisualController_RefreshAddresses();
    void VisualController_BroadcastSearch(quint16 xPort);
    void VisualController_SingleSearch(QString xAddress,quint16 xPort);
    void VisualController_ReloadPlugins();

    void networkController_NodeAdded(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort);
    void networkController_NodeRemoved(QString xConnectionUuid);
    void networkController_NodeOnline(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort);
    void networkController_NodeOffline(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort);
    void networkController_UDPBindStateChanged(bool xBindState);//сигнал оповещения состояния прослушивания UDP порта
    void networkController_TCPBindStateChanged(bool xBindState);//сигнал оповещения состояния прослушивания TCP порта
    void networkController_CommandReceive(QString xConnectionUuid, QString xMessageType, QString xCommand, QString xPluginName);
    void networkController_FileReceive(QString xConnectionUuid, QString xPluginName, QString xFilePath);
    void mainApp_AboutToQuit();
};

#endif // MAINBRIDGE_H
