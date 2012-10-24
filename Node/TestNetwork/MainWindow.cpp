#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *xParent) : QMainWindow(xParent), mUI(new Ui::MainWindow)
{
    mUI->setupUi(this);

    mCommunicationSystem = new CommunicationSystem();

    mUI->comboBox->addItems(mCommunicationSystem->getIPv4Addresses());
}

MainWindow::~MainWindow()
{
    delete mCommunicationSystem;
    delete mUI;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<mUI->comboBox->currentText()<<mUI->lineEdit->text().toUInt();
    mCommunicationSystem->initialize(mUI->lineEdit->text().toUInt());


}

void MainWindow::on_pushButton_2_clicked()
{
    Message *xMessage = new Message("lol", "lol", "plugin", "lol");
    mCommunicationSystem->sendMessage("lol", xMessage);
}
