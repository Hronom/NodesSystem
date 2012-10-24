#ifndef IPLUGIN_H
#define IPLUGIN_H

#include <QThread>
#include "INode.h"

class IPlugin: public QObject
{
public:
    virtual QString getPluginName() = 0;//получение имени плагина
    virtual QString getPluginVersion() = 0;//получение версии плагина
    virtual QString getPluginAuthor() = 0;//получение автора плагина

    virtual void initializePlugin(INode* xINode) = 0;//инциализация плагина
    virtual void executeCommand(QString xConnectionUuid, QString xCommand) = 0;//выполнение команды
    virtual void receiveFile(QString xConnectionUuid, QString xPluginName, QString xFilePath) = 0;
    virtual void closePlugin() = 0;//закрытие плагина
};

Q_DECLARE_INTERFACE(IPlugin,"IPlugin");

#endif // IPLUGIN_H
