QT += xml
TARGET = ClientSidePlugin
TEMPLATE = lib
CONFIG += debug_and_release build_all
DEFINES += CLIENTSIDEPLUGIN_LIBRARY

INCLUDEPATH += $$PWD/../Node/Core
HEADERS += ClientSidePluginClass.h \
    ClientSidePlugin_global.h
SOURCES += ClientSidePluginClass.cpp
