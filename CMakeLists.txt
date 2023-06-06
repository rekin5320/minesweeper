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

add_executable(${PROJECT_NAME} ${QT_RESOURCES} main.cpp position.cpp position.hpp tile.cpp tile.hpp board.cpp board.hpp game.cpp game.hpp)
target_link_libraries(${PROJECT_NAME} ${QT_LIBS})

add_executable(test tests/test_root.cpp position.hpp position.cpp tile.cpp tile.hpp tests/test_tile.cpp board.cpp board.hpp tests/test_board.cpp game.cpp game.hpp tests/test_game.cpp)
target_link_libraries(test ${QT_LIBS})
