#include "VisualController.h"

VisualController::VisualController()
{
    Q_INIT_RESOURCE(Resources);

    mNodeSettingsForm = new NodeSettingsForm();
    this->connect(mNodeSettingsForm, SIGNAL(needProgramAutoStart(bool)), SIGNAL(needProgramAutoStart(bool)));
    this->connect(mNodeSettingsForm, SIGNAL(needChangePort(quint16)), SIGNAL(needChangePort(quint16)));
    this->connect(mNodeSettingsForm, SIGNAL(needRefreshAddresses()), SIGNAL(needRefreshAddresses()));
    this->connect(mNodeSettingsForm, SIGNAL(needBroadcastSearch(quint16)), SIGNAL(needBroadcastSearch(quint16)));
    this->connect(mNodeSettingsForm, SIGNAL(needSingleSearch(QString,quint16)), SIGNAL(needSingleSearch(QString,quint16)));
    this->connect(mNodeSettingsForm, SIGNAL(needReloadPlugins()), SIGNAL(needReloadPlugins()));

    mTrayIcon = new TrayIcon();
    connect(mTrayIcon, SIGNAL(settingsAction_triggered()), this, SLOT(showNodeSettingsForm()));
}

VisualController::~VisualController()
{
    if(mNodeSettingsForm != NULL)
    {
        delete mNodeSettingsForm;
        mNodeSettingsForm = NULL;
    }

    if(mTrayIcon != NULL)
    {
        delete mTrayIcon;
        mTrayIcon = NULL;
    }

    Q_CLEANUP_RESOURCE(Resources);
}

void VisualController::setProgramAutoStart(bool xAutoStart)
{
    mNodeSettingsForm->setProgramAutoStart(xAutoStart);
}

void VisualController::setCurrentPort(quint16 xPort)
{
    mNodeSettingsForm->setCurrentPort(xPort);
}

void VisualController::updateHostAddressesList(const QList<NodeInfo> &xNodeInfoList)
{
    mNodeSettingsForm->updateHostAddressesList(xNodeInfoList);
}

void VisualController::updateNodesList(const QList<NodeInfo> &xNodeInfoList)
{
    mNodeSettingsForm->updateNodesList(xNodeInfoList);
}

void VisualController::updatePluginsList(const QList<PluginInfo> &xPluginInfoList)
{
    mNodeSettingsForm->updatePluginsList(xPluginInfoList);
}

void VisualController::UDPBindStateChanged(bool xBindState)
{
    mNodeSettingsForm->UDPBindStateChanged(xBindState);
}

void VisualController::TCPBindStateChanged(bool xBindState)
{
    mNodeSettingsForm->TCPBindStateChanged(xBindState);
}

void VisualController::insertContextMenuAction(QAction *xAction)
{
    mTrayIcon->insertContextMenuAction(xAction);
}

void VisualController::showNodeSettingsForm()
{
    mNodeSettingsForm->show();
}
