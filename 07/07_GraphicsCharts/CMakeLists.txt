cmake_minimum_required(VERSION 3.5)

project(07_GraphicsCharts VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        graphicchart.cpp
        graphicchart.h
        #qcustomplot.cpp
        #qcustomplot.h
        #graphic.cpp
        #graphic.h
)

qt_add_executable(07_GraphicsCharts
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)


target_link_libraries(07_GraphicsCharts PRIVATE Qt6::Widgets
                                          Qt6::Charts)

qt_finalize_executable(07_GraphicsCharts)

