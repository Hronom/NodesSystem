#ifndef VISUALCONTROLLER_H
#define VISUALCONTROLLER_H

#include <QObject>
#include "NodeSettingsForm.h"
#include "TrayIcon.h"
#include "NodeInfo.h"
#include "PluginInfo.h"

class VisualController : public QObject
{
    Q_OBJECT
private:
    NodeSettingsForm *mNodeSettingsForm;
    TrayIcon *mTrayIcon;

public:
    VisualController();
    ~VisualController();

    void setProgramAutoStart(bool xAutoStart);
    void setCurrentPort(quint16 xPort);
    void updateHostAddressesList(const QList<NodeInfo> &xNodeInfoList);
    void updateNodesList(const QList<NodeInfo> &xNodeInfoList);
    void updatePluginsList(const QList<PluginInfo> &xPluginInfoList);
    void UDPBindStateChanged(bool xBindState);
    void TCPBindStateChanged(bool xBindState);

    void insertContextMenuAction(QAction *xAction);

signals:
    void needProgramAutoStart(bool xAutoStart);
    void needChangePort(quint16 xPort);
    void needRefreshAddresses();
    void needBroadcastSearch(quint16 xPort);
    void needSingleSearch(QString xAddress,quint16 xPort);
    void needReloadPlugins();

private slots:
    void showNodeSettingsForm();
};

#endif // VISUALCONTROLLER_H
