cmake_minimum_required(VERSION 3.5)

project(07_GraphicsCustomPlot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Widgets PrintSupport REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        graphic.cpp
        graphic.h
)

qt_add_executable(07_GraphicsCustomPlot
	MANUAL_FINALIZATION
	${PROJECT_SOURCES}
)
#Необходимо при использовании динамической библиотеки QCustomPlot
add_compile_definitions(QCUSTOMPLOT_USE_LIBRARY)
#Добавляем путь где искать библиотеки
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(07_GraphicsCustomPlot PRIVATE Qt6::Widgets
                                                    Qt6::PrintSupport
                                                    qcustomplot2.dll)

qt_finalize_executable(07_GraphicsCustomPlot)

