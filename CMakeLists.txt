cmake_minimum_required(VERSION 3.19)
project(ACPS)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(CMAKE_PREFIX_PATH E:/QT/5.15.2/mingw81_64)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if (CMAKE_BUILD_TYPE STREQUAL Release)

    ADD_DEFINITIONS(-DNDEBUG)

endif ()

link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)


file(GLOB MOD_LIST ${CMAKE_CURRENT_SOURCE_DIR}/modules/*)
include_directories()
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
        ${MOD_LIST}
)


foreach (MOD ${MOD_LIST})
    add_subdirectory(${MOD})
    string(REGEX REPLACE ".+/" "" MOD ${MOD})
    list(APPEND MODULES ${MOD})
endforeach (MOD)

#TODO:SDK Develop
#add_subdirectory(SDK/CXX/extension)

file(GLOB EXT_LIST ${CMAKE_CURRENT_SOURCE_DIR}/extension/CXX/*)

foreach (EXT ${EXT_LIST})
    message(${EXT})
    add_subdirectory(${EXT})

endforeach ()

file(GLOB UI_LIST ${CMAKE_CURRENT_SOURCE_DIR}/UI/*.*)
#
#add_library(UI SHARED ${UI_LIST})
#list(APPEND MODULES UI)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/UI)

add_executable(${PROJECT_NAME} WIN32
        app/Main/main.cpp
        app/Main/Application.h
        app/Main/Application.cpp
        ${UI_LIST}
        )
add_executable(initEnv WIN32 app/init.cpp)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
            ARGS -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR}/bin
            COMMENT "copy dynamic lib dir to workdir to run")
endif ()

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} ${MODULES})

add_executable(extManagerTest test/extManagerTest.cpp)

target_link_libraries(extManagerTest ExtManager)