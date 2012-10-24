QT += xml
TARGET = ServerSidePlugin
TEMPLATE = lib
CONFIG += plugin debug_and_release build_all
DEFINES += SERVERSIDEPLUGIN_LIBRARY

INCLUDEPATH += $$PWD/../Node/Core
HEADERS += ServerSidePluginClass.h \
    MainForm.h \
    InstalledProgramsForm.h
SOURCES += ServerSidePluginClass.cpp \
    MainForm.cpp \
    InstalledProgramsForm.cpp
FORMS += MainForm.ui \
    InstalledProgramsForm.ui

symbian {
    load(data_caging_paths)
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE212739A
    TARGET.CAPABILITY = NetworkServices TCB
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ServerSidePlugin.dll
    #addFiles.path = !:/sys/bin
    addFiles.path = $$QT_PLUGINS_BASE_DIR/Node/ServerSidePlugin
    DEPLOYMENT += addFiles
}
