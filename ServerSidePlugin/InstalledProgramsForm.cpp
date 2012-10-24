#include "InstalledProgramsForm.h"
#include "ui_InstalledProgramsForm.h"
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QDomDocument>
#include <QDomNodeList>
#include <QDir>


InstalledProgramsForm::InstalledProgramsForm(NodeInfo xNodeInfo, QWidget *xParent)
    :QWidget(xParent), mUI(new Ui::InstalledProgramsForm)
{
    mUI->setupUi(this);
    mUI->ProgramsList->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    mUI->CompName->setText(xNodeInfo.Name);
    mUI->CompIPAddress->setText(xNodeInfo.IPAddress);
    mUI->CompPort->setText(QString::number(xNodeInfo.Port));
}

InstalledProgramsForm::~InstalledProgramsForm()
{
    delete mUI;

    mUI->ProgramsList->clearContents();
}

void InstalledProgramsForm::setProgramList(QString xFilePath)
{
    QDomDocument xDomDocument("xml");

    QFile xFile(xFilePath);
    xFile.open(QIODevice::ReadOnly);
    xDomDocument.setContent(&xFile);
    xFile.close();

    QDomElement xRootElement = xDomDocument.documentElement();

    for(QDomElement xProgramElement = xRootElement.firstChildElement("InstalledProgram"); xProgramElement.isNull() == false; xProgramElement = xProgramElement.nextSiblingElement("InstalledProgram"))
    {
        if(xProgramElement.attribute("DisplayName", "") != "")
        {
            QString mRegisterPath = xProgramElement.attribute("RegisterPath", tr("������ �����������"));
            QString mDisplayName = xProgramElement.attribute("DisplayName", tr("������ �����������"));
            QString mDisplayVersion = xProgramElement.attribute("DisplayVersion", tr("������ �����������"));
            QString mInstallLocation = xProgramElement.attribute("InstallLocation", tr("������ �����������"));
            QString mInstallDate = xProgramElement.attribute("InstallDate", tr("������ �����������"));
            QString mPublisher = xProgramElement.attribute("Publisher", tr("������ �����������"));

            mUI->ProgramsList->insertRow(0);
            QTableWidgetItem *xDisplayName = new QTableWidgetItem(mDisplayName);
            QTableWidgetItem *xDisplayVersion = new QTableWidgetItem(mDisplayVersion);
            QTableWidgetItem *xPublisher = new QTableWidgetItem(mPublisher);
            QTableWidgetItem *xInstallDate = new QTableWidgetItem(mInstallDate);
            QTableWidgetItem *xInstallLocation = new QTableWidgetItem(mInstallLocation);
            QTableWidgetItem *xRegisterPath = new QTableWidgetItem(mRegisterPath);
            mUI->ProgramsList->setItem(0, 0, xDisplayName);
            mUI->ProgramsList->setItem(0, 1, xDisplayVersion);
            mUI->ProgramsList->setItem(0, 2, xPublisher);
            mUI->ProgramsList->setItem(0, 3, xInstallDate);
            mUI->ProgramsList->setItem(0, 4, xInstallLocation);
            mUI->ProgramsList->setItem(0, 5, xRegisterPath);
        }
    }
}

void InstalledProgramsForm::changeEvent(QEvent *xEvent)
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

void InstalledProgramsForm::on_pushButton_clicked()
{
    QString xFilePath = QFileDialog::getSaveFileName(this, tr("��������� ����"),
                                                     mUI->CompName->text() + ".html",
                                                     tr("����� (*.html)"));

    QFile xFile(xFilePath);
    if(xFile.exists() == true) xFile.remove();
    xFile.open(QFile::WriteOnly);

    QTextStream xOut(&xFile);
    xOut<<"<html><body><h4>"<<tr("O���� � ����������� �����������")<<"</h4>"
            <<tr("��� ����������: ")
            <<mUI->CompName->text()
            <<"<br>"<<tr("IP-������: ")
            <<mUI->CompIPAddress->text()<<endl;
    xOut<<"<table border=1 cellpadding=5px style='border:solid; border-collapse:collapse;' >"<<endl;

    xOut<<"<tr>";
    xOut<<"<td>"<<tr("��� ���������");
    xOut<<"<td>"<<tr("������������ ������");
    xOut<<"<td>"<<tr("�����������");
    xOut<<"<td>"<<tr("���� ���������");
    xOut<<"<td>"<<tr("���� ���������");
    xOut<<"<td>"<<tr("���� � �������");
    xOut<<endl;

    for(int i = 0; i < mUI->ProgramsList->rowCount(); i++)
    {
        xOut<<"<tr>";
        xOut<<"<td>"<<mUI->ProgramsList->item(i,0)->text();
        xOut<<"<td>"<<mUI->ProgramsList->item(i,1)->text();
        xOut<<"<td>"<<mUI->ProgramsList->item(i,2)->text();
        xOut<<"<td>"<<mUI->ProgramsList->item(i,3)->text();
        xOut<<"<td>"<<mUI->ProgramsList->item(i,4)->text();
        xOut<<"<td>"<<mUI->ProgramsList->item(i,5)->text();
        xOut<<endl;
    }

    xOut<<"</table>"<<endl;
    xOut<<"</body></html>";
    xFile.flush();
    xFile.close();
}
