QT       += core gui network
TARGET = Node
#VERSION = 0.3.0
TEMPLATE = app qt
#CONFIG += debug_and_release build_all

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../Node-build-desktop/CommunicationSystem/debug -lCommunicationSystem
    LIBS += -L$$PWD/../../Node-build-desktop/VisualController/debug -lVisualController
}

CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../../Node-build-desktop/CommunicationSystem/release -lCommunicationSystem
    LIBS += -L$$PWD/../../Node-build-desktop/VisualController/release -lVisualController
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += $$PWD/../CommunicationSystem \
    $$PWD/../VisualController

HEADERS += INode.h \
    IPlugin.h \
    PluginsController.h \
    PlatformFunctions.h \
    SettingsController.h \
    NodeInfo.h \
    PluginInfo.h \
    MainBridge.h
SOURCES += main.cpp \
    PluginsController.cpp \
    SettingsController.cpp \
    MainBridge.cpp
RC_FILE = Node_resource.rc
TRANSLATIONS = node_eng.ts \
    node_ukr.ts

CODEC = Windows-1251
CODECFORSRC = Windows-1251

symbian {
    ICON = $$PWD/Resources/puzzle.svg
    TARGET.UID3 = 0xE1C4EA2E
    TARGET.CAPABILITY += NetworkServices TCB
    #TARGET.EPOCSTACKSIZE = 0x14000
    #TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
