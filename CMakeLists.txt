cmake_minimum_required(VERSION 3.15)
project(BattleShip)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip main.cpp BlankBoard.cpp BlankBoard.h Player.cpp Player.h HumanPlayer.cpp HumanPlayer.h AIPlayer.cpp AIPlayer.h CheatingAI.cpp CheatingAI.h RandomAI.cpp RandomAI.h SearchAndDestroyAI.cpp SearchAndDestroyAI.h Game.cpp Game.h)