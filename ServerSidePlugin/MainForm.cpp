#include "MainForm.h"
#include "ui_MainForm.h"
#include <QAbstractItemDelegate>
#include <QMessageBox>

MainForm::MainForm(INode *xINode, QWidget *xParent) : QWidget(xParent), mUI(new Ui::MainForm)
{
    mINode = xINode;
    mUI->setupUi(this);
    this->connect(mINode,SIGNAL(nodeAdded(QString,QString,QString,quint16)),this,SLOT(newNodesFound()));
    this->connect(mINode,SIGNAL(nodeRemoved(QString)),this,SLOT(newNodesFound()));
    this->connect(mINode,SIGNAL(nodeOnline(QString,QString,QString,quint16)),this,SLOT(newNodesFound()));
    this->connect(mINode,SIGNAL(nodeOffline(QString,QString,QString,quint16)),this,SLOT(newNodesFound()));
    mUI->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    QAction *xShowAction = new QAction(tr("Показать Аудит ПО"), this);
    this->connect(xShowAction,SIGNAL(triggered()),this,SLOT(show()));
    mINode->addContextMenuItem(xShowAction);
}

MainForm::~MainForm()
{
    delete mUI;
}

void MainForm::refillNodesTable()
{
    mUI->tableWidget->clearContents();
    for(int i = 0; i<mUI->tableWidget->rowCount(); i++)
        mUI->tableWidget->removeRow(i);
    mUI->tableWidget->setRowCount(0);

    QList<NodeInfo> xNodeInfoList = mINode->getFoundedNodes();
    foreach(NodeInfo xNodeInfo, xNodeInfoList)
    {
        mUI->tableWidget->insertRow(0);
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
        this->connect(mUI->tableWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(itemClicked_SLOT(QTableWidgetItem*)));
        mUI->tableWidget->setItem(0, 0, xNameItem);
        mUI->tableWidget->setItem(0, 1, xIPAddressItem);
        mUI->tableWidget->setItem(0, 2, xPortItem);
        mUI->tableWidget->setItem(0, 3, xConnectionStatusItem);
        mUI->tableWidget->setItem(0, 4, xDeleteItem);
    }
}

void MainForm::itemClicked_SLOT(QTableWidgetItem* xTableWidgetItem)
{
    if(xTableWidgetItem->column() == 4)
        mINode->removeNode(mUI->tableWidget->item(xTableWidgetItem->row(),0)->data(Qt::UserRole).toString());
}

void MainForm::newNodesFound()
{
    refillNodesTable();
}

void MainForm::changeEvent(QEvent *xEvent)
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

void MainForm::on_pushButton_clicked()
{
    refillNodesTable();
}

void MainForm::on_pushButton_2_clicked()
{
    if(mUI->tableWidget->selectedItems().count() > 0)
    {
        mINode->sendCommand(mUI->tableWidget->selectedItems().at(0)->data(Qt::UserRole).toString(),
                            "command",
                            "collectinfo",
                            "ClientSidePlugin");
    }
}

void MainForm::on_pushButton_3_clicked()
{
    if(mUI->radioButton_2->isChecked() == true)
        if(mUI->lineEdit->text() == "" && mUI->lineEdit_2->text().toInt() == 0)
            QMessageBox::information(NULL, tr("Ошибка ввода адреса"), tr("Введите IP-адрес и порт"));
    else
        if(mUI->lineEdit->text() == "")
            QMessageBox::information(NULL, tr("Ошибка ввода адреса"), tr("Введите IP-адрес"));
    else
        if(mUI->lineEdit_2->text().toInt() == 0)
            QMessageBox::information(NULL, tr("Ошибка ввода адреса"), tr("Введите порт"));
    else
        mINode->addNode(mUI->lineEdit->text(), mUI->lineEdit_2->text().toInt());
    else
        if(mUI->lineEdit_2->text().toInt() == 0)
            QMessageBox::information(NULL, tr("Ошибка ввода адреса"), tr("Введите порт"));
    else
        mINode->findNodes(mUI->lineEdit_2->text().toInt());
}
