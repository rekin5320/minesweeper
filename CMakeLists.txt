cmake_minimum_required(VERSION 3.24)
project(minesweeper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

list(APPEND QT_LIBS
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

list(APPEND QT_RESOURCES
    resources/resources.qrc
)

set(COMPILE_OPTIONS "-Wall" "-Wextra" "-Werror" "-pedantic" "-fsanitize=undefined")
add_compile_options(${COMPILE_OPTIONS})
add_link_options(${COMPILE_OPTIONS})

add_library(minesweeper_lib SHARED
    position.hpp position.cpp
    tile.hpp tile.cpp
    board.hpp board.cpp
    game.hpp game.cpp
    emoji.h emoji.cpp
)
target_link_libraries(minesweeper_lib ${QT_LIBS})

add_executable(${PROJECT_NAME} ${QT_RESOURCES} main.cpp)
target_link_libraries(${PROJECT_NAME} ${QT_LIBS} minesweeper_lib)

add_executable(test tests/test_root.cpp tests/test_tile.cpp tests/test_board.cpp tests/test_game.cpp)
target_link_libraries(test ${QT_LIBS} minesweeper_lib)
