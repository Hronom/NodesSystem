#include "PluginsController.h"
#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QLibraryInfo>

PluginsController::PluginsController(INode* xINode)
{
    mINode = xINode;
}

PluginsController::~PluginsController()
{
    unloadPlugins();
}

void PluginsController::loadPlugins()
{
#ifdef Q_WS_WIN
    QDir xPluginsDir(qApp->applicationDirPath() + "/plugins/");//����� ���������� ��������

    //-1-���� ���������� �������� �� ���������� ������ �
    if(xPluginsDir.exists() == false)
        xPluginsDir.mkpath(xPluginsDir.absolutePath());
    //-1-

    QStringList xListOfDirs = xPluginsDir.entryList(QDir::Dirs|QDir::NoDotAndDotDot);

    foreach(QString xDirName, xListOfDirs)
    {
        QPluginLoader *xPluginLoader = new QPluginLoader(xPluginsDir.absolutePath() + "/"
                                                         + xDirName + "/" + xDirName + ".dll");

        if(xPluginLoader->load() == true)//��������� �� ������� ���� ������������ �����������
        {
            //QPluginLoader *xPluginLoader = new QPluginLoader(xPluginLib.fileName());//�������� �������
            QObject *xObject = xPluginLoader->instance();//��������� �������� ���������� �������
            if (xObject != NULL)
            {
                IPlugin *xIPlugin;
                xIPlugin = qobject_cast<IPlugin *>(xObject);//��������� ��������� �������
                if(xIPlugin != NULL)
                {
                    xIPlugin->initializePlugin(mINode);
                    mIPluginMap[xIPlugin] = xPluginLoader;
                }
            }
            else QMessageBox::information(NULL, tr("������ �������� ������"), xPluginLoader->errorString ());
        }
        else
            xPluginLoader->deleteLater();
    }
#endif

#ifdef Q_WS_S60
    QDir xPluginsDir(QLibraryInfo::location(QLibraryInfo::PluginsPath));
    QPluginLoader *xPluginLoader = new QPluginLoader(xPluginsDir.absolutePath() + "/Node/ServerSidePlugin/ServerSidePlugin.qtplugin");

    if(xPluginLoader->load() == true)//��������� �� ������� ���� ������������ �����������
    {
        QObject *xObject = xPluginLoader->instance();//��������� �������� ���������� �������
        if (xObject != NULL)
        {
            IPlugin *xIPlugin;
            xIPlugin = qobject_cast<IPlugin *>(xObject);//��������� ��������� �������
            if(xIPlugin != NULL)
            {
                xIPlugin->initializePlugin(mINode);
                mIPluginMap[xIPlugin] = xPluginLoader;
            }
        }
        else QMessageBox::information(NULL, tr("������ �������� ������"), xPluginLoader->errorString());
    }
    else
        QMessageBox::information(NULL, "ServerSidePlugin not loaded error string: ", xPluginLoader->errorString());
#endif
}

void PluginsController::unloadPlugins()
{
    QMutableMapIterator<IPlugin*, QPluginLoader*> i(mIPluginMap);
    while(i.hasNext())
    {
        i.next();

        i.key()->closePlugin();
        delete i.key();
        i.value()->unload();
        delete i.value();

        i.remove();
    }
}

void PluginsController::receivedCommand(QString xConnectionUuid, QString xPluginName, QString xCommand)
{
    QMutableMapIterator<IPlugin*, QPluginLoader*> i(mIPluginMap);
    if(xPluginName == "all")
    {
        while(i.hasNext())
        {
            i.next();
            i.key()->executeCommand(xConnectionUuid, xCommand);
        }
    }
    else
    {
        while(i.hasNext())
        {
            i.next();
            if(i.key()->getPluginName() == xPluginName)
            {
                i.key()->executeCommand(xConnectionUuid, xCommand);
                //return;
            }
        }
    }
}

void PluginsController::receivedFile(QString xConnectionUuid, QString xPluginName, QString xFilePath)
{
    QMutableMapIterator<IPlugin*, QPluginLoader*> i(mIPluginMap);
    if(xPluginName == "all")
    {
        while(i.hasNext())
        {
            i.next();
            i.key()->receiveFile(xConnectionUuid, xPluginName, xFilePath);
        }
    }
    else
    {
        while(i.hasNext())
        {
            i.next();
            if(i.key()->getPluginName() == xPluginName)
            {
                i.key()->receiveFile(xConnectionUuid, xPluginName, xFilePath);
                //return;
            }
        }
    }
}

QList<PluginInfo> PluginsController::getLoadedPluginsList()
{
    QList<PluginInfo> xPluginInfoList;
    QMutableMapIterator<IPlugin*, QPluginLoader*> i(mIPluginMap);
    while(i.hasNext())
    {
        i.next();

        PluginInfo xPluginInfo;
        xPluginInfo.Name = i.key()->getPluginName();
        xPluginInfo.Version = i.key()->getPluginVersion();
        xPluginInfo.Author = i.key()->getPluginAuthor();
        xPluginInfoList.push_back(xPluginInfo);
    }

    return xPluginInfoList;
}
