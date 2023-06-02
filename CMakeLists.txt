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

list(APPEND QT_RESOURCES
    resources/resources.qrc
)

set(COMPILE_OPTIONS "-Wall" "-Wextra" "-Werror" "-pedantic" "-fsanitize=undefined")
add_compile_options(${COMPILE_OPTIONS})
add_link_options(${COMPILE_OPTIONS})

add_executable(${PROJECT_NAME} main.cpp ${QT_RESOURCES})
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

add_executable(logic logic.cpp)  # temporary
target_link_libraries(logic
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
