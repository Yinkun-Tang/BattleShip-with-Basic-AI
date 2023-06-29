//
// Created by 人之初 on 2021/6/12.
//

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H
#include "BlankBoard.h"
#include <vector>
#include <string>
#include <utility>
class Player{
public:
    virtual void SetPlacementBoardAndFiringBoard(BlankBoard& InitialBoard) = 0;
    virtual void PrintOutPlacementBoard() = 0;
    virtual void PrintOutFiringBoard() = 0;
    virtual std::vector<std::pair<int, int>> GetVectorOfSelfValidCoordinates() = 0;
    virtual std::string GetName() = 0;
    virtual std::vector<std::vector<std::string>> GetSelfBoard() = 0;
    virtual std::vector<std::vector<std::string>> GetOpponentFireBoard() = 0;
};
#endif //BATTLESHIP_PLAYER_H
