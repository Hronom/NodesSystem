#ifndef INODE_H
#define INODE_H

#include <QObject>
#include <QList>

class QAction;
class QFile;

class NodeInfo;
class PluginInfo;

class INode: public QObject
{
    Q_OBJECT
public:
    virtual void setAutoStartProgram(bool xAutoStartProgram) = 0;
    virtual bool isProgramAutoStart() = 0;
    virtual void closeApp() = 0;//�������� ��������� ������
    virtual void findNodes(quint16 xNodePort) = 0;//�������� ��������� ��������� �� ��� ������� �� �������� ���� UDP
    virtual void addNode(QString xNodeIP, quint16 xNodePort) = 0;//���������� ���� �� ���������� ���� � ����� TCP
    virtual void removeNode(QString xConnectionUuid) = 0;//�������� ���� �� ���������� ����������� ������
    virtual QList<NodeInfo> getHostAddresses() = 0;
    virtual QList<NodeInfo> getFoundedNodes() = 0;//��������� ������ ����� ������ �������� ���� ������� ������ ����
    virtual NodeInfo getNodeInfo(QString xConnectionUuid) = 0;
    virtual void sendCommand(QString xConnectionUuid, QString xMessageType, QString xCommand, QString xPluginName) = 0;
    virtual void sendFile(QString xConnectionUuid, QString xPluginName, QString xFilePath) = 0;
    virtual quint16 getBindPort() = 0;
    virtual void setBindPort(quint16 xPort) = 0;
    virtual bool getUDPPortStatus() = 0;
    virtual bool getTCPPortStatus() = 0;
    virtual QList<PluginInfo> getLoadedPluginsList() = 0;
    virtual void reloadPlugins() = 0;
    virtual void addContextMenuItem(QAction *xAction) = 0;

signals:
    void nodeAdded(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort);
    void nodeRemoved(QString xConnectionUuid);
    void nodeOnline(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort);
    void nodeOffline(QString xConnectionUuid, QString xPeerNodeName, QString xPeerNodeIP, quint16 xPeerNodePort);
    void UDPBindStateChanged(bool xBindState);//������ ���������� ��������� ������������� UDP �����
    void TCPBindStateChanged(bool xBindState);//������ ���������� ��������� ������������� TCP �����
    void mainAppAboutToQuit();//������ ����������� � ��� ��� ������� ���������� ������������
};

Q_DECLARE_INTERFACE(INode,"INode");

#endif // INODE_H
