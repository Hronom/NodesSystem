#include <QtGui/QApplication>
#include <QTextCodec>
//#include <QTranslator>
#include "MainBridge.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));//��������� ������ ���������
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));//��������� ������ ���������
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));//��������� ������ ��������� ��� Tr

    QApplication xApp(argc, argv);
    xApp.setApplicationName("Node");
    xApp.setOrganizationName("-X-");
    xApp.setQuitOnLastWindowClosed(false);//������ �������� ���������� ����� �������� ��������� ����

    //    QTranslator xTranslator;
    //    xTranslator.load("node_eng", qApp->applicationDirPath() + "/lang");
    //    xApplication.installTranslator(&xTranslator);

    MainBridge xMainBridge;
    xMainBridge.initialize();//������������� � ������ ��������� ����� ����������

    return xApp.exec();
}
