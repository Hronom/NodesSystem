#include "MainBridge.h"
#include <QApplication>
#include <QIcon>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopWidget>

#include "PlatformFunctions.h"

void MainBridge::initialize()
{
    mUDPPortStatus = false;
    mTCPPortStatus = false;

    this->connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(mainApp_AboutToQuit()));
    this->connect(this,SIGNAL(mainAppAboutToQuit()),this,SLOT(mainApp_AboutToQuit()));
    
    mSettingsController = new SettingsController();

    mVisualController = new VisualController();
    this->connect(mVisualController,SIGNAL(needProgramAutoStart(bool)),SLOT(VisualController_ProgramAutoStart(bool)));
    this->connect(mVisualController, SIGNAL(needChangePort(quint16)), SLOT(VisualController_ChangePort(quint16)));
    this->connect(mVisualController, SIGNAL(needRefreshAddresses()), SLOT(VisualController_RefreshAddresses()));
    this->connect(mVisualController, SIGNAL(needBroadcastSearch(quint16)), SLOT(VisualController_BroadcastSearch(quint16)));
    this->connect(mVisualController, SIGNAL(needSingleSearch(QString,quint16)), SLOT(VisualController_SingleSearch(QString,quint16)));
    this->connect(mVisualController, SIGNAL(needReloadPlugins()), SLOT(VisualController_ReloadPlugins()));
    mSettingsController->setAutoStartProgram(mSettingsController->isProgramAutoStart());

    mNetworkController = new NetworkController();
    this->connect(mNetworkController,SIGNAL(nodeAdded(QString,QString,QString,quint16)),
                  this,SLOT(networkController_NodeAdded(QString,QString,QString,quint16)));
    this->connect(mNetworkController,SIGNAL(nodeRemoved(QString)),
                  this,SLOT(networkController_NodeRemoved(QString)));
    this->connect(mNetworkController,SIGNAL(nodeOnline(QString,QString,QString,quint16)),
                  this,SLOT(networkController_NodeOnline(QString,QString,QString,quint16)));
    this->connect(mNetworkController,SIGNAL(nodeOffline(QString,QString,QString,quint16)),
                  this,SLOT(networkController_NodeOffline(QString,QString,QString,quint16)));
    this->connect(mNetworkController,SIGNAL(UDPBindStateChanged(bool)),
                  this,SLOT(networkController_UDPBindStateChanged(bool)));
    this->connect(mNetworkController,SIGNAL(TCPBindStateChanged(bool)),
                  this,SLOT(networkController_TCPBindStateChanged(bool)));
    this->connect(mNetworkController,SIGNAL(receiveCommand(QString,QString,QString,QString)),
                  this,SLOT(networkController_CommandReceive(QString,QString,QString,QString)));
    this->connect(mNetworkController,SIGNAL(receiveFile(QString,QString,QString)),
                  this,SLOT(networkController_FileReceive(QString,QString,QString)));
    mNetworkController->initialize(mSettingsController->getBindPort());

    mVisualController->setCurrentPort(mNetworkController->getBindPort());

    mPluginsController = new PluginsController(this);
    mPluginsController->loadPlugins();
    mVisualController->updatePluginsList(mPluginsController->getLoadedPluginsList());

    mVisualController->updateHostAddressesList(mNetworkController->getHostAddresses());
}

void MainBridge::setAutoStartProgram(bool xAutoStartProgram)
{
    mSettingsController->setAutoStartProgram(xAutoStartProgram);
}

bool MainBridge::isProgramAutoStart()
{
    return mSettingsController->isProgramAutoStart();
}

void MainBridge::closeApp()
{
    emit this->mainAppAboutToQuit();
}

void MainBridge::findNodes(quint16 xNodePort)
{
    mNetworkController->findNodes(xNodePort);
}

void MainBridge::addNode(QString xNodeIP, quint16 xNodePort)
{
    return mNetworkController->addNode(xNodeIP, xNodePort);
}

void MainBridge::removeNode(QString xConnectionUuid)
{
    mNetworkController->removeNode(xConnectionUuid);
}

QList<NodeInfo> MainBridge::getHostAddresses()
{
    return mNetworkController->getHostAddresses();
}

QList<NodeInfo> MainBridge::getFoundedNodes()
{
    return mNetworkController->getFoundedNodes();
}

NodeInfo MainBridge::getNodeInfo(QString xConnectionUuid)
{
    return mNetworkController->getNodeInfo(xConnectionUuid);
}

void MainBridge::sendCommand(QString xConnectionUuid, QString xMessageType, QString xCommand, QString xPluginName)
{
    mNetworkController->sendCommand(xConnectionUuid, xMessageType, xCommand, xPluginName);
}

void MainBridge::sendFile(QString xConnectionUuid, QString xPluginName, QString xFilePath)
{
    mNetworkController->sendFile(xConnectionUuid, xPluginName, xFilePath);
}

quint16 MainBridge::getBindPort()
{
    return mNetworkController->getBindPort();
}

void MainBridge::setBindPort(quint16 xPort)
{
    mSettingsController->setBindPort(xPort);
    mNetworkController->setBindPort(xPort);
}

bool MainBridge::getUDPPortStatus()
{
    return mUDPPortStatus;
}

bool MainBridge::getTCPPortStatus()
{
    return mTCPPortStatus;
}

QList<PluginInfo> MainBridge::getLoadedPluginsList()
{
    return mPluginsController->getLoadedPluginsList();
}

void MainBridge::reloadPlugins()
{
    mPluginsController->unloadPlugins();
    mPluginsController->loadPlugins();
    mVisualController->updatePluginsList(mPluginsController->getLoadedPluginsList());
}

void MainBridge::addContextMenuItem(QAction *xAction)
{
    mVisualController->insertContextMenuAction(xAction);
}

void MainBridge::VisualController_ProgramAutoStart(bool xAutoStart)
{
    mSettingsController->setAutoStartProgram(xAutoStart);
    mSettingsController->setAutoStartProgram(mSettingsController->isProgramAutoStart());
}

void MainBridge::VisualController_ChangePort(quint16 xPort)
{
    mSettingsController->setBindPort(xPort);
    mNetworkController->setBindPort(xPort);
    mVisualController->updateHostAddressesList(mNetworkController->getHostAddresses());
}

void MainBridge::VisualController_RefreshAddresses()
{
    mVisualController->updateHostAddressesList(mNetworkController->getHostAddresses());
}

void MainBridge::VisualController_BroadcastSearch(quint16 xPort)
{
    mNetworkController->findNodes(xPort);
}

void MainBridge::VisualController_SingleSearch(QString xAddress,quint16 xPort)
{
    mNetworkController->addNode(xAddress, xPort);
}

void MainBridge::VisualController_ReloadPlugins()
{
    mPluginsController->unloadPlugins();
    mPluginsController->loadPlugins();
    mVisualController->updatePluginsList(mPluginsController->getLoadedPluginsList());
}

void MainBridge::networkController_NodeAdded(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort)
{
    mVisualController->updateNodesList(mNetworkController->getFoundedNodes());
    emit this->nodeAdded(xConnectionUuid, xPeerNodeName, xPeerNodeIP, xPeerNodePort);
}

void MainBridge::networkController_NodeRemoved(QString xConnectionUuid)
{
    mVisualController->updateNodesList(mNetworkController->getFoundedNodes());
    emit this->nodeRemoved(xConnectionUuid);
}

void MainBridge::networkController_NodeOnline(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort)
{
    mVisualController->updateNodesList(mNetworkController->getFoundedNodes());
    emit this->nodeOnline(xConnectionUuid, xPeerNodeName, xPeerNodeIP, xPeerNodePort);
}

void MainBridge::networkController_NodeOffline(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort)
{
    mVisualController->updateNodesList(mNetworkController->getFoundedNodes());
    emit this->nodeOffline(xConnectionUuid, xPeerNodeName, xPeerNodeIP, xPeerNodePort);
}

void MainBridge::networkController_UDPBindStateChanged(bool xBindState)
{
    mUDPPortStatus = xBindState;
    mVisualController->UDPBindStateChanged(mUDPPortStatus);
    emit this->UDPBindStateChanged(xBindState);
}

void MainBridge::networkController_TCPBindStateChanged(bool xBindState)
{
    mTCPPortStatus = xBindState;
    mVisualController->TCPBindStateChanged(mTCPPortStatus);
    emit this->TCPBindStateChanged(xBindState);
}

void MainBridge::networkController_CommandReceive(QString xConnectionUuid, QString xMessageType, QString xCommand, QString xPluginName)
{
    if(xMessageType != "sys")
        mPluginsController->receivedCommand(xConnectionUuid, xPluginName, xCommand);
}

void MainBridge::networkController_FileReceive(QString xConnectionUuid, QString xPluginName, QString xFilePath)
{
    mPluginsController->receivedFile(xConnectionUuid, xPluginName, xFilePath);
}

void MainBridge::mainApp_AboutToQuit()
{
    if(mPluginsController != NULL)
    {
        qDebug()<<"Delete mPluginsController";
        delete mPluginsController;
        mPluginsController = NULL;
        qDebug()<<"mPluginsController deleted";
    }

    if(mNetworkController != NULL)
    {
        qDebug()<<"Delete mNetworkController";
        delete mNetworkController;
        mNetworkController = NULL;
        qDebug()<<"mNetworkController deleted";
    }

    if(mVisualController != NULL)
    {
        qDebug()<<"Delete mVisualController";
        delete mVisualController;
        mVisualController = NULL;
        qDebug()<<"mVisualController deleted";
    }

    if(mSettingsController != NULL)
    {
        qDebug()<<"Delete mSettingsController";
        delete mSettingsController;
        mSettingsController = NULL;
        qDebug()<<"mSettingsController deleted";
    }
}
