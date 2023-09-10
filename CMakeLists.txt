cmake_minimum_required(VERSION 3.22.1)

project(ncurses)

# Set C++ Standard and export compile commands for clangd
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_DL_LIBS} "-lncurses")
