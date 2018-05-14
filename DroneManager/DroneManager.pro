#-------------------------------------------------
#
# Project created by QtCreator 2018-04-07T19:38:20
#
#-------------------------------------------------

QT += gui positioning

TARGET = DroneManager
TEMPLATE = lib

DEFINES += DRONEMANAGER_LIBRARY
INCLUDEPATH += $$PWD/../plugin

CONFIG(debug, debug|release) {
    TARGET = dronemanagerd
} else {
    TARGET = dronemanager
}

unix {
    DESTDIR = ../bin/plugins
    MOC_DIR = ../moc
    OBJECTS_DIR = ../obj
}

win32 {
    DESTDIR = ..\\bin\\plugins
    MOC_DIR = ..\\moc
    OBJECTS_DIR = ..\\obj
}

unix {
    QMAKE_CLEAN *= $$DESTDIR/*$$TARGET*
    QMAKE_CLEAN *= $$MOC_DIR/*moc_*
    QMAKE_CLEAN *= $$OBJECTS_DIR/*.o*
}

win32 {
    QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
    QMAKE_CLEAN *= $$MOC_DIR\\*moc_*
    QMAKE_CLEAN *= $$OBJECTS_DIR\\*.o*
}

SOURCES += \
    dronemanager.cpp \
    flightsimulator.cpp \
    drone.cpp \
    batterysimulator.cpp \
    gpssimulator.cpp \
    basesimulator.cpp \
    waypoint.cpp

HEADERS +=\
    ibaseplugin.h \
    dronemanager.h \
    drone_manager_global.h \
    flightsimulator.h \
    drone.h \
    batterysimulator.h \
    gpssimulator.h \
    basesimulator.h \
    waypoint.h

