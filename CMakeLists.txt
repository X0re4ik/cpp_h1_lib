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
