cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

add_executable(minesweeper main.cpp)
target_link_libraries(minesweeper
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
