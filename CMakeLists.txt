cmake_minimum_required(VERSION 3.16)

project(Inode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Inode
    src/main.cpp
    src/Inode.cpp
    src/get_dir_names.cpp
)

target_link_libraries(Inode PRIVATE Qt6::Widgets)

