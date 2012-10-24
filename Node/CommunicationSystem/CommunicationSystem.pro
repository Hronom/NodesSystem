QT       += network

TARGET = CommunicationSystem
TEMPLATE = lib
CONFIG += staticlib qt thread

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH += $$PWD/../Core

HEADERS += NetworkController.h \
    TCPConnection.h \
    CommunicationSystem.h \
    GroupsController.h \
    Group.h \
    Member.h \
    TCPServer.h \
    NetworkRequest.h \
    NetworkReply.h \
    Message.h

SOURCES += NetworkController.cpp \
    TCPConnection.cpp \
    CommunicationSystem.cpp \
    GroupsController.cpp \
    Group.cpp \
    Member.cpp \
    TCPServer.cpp \
    NetworkRequest.cpp \
    NetworkReply.cpp \
    Message.cpp

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
