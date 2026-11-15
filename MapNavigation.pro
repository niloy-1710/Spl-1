QT += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = MapNavigation
TEMPLATE = app

SOURCES += \
    main_gui.cpp \
    MainWindow.cpp \
    Graph.cpp \
    MinHeap.cpp

HEADERS += \
    MainWindow.h \
    Graph.h \
    MinHeap.h \
    Location.h

