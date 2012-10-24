#include "TrayIcon.h"
#include <QApplication>

TrayIcon::TrayIcon(QObject *parent) : QObject(parent)
{
    //�������� ������������ ����
    mSystemTrayIconMenu = new QMenu();

    mSettingsAction = new QAction(tr("������������"), mSystemTrayIconMenu);
    connect(mSettingsAction,SIGNAL(triggered()),this,SLOT(on_settingsAction_triggered()));

    mAboutQtAction = new QAction(tr("��� Qt"), mSystemTrayIconMenu);
    connect(mAboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));

    mExitAction = new QAction(tr("�����"), mSystemTrayIconMenu);
    connect(mExitAction,SIGNAL(triggered()),this,SLOT(on_exitAction_triggered()));

    mSeparatorAction = mSystemTrayIconMenu->addSeparator();
    mSystemTrayIconMenu->addAction(mSettingsAction);
    mSystemTrayIconMenu->addAction(mAboutQtAction);
    mSystemTrayIconMenu->addAction(mExitAction);

    //�������� ������ � ����
    mSystemTrayIcon = new QSystemTrayIcon();
    mSystemTrayIcon->setContextMenu(mSystemTrayIconMenu);
    mSystemTrayIcon->setIcon(QIcon(":/Icons/MainProgramPicture"));
    mSystemTrayIcon->show();
}

TrayIcon::~TrayIcon()
{
    if(mSystemTrayIcon != NULL)
    {
        delete mSystemTrayIcon;
        mSystemTrayIcon = NULL;
    }

    if(mSystemTrayIconMenu != NULL)
    {
        delete mSystemTrayIconMenu;
        mSystemTrayIconMenu = NULL;
    }
}

void TrayIcon::insertContextMenuAction(QAction *xAction)
{
    mSystemTrayIconMenu->insertAction(mSeparatorAction, xAction);
}

void TrayIcon::on_settingsAction_triggered()
{
    emit this->settingsAction_triggered();
}

void TrayIcon::on_exitAction_triggered()
{
    qApp->exit();
}
