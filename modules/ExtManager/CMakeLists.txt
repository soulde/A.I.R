string(REGEX REPLACE ".+/" "" NAME ${CMAKE_CURRENT_SOURCE_DIR})
message(${NAME})
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.*)

add_library(${NAME} SHARED ${SRC_LIST})

target_link_libraries(${NAME} PathManager)