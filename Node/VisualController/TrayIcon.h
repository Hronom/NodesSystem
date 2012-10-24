#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QMenu>
#include <QSystemTrayIcon>

class TrayIcon : public QObject
{
    Q_OBJECT

private:
    QSystemTrayIcon *mSystemTrayIcon;

    QMenu *mSystemTrayIconMenu;
    QAction *mSeparatorAction;
    QAction *mSettingsAction;
    QAction *mAboutQtAction;
    QAction *mExitAction;

public:
    explicit TrayIcon(QObject *xParent = 0);
    ~TrayIcon();

    void insertContextMenuAction(QAction *xAction);

signals:
    void settingsAction_triggered();

private slots:
    void on_settingsAction_triggered();
    void on_exitAction_triggered();
};

#endif // TRAYICON_H
