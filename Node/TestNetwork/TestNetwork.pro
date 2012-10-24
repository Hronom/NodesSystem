QT       += core gui network

TARGET = TestNetwork
TEMPLATE = app qt

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../../Node-build-desktop/CommunicationSystem/debug -lCommunicationSystem
    PRE_TARGETDEPS += $$PWD/../../Node-build-desktop/CommunicationSystem/debug/libCommunicationSystem.a
}

CONFIG(release, debug|release) {
    LIBS += -L$$PWD/../../Node-build-desktop/CommunicationSystem/release -lCommunicationSystem
    PRE_TARGETDEPS += $$PWD/../../Node-build-desktop/CommunicationSystem/release/libCommunicationSystem.a
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += $$PWD/../CommunicationSystem \
                $$PWD/../Core

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui
