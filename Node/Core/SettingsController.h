#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H

#include <QObject>
#include <QSettings>

class SettingsController : public QObject
{
    Q_OBJECT
private:
    QSettings *mIniFileSettings;
    QSettings *mStartupSettings;

public:
    SettingsController();
    ~SettingsController();

    void setAutoStartProgram(bool xAutoStartProgram);
    bool isProgramAutoStart();
    void setBindPort(quint16 xBindPort);
    quint16 getBindPort();
};

#endif // SETTINGSCONTROLLER_H
