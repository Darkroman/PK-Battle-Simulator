cmake_minimum_required(VERSION "3.30")

project("PKBattleSimulator")
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_executable(PKBattleSimulator main.cpp ${HEADER_FILES} ${SOURCE_FILES})

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/data
        ${PROJECT_BINARY_DIR}/data
        COMMENT "Copying resources into binary directory")

add_dependencies(PKBattleSimulator copy_resources)