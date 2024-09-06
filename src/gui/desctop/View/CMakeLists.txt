cmake_minimum_required(VERSION 3.5)

#set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/13.2.0/bin/g++-13")

project(View VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        view.cpp
        view.h
        view.ui
        ../../../brick_game/tetris/controller.h
        ../../../brick_game/tetris/controller.cpp
        ../../../brick_game/tetris/tetris.h
        ../../../brick_game/tetris/tetris.cpp
        ../../../brick_game/tetris/allShapes.h
        ../../../brick_game/tetris/declarations.h
        ../../../brick_game/tetris/model.h
        ../../../brick_game/snake/snake.h
        ../../../brick_game/snake/snake.cpp
        ../../../brick_game/snake/declarations.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(View
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET View APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(View SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(View
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(View PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(View PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(View)
endif()
