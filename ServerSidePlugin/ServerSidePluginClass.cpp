#include <ServerSidePluginClass.h>

#include "InstalledProgramsForm.h"
#include <QApplication>
#include <QDebug>
#include <QThread>

void ServerSidePluginClass::initializePlugin(INode *xINode)
{
    mPluginName = "ServerSidePlugin";
    mPluginVersion = "3.0.0";
    mPluginAuthor = "Hronom";

    qDebug()<<"InitializePlugin"<<mPluginName;
    mPluginFilePath = qApp->applicationFilePath();
    mINode = xINode;

    mMainForm = new MainForm(mINode);
    mMainForm->show();
}

void ServerSidePluginClass::executeCommand(QString xConnectionUuid, QString xCommand)
{
}

void ServerSidePluginClass::receiveFile(QString xConnectionUuid, QString xPluginName, QString xFilePath)
{
    InstalledProgramsForm *xInstalledProgramsForm = new InstalledProgramsForm(mINode->getNodeInfo(xConnectionUuid));
    xInstalledProgramsForm->setProgramList(xFilePath);
    xInstalledProgramsForm->show();
}

void ServerSidePluginClass::closePlugin()
{
    qDebug()<<"ClosePlugin"<<mPluginName;

    if(mMainForm != NULL)
    {
        delete mMainForm;
        mMainForm = NULL;
    }
}

Q_EXPORT_PLUGIN2(ServerSidePlugin,ServerSidePluginClass)
