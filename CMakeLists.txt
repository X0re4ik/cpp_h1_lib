cmake_minimum_required(VERSION 3.22)

project(H1 VERSION 1.0 LANGUAGES CXX)

string(ASCII 27 Esc)
set(COLOR_RESET "${Esc}[0m")
set(COLOR_RED "${Esc}[31m")
set(COLOR_GREEN "${Esc}[32m")
set(COLOR_YELLOW "${Esc}[33m")
set(COLOR_BLUE "${Esc}[34m")



if(NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(
        STATUS
        "${COLOR_BLUE}${PROJECT_NAME} будет собрана как библиотека [${CMAKE_PROJECT_NAME}]${COLOR_RESET}"
    )
else()
    message(STATUS "${COLOR_BLUE}${PROJECT_NAME} будет собрана, как проект${COLOR_RESET}")
endif()


add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    PRIVATE
    "include/h1.hpp"
    "include/task.hpp"
)


target_include_directories(${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


if(USE_CLANG_FORMAT_CHECK)
    find_program(CLANG_FORMAT_PATH NAMES clang-format-21 REQUIRED)
    message(STATUS "${COLOR_GREEN}Found clang-format: ${CLANG_FORMAT_PATH}${COLOR_RESET}")

    file(GLOB_RECURSE CLANG_FORMAT_SRC CONFIGURE_DEPENDS
        include/*.h
        include/*.cpp
        include/*.hpp
    )

    add_custom_target(clang-format-fix
        COMMAND
        ${CLANG_FORMAT_PATH} -style=file -i ${CLANG_FORMAT_SRC}
        WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}
        COMMENT
        "Formatting ${PROJECT_NAME} with ${CLANG_FORMAT_PATH} ..."
    )

    add_custom_target(clang-format
        COMMAND
        python3.10 run-clang-format.py --clang-format-executable=${CLANG_FORMAT_PATH} --style=file ${CLANG_FORMAT_SRC}
        WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}
        COMMENT
        "Checking format ${PROJECT_NAME} with ${CLANG_FORMAT_PATH} ..."
    )
    add_dependencies(${PROJECT_NAME} clang-format)
endif()

if(USE_CLANG_FORMAT_FIX)
    find_program(CLANG_FORMAT_PATH NAMES clang-format-21 REQUIRED)
    message(STATUS "${COLOR_GREEN}Found clang-format: ${CLANG_FORMAT_PATH}${COLOR_RESET}")

    file(GLOB_RECURSE CLANG_FORMAT_SRC CONFIGURE_DEPENDS
        include/*.h
        include/*.cpp
        include/*.hpp
    )

    add_custom_target(clang-format-fix
        COMMAND
        ${CLANG_FORMAT_PATH} -style=file -i ${CLANG_FORMAT_SRC}
        WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}
        COMMENT
        "Formatting ${PROJECT_NAME} with ${CLANG_FORMAT_PATH} ..."
    )

    add_dependencies(${PROJECT_NAME} clang-format-fix)
endif()

# 
if(USE_CLANG_TIDY)
    find_program(CLANG_TIDY_PATH NAMES clang-tidy-21 REQUIRED)
    file(GLOB_RECURSE CLANG_FORMAT_SRC CONFIGURE_DEPENDS
        include/*.h
        include/*.cpp
        include/*.hpp
    )
    message(STATUS "${COLOR_GREEN}Found clang-tidy: ${CLANG_TIDY_PATH}${COLOR_RESET}")
    set(CLANG_TIDY_COMMAND ${CLANG_TIDY_PATH} "-p=${CMAKE_BINARY_DIR}" "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy" ${CLANG_FORMAT_SRC})
    message(STATUS "${COLOR_GREEN}Clang tidy command: ${CLANG_TIDY_COMMAND}${COLOR_RESET}")
    add_custom_target(
        clang-tidy-check
        COMMAND
        ${CLANG_TIDY_COMMAND}
        WORKING_DIRECTORY
        ${CMAKE_SOURCE_DIR}
        COMMENT
        "Tidy ${PROJECT_NAME} with ${CLANG_FORMAT_PATH} ..."
    )
    add_dependencies(${PROJECT_NAME} clang-tidy-check)
    set_target_properties(
        ${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()