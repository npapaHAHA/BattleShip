
cmake_minimum_required(VERSION 3.10)
project(battleship228)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
        main.cpp
        CommandParser.cpp
        Game.cpp
        Board.cpp
        Ship.cpp
        Player.cpp
        OrderedStrategy.cpp
        CustomStrategy.cpp
        Utils.cpp
)

set(HEADERS
        CommandParser.h
        Game.h
        Board.h
        Ship.h
        Player.h
        Strategy.h
        OrderedStrategy.h
        CustomStrategy.h
        Utils.h
)

add_executable(battleship228 ${SOURCES} ${HEADERS})
