#-------------------------------------------------
#
# Project created by QtCreator 2011-02-14T18:23:28
#
#-------------------------------------------------

TARGET = VisualController
TEMPLATE = lib
CONFIG += staticlib

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += $$PWD/../Core

HEADERS += VisualController.h \
    NodeSettingsForm.h \
    TrayIcon.h

SOURCES += VisualController.cpp \
    NodeSettingsForm.cpp \
    TrayIcon.cpp

RESOURCES += Resources.qrc

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

FORMS += \
    NodeSettingsForm.ui
