#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T09:04:28
# Project created by QtCreator 2017-04-10T21:51:24
#
#-------------------------------------------------

QT += core gui qml quick quickwidgets positioning
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT       += core gui
INCLUDEPATH += $$PWD/../DroneManager

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpyC
TEMPLATE = app

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../bin/plugins -ldronemanagerd
    TARGET = SpyCd
} else {
    LIBS += -L$$PWD/../bin/plugins -ldronemanager
    TARGET = SpyC
}

unix {
    DESTDIR = ../bin
    MOC_DIR = ../moc
    OBJECTS_DIR = ../obj
}

win32 {
    DESTDIR = ..\\bin
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

RESOURCES += \
    resources.qrc

HEADERS += \
    defs.h \
    iservice.h \
    pluginloader.h \
    spyc.h \
    droneview.h \
    dronebase.h \
    alert.h \
    waypointmodel.h \
    mastercontroller.h \
    missionplancontroller.h

SOURCES += \
    main.cpp \
    pluginloader.cpp \
    spyc.cpp \
    droneview.cpp \
    dronebase.cpp \
    alert.cpp \
    waypointmodel.cpp \
    mastercontroller.cpp \
    missionplancontroller.cpp

DISTFILES += \
    qml/mapviewer/map/CircleItem.qml \
    qml/mapviewer/map/ImageItem.qml \
    qml/mapviewer/map/MapComponent.qml \
    qml/mapviewer/map/Marker.qml \
    qml/mapviewer/map/MiniMap.qml \
    qml/mapviewer/map/PolygonItem.qml \
    qml/mapviewer/map/PolylineItem.qml \
    qml/mapviewer/map/RectangleItem.qml


