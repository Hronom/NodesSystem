#include "SettingsController.h"
#include <QApplication>
#include <QMessageBox>
#include <QDir>

SettingsController::SettingsController()
{
    mIniFileSettings = new QSettings(qApp->applicationDirPath() + "/settings.ini", QSettings::IniFormat);
#ifdef Q_OS_WIN32
    mStartupSettings = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    if(mIniFileSettings->value("AutoStartProgram", false).toBool() != mStartupSettings->contains("Node"))
        this->setAutoStartProgram(mIniFileSettings->value("AutoStartProgram", false).toBool());
#endif
}

SettingsController::~SettingsController()
{
    if(mStartupSettings != NULL)
    {
        delete mStartupSettings;
        mStartupSettings = NULL;
    }

    if(mIniFileSettings != NULL)
    {
        delete mIniFileSettings;
        mIniFileSettings = NULL;
    }
}

void SettingsController::setAutoStartProgram(bool xAutoStartProgram)
{
#ifdef Q_OS_WIN32
    //-1-Изменяем запись в реестре если нужно
    if(mStartupSettings->contains("Node") != xAutoStartProgram)
    {
        if(xAutoStartProgram == true)
            mStartupSettings->setValue("Node", QDir().toNativeSeparators(qApp->applicationFilePath()));
        else
            mStartupSettings->remove("Node");

        if(mStartupSettings->status() == QSettings::AccessError)
            QMessageBox::warning(0, "Node", tr("Невозможно изменить ключ в реестре"));
    }
    //-1-
#endif

    //-2-Изменяем запись в файле если нужно
    if(mIniFileSettings->value("AutoStartProgram", false).toBool() != xAutoStartProgram)
    {
        mIniFileSettings->setValue("AutoStartProgram", xAutoStartProgram);
        mIniFileSettings->sync();

        if(mIniFileSettings->status() == QSettings::AccessError)
            QMessageBox::warning(0, "Node",tr("Невозможно изменить файл настроек"));
    }
    //-2-
}

bool SettingsController::isProgramAutoStart()
{
#ifdef Q_OS_WIN32
    return mStartupSettings->contains("Node");
#endif
}

void SettingsController::setBindPort(quint16 xBindPort)
{
    mIniFileSettings->setValue("BindPort", xBindPort);
    mIniFileSettings->sync();

    if(mIniFileSettings->status() == QSettings::AccessError)
        QMessageBox::warning(0, "Node",tr("Невозможно изменить файл настроек"));
}

quint16 SettingsController::getBindPort()
{
    return mIniFileSettings->value("BindPort", 9050).toInt();
}
