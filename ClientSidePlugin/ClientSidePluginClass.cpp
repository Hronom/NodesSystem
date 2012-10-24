#include <ClientSidePluginClass.h>
#include <QApplication>
#include <QDebug>
#include <QStringList>
#include <QFile>
#include <QDomDocument>
#include <QDir>
#include <QTextStream>
#include <QSettings>

void ClientSidePluginClass::initializePlugin(INode *xINode)
{
    mPluginName = "ClientSidePlugin";
    mPluginVersion = "3.0.0";
    mPluginAuthor = "Hronom";

    qDebug()<<"InitializePlugin"<<mPluginName;
    mPluginFilePath = qApp->applicationFilePath();
    mINode = xINode;
}

void ClientSidePluginClass::executeCommand(QString xConnectionUuid, QString xCommand)
{
    if(xCommand == "collectinfo") collectInfo(xConnectionUuid);
}

void ClientSidePluginClass::receiveFile(QString xConnectionUuid, QString xPluginName, QString xFilePath)
{
}

void ClientSidePluginClass::closePlugin()
{
    qDebug()<<"ClosePlugin"<<mPluginName;
}

void ClientSidePluginClass::collectInfo(QString xConnectionUuid)
{
    QString xFilePath;
    xFilePath = collectInfoToFile(qApp->applicationDirPath() + "/filetosend/");
    mINode->sendFile(xConnectionUuid, "ServerSidePlugin", xFilePath);
}

QString ClientSidePluginClass::collectInfoToFile(QString xFilePath)
{
    QString xMainRegKey = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall";
    QSettings *xMainRegSettings = new QSettings(xMainRegKey, QSettings::NativeFormat);
    QStringList xKeys = xMainRegSettings->childGroups();
    delete xMainRegSettings;

    QDomDocument xDomDocument = QDomDocument("xml");
    QDomElement xRootElement = xDomDocument.createElement("main");
    xDomDocument.appendChild(xRootElement);

    foreach(QString xString, xKeys)
    {
        QSettings *xInstalledProgramSettings;
        xInstalledProgramSettings = new QSettings(xMainRegKey + "\\" + xString, QSettings::NativeFormat);

        QString xRegisterPath = xInstalledProgramSettings->fileName();
        QString xDisplayName = xInstalledProgramSettings->value("DisplayName", "").toString();
        QString xDisplayVersion = xInstalledProgramSettings->value("DisplayVersion", "").toString();
        QString xPublisher = xInstalledProgramSettings->value("Publisher", "").toString();
        QString xInstallDate = xInstalledProgramSettings->value("InstallDate", "").toString();
        QString xInstallLocation = xInstalledProgramSettings->value("InstallLocation", "").toString();

        delete xInstalledProgramSettings;

        QDomElement xProgramElement = xDomDocument.createElement("InstalledProgram");

        if(xRegisterPath != "")
            xProgramElement.setAttribute("RegisterPath", xRegisterPath);
        if(xDisplayName != "")
            xProgramElement.setAttribute("DisplayName", xDisplayName);
        if(xDisplayVersion != "")
            xProgramElement.setAttribute("DisplayVersion", xDisplayVersion);
        if(xPublisher != "")
            xProgramElement.setAttribute("Publisher", xPublisher);
        if(xInstallDate != "")
            xProgramElement.setAttribute("InstallDate", xInstallDate);
        if(xInstallLocation != "")
            xProgramElement.setAttribute("InstallLocation", xInstallLocation);

        xRootElement.appendChild(xProgramElement);
    }

    QDir xFileDir(xFilePath);
    if(xFileDir.exists() == false) xFileDir.mkpath(xFileDir.absolutePath());

    QFile xFile(xFilePath + "InstalledPrograms.xml");
    if(xFile.exists() == true) xFile.remove();
    xFile.open(QFile::WriteOnly);

    QTextStream xOut(&xFile);
    const int xIndentSize = 4;
    xDomDocument.save(xOut, xIndentSize);

    xFile.close();

    return xFile.fileName();
}

Q_EXPORT_PLUGIN2(ClientSidePlugin,ClientSidePluginClass)
