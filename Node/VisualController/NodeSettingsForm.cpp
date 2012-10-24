#include "NodeSettingsForm.h"
#include "ui_NodeSettingsForm.h"
#include "NodeInfo.h"

#include <QList>
#include <QPushButton>
#include <QDebug>

NodeSettingsForm::NodeSettingsForm(QWidget *xParent) : QMainWindow(xParent), mUI(new Ui::MainWindow)
{
    mUI->setupUi(this);

    mUI->NodesTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    mUI->PluginsTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    mUI->HostAddressesTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    mUI->tabWidget->setCurrentIndex(0);
}

NodeSettingsForm::~NodeSettingsForm()
{
    delete mUI;
}

void NodeSettingsForm::setProgramAutoStart(bool xAutoStart)
{
    if(xAutoStart == true)
        mUI->programAutoStart->setCheckState(Qt::Checked);
    else
        mUI->programAutoStart->setCheckState(Qt::Unchecked);
}

void NodeSettingsForm::setCurrentPort(quint16 xPort)
{
    mUI->currentPortSpinBox->setValue(xPort);
}

void NodeSettingsForm::updateHostAddressesList(const QList<NodeInfo> &xNodeInfoList)
{
    mUI->HostAddressesTable->clearContents();
    mUI->HostAddressesTable->setRowCount(0);

    foreach(NodeInfo xNodeInfo, xNodeInfoList)
    {
        mUI->HostAddressesTable->insertRow(0);
        QTableWidgetItem *xIPAddressItem = new QTableWidgetItem(xNodeInfo.IPAddress);
        QTableWidgetItem *xPortItem = new QTableWidgetItem(QString::number(xNodeInfo.Port));
        mUI->HostAddressesTable->setItem(0, 0, xIPAddressItem);
        mUI->HostAddressesTable->setItem(0, 1, xPortItem);
    }
}

void NodeSettingsForm::updateNodesList(const QList<NodeInfo> &xNodeInfoList)
{
    mUI->NodesTable->clearContents();
    mUI->NodesTable->setRowCount(0);

    foreach(NodeInfo xNodeInfo, xNodeInfoList)
    {
        mUI->NodesTable->insertRow(0);
        QTableWidgetItem *xNameItem = new QTableWidgetItem(xNodeInfo.Name);
        xNameItem->setData(Qt::UserRole, xNodeInfo.ConnectionUuid);
        QTableWidgetItem *xIPAddressItem = new QTableWidgetItem(xNodeInfo.IPAddress);
        QTableWidgetItem *xPortItem = new QTableWidgetItem(QString::number(xNodeInfo.Port));
        QTableWidgetItem *xConnectionStatusItem;
        if(xNodeInfo.ConnectionStatus == 1)
            xConnectionStatusItem = new QTableWidgetItem(tr("соединение установлено"));
        else
            xConnectionStatusItem = new QTableWidgetItem(tr("соединение не установлено"));
        QTableWidgetItem *xDeleteItem = new QTableWidgetItem(QIcon(":/Icons/Delete"),tr("Удалить"));
        this->connect(mUI->NodesTable,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(itemClicked_SLOT(QTableWidgetItem*)));
        mUI->NodesTable->setItem(0, 0, xNameItem);
        mUI->NodesTable->setItem(0, 1, xIPAddressItem);
        mUI->NodesTable->setItem(0, 2, xPortItem);
        mUI->NodesTable->setItem(0, 3, xConnectionStatusItem);
        mUI->NodesTable->setItem(0, 4, xDeleteItem);
    }
}

void NodeSettingsForm::updatePluginsList(const QList<PluginInfo> &xPluginInfoList)
{
    mUI->PluginsTable->clearContents();
    mUI->PluginsTable->setRowCount(0);

    foreach(PluginInfo xPluginInfo, xPluginInfoList)
    {
        mUI->PluginsTable->insertRow(0);
        QTableWidgetItem *xPluginAuthorItem = new QTableWidgetItem(xPluginInfo.Author);
        QTableWidgetItem *xPluginNameItem = new QTableWidgetItem(xPluginInfo.Name);
        QTableWidgetItem *xPluginVersionItem = new QTableWidgetItem(xPluginInfo.Version);
        mUI->PluginsTable->setItem(0, 0, xPluginAuthorItem);
        mUI->PluginsTable->setItem(0, 1, xPluginNameItem);
        mUI->PluginsTable->setItem(0, 2, xPluginVersionItem);
    }
}

void NodeSettingsForm::UDPBindStateChanged(bool xBindState)
{
    if(xBindState == true)
    {
        mUI->label_7->setText(tr("прослушивается"));
        mUI->label_7->setStyleSheet("background: green; color: white;");
    }
    else
    {
        mUI->label_7->setText(tr("уже используеться"));
        mUI->label_7->setStyleSheet("background: red; color: white;");
    }
}

void NodeSettingsForm::TCPBindStateChanged(bool xBindState)
{
    if(xBindState == true)
    {
        mUI->label_9->setText(tr("прослушивается"));
        mUI->label_9->setStyleSheet("background: green; color: white;");
    }
    else
    {
        mUI->label_9->setText(tr("уже используеться"));
        mUI->label_9->setStyleSheet("background: red; color: white;");
    }
}

void NodeSettingsForm::changeEvent(QEvent *xEvent)
{
    QWidget::changeEvent(xEvent);
    switch (xEvent->type())
    {
    case QEvent::LanguageChange:
        mUI->retranslateUi(this);
        break;
    default:
        break;
    }
}

void NodeSettingsForm::showEvent(QShowEvent *xEvent)
{

}

void NodeSettingsForm::on_programAutoStart_stateChanged(int xState)
{
    if(xState == Qt::Checked)
        emit this->needProgramAutoStart(true);
    else
        emit this->needProgramAutoStart(false);
}

void NodeSettingsForm::on_changePortButton_clicked()
{
    emit this->needChangePort(mUI->currentPortSpinBox->value());
}

void NodeSettingsForm::on_refreshAddressesButton_clicked()
{
    emit this->needRefreshAddresses();
}

void NodeSettingsForm::on_beginSearchButton_clicked()
{
    if(mUI->MassSearch->isChecked() == true)
        emit this->needBroadcastSearch(mUI->searchPortSpinBox->value());
    else
        emit this->needSingleSearch(mUI->searchAddressLineEdit->text(), mUI->searchPortSpinBox->value());
}

void NodeSettingsForm::on_reloadPluginsButton_clicked()
{
    emit this->needReloadPlugins();
}
