cmake_minimum_required(VERSION 3.5)

project(3DViewer_2-0 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui  OpenGLWidgets Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui OpenGLWidgets Widgets)

include_directories(
    ./
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt6Gui_INCLUDE_DIRS}
    ${Qt5OpenGLWidgets_INCLUDE_DIRS}
    ${Qt6OpenGLWidgets_INCLUDE_DIRS}
)

add_compile_options(-Wall -Werror -Wextra)

set(MODEL_SOURCES
    model/processors/obj_parser.cc
    model/processors/primitive_builder.cc
    model/processors/transform_processor.cc
    model/entity.cc
    model/scene.cc
    shaders/shader_pool.cc
)

set(CONTROLLER_SOURCES
    controller/application_controller.cc
    )

set(PROJECT_SOURCES
        main.cc
        resources/shaders.qrc
        view/ui/main_window.cc
        view/ui/main_window.ui
        view/ui/main_window.h
        view/ui/settings_window.h
        view/ui/settings_window.cc
        view/ui/settings_window.ui
        view/render/renderer.cc
        view/render/drawable.cc
        view/render/wireframe_edge.cc
        view/render/wireframe_edge.cc
        view/render/render_strategy.cc
        view/render/vertex_round.cc
        view/render/vertex_square.cc
        ${CONTROLLER_SOURCES}
        ${MODEL_SOURCES}
)

set(TEST_SOURCES tests/3DViewer_v2_tests.cc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer_2-0
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        config.ini
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer_2-0 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer_2-0 SHARED
            ${PROJECT_SOURCES}
            config.ini
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer_2-0
            ${PROJECT_SOURCES} config.ini
        )
    endif()
endif()

add_library(viewer_model ${MODEL_SOURCES})

target_link_libraries(3DViewer_2-0 PRIVATE viewer_model Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::Widgets )

set_target_properties(3DViewer_2-0 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    RESOURCE config.ini
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests viewer_model Qt${QT_VERSION_MAJOR}::Gui GTest::gtest_main)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer_2-0)
endif()
