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


add_library(${PROJECT_NAME} SHARED)

target_sources(${PROJECT_NAME}
    PRIVATE
    "include/h1.hpp"
    "include/task.hpp"
)


target_include_directories(${PROJECT_NAME}
    PUBLIC
    # where top-level project will look for the library's public headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    # where external projects will look for the library's public headers
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)


include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
