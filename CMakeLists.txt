cmake_minimum_required(VERSION 3.5)

project(api-chain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools svgwidgets REQUIRED)
find_package(Qt6 COMPONENTS SvgWidgets Xml REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)

set(TS_FILES api-chain_zh_CN.ts)

if (APPLE)
    set(CROSSFILES src/mainwindow.mm)
elseif (WIN32)
    set(CROSSFILES src/mainwindow.cpp)
endif()

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.h
        ${CROSSFILES}
        src/mainwindow.cpp
        src/buttons.h
        src/buttons.cpp
        src/input.h
        src/input.cpp
        src/labels.h
        src/labels.cpp
        src/requestspage.h
        src/requestspage.cpp
        src/chainpage.h
        src/chainpage.cpp
        src/combobox.h
        src/combobox.cpp
        src/log.h
        src/log.cpp
        src/constants.h
        src/widgets.h
        src/widgets.cpp
        src/network.h
        src/network.cpp
        resource.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(api-chain
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET api-chain APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(api-chain SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(api-chain
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(api-chain PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::SvgWidgets Qt6::Xml Qt6::Network)


set_target_properties(api-chain PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(api-chain)
endif()
