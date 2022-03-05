string(REGEX REPLACE ".+/" "" NAME ${CMAKE_CURRENT_SOURCE_DIR})
message(${NAME})
file(GLOB SRC_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)
add_executable(${NAME} WIN32 ${SRC_LIST})

target_link_libraries(${NAME} ${REQUIRED_LIBS_QUALIFIED} DataBase yaml-cpp User)


