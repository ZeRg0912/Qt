cmake_minimum_required(VERSION 3.14)

project(HW-02 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)

add_executable(HW-02
  main.cpp
  header.h
)
target_link_libraries(HW-02 PRIVATE
                                    Qt${QT_VERSION_MAJOR}::Core
                                    Qt${QT_VERSION_MAJOR}::Sql
                                    Qt${QT_VERSION_MAJOR}::Network)

install(TARGETS HW-02
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
