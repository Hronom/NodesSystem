#ifndef NODESETTINGSFORM_H
#define NODESETTINGSFORM_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "NodeInfo.h"
#include "PluginInfo.h"

namespace Ui
{
class MainWindow;
}

class NodeSettingsForm : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *mUI;

public:
    NodeSettingsForm(QWidget *xParent = 0);
    ~NodeSettingsForm();

    void setProgramAutoStart(bool xAutoStart);
    void setCurrentPort(quint16 xPort);
    void updateHostAddressesList(const QList<NodeInfo> &xNodeInfoList);
    void updateNodesList(const QList<NodeInfo> &xNodeInfoList);
    void updatePluginsList(const QList<PluginInfo> &xPluginInfoList);
    void UDPBindStateChanged(bool xBindState);
    void TCPBindStateChanged(bool xBindState);

protected:
    void changeEvent(QEvent *xEvent);
    void showEvent(QShowEvent *xEvent);

signals:
    void needProgramAutoStart(bool xAutoStart);
    void needChangePort(quint16 xPort);
    void needRefreshAddresses();
    void needBroadcastSearch(quint16 xPort);
    void needSingleSearch(QString xAddress,quint16 xPort);
    void needReloadPlugins();

private slots:
    void on_programAutoStart_stateChanged(int xState);
    void on_changePortButton_clicked();
    void on_refreshAddressesButton_clicked();
    void on_beginSearchButton_clicked();
    void on_reloadPluginsButton_clicked();
};

#endif // NODESETTINGSFORM_H
