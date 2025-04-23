cmake_minimum_required(VERSION 3.5)

project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_resources(resources "resources"
    PREFIX "/"
    FILES
        resources/styles.qss
)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/gameboard.cpp
    src/gameengine.cpp
    src/settingsdialog.cpp
)

set(HEADERS
    include/mainwindow.h
    include/gameboard.h
    include/gameengine.h
    include/settingsdialog.h
)

add_executable(TicTacToe ${SOURCES} ${HEADERS})

target_link_libraries(TicTacToe PRIVATE Qt6::Widgets)

target_include_directories(TicTacToe PRIVATE include)

install(TARGETS TicTacToe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)