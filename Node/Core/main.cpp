#include <QtGui/QApplication>
#include <QTextCodec>
//#include <QTranslator>
#include "MainBridge.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));//установка нужной кодировки для Tr

    QApplication xApp(argc, argv);
    xApp.setApplicationName("Node");
    xApp.setOrganizationName("-X-");
    xApp.setQuitOnLastWindowClosed(false);//отмена закрытия приложения после закрытия последнее окна

    //    QTranslator xTranslator;
    //    xTranslator.load("node_eng", qApp->applicationDirPath() + "/lang");
    //    xApplication.installTranslator(&xTranslator);

    MainBridge xMainBridge;
    xMainBridge.initialize();//инициализация и запуск основного цикла приложения

    return xApp.exec();
}
