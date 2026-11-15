cmake_minimum_required(VERSION 3.16)
project(MapNavigation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

set(PROJECT_SOURCES
    main_gui.cpp
    MainWindow.cpp
    MainWindow.h
    MapCanvas.cpp
    MapCanvas.h
    Graph.cpp
    Graph.h
    MinHeap.cpp
    MinHeap.h
    Location.h
)

add_executable(MapNavigation ${PROJECT_SOURCES})

target_link_libraries(MapNavigation PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
)
