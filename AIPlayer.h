//
// Created by 人之初 on 2021/6/12.
//

#ifndef BATTLESHIP_AIPLAYER_H
#define BATTLESHIP_AIPLAYER_H
#include "Player.h"
#include <random>
class AIPlayer : public Player {
public:
    static std::mt19937 RandomNumberGenerator;
    virtual void SetPlacementBoardAndFiringBoard(BlankBoard& InitialBoard) override = 0;
    virtual void PrintOutPlacementBoard() override = 0;
    virtual void PrintOutFiringBoard() override = 0;
    virtual std::vector<std::pair<int, int>> GetVectorOfSelfValidCoordinates() override = 0;
    virtual std::string GetName() = 0;
    virtual std::vector<std::vector<std::string>> GetSelfBoard() override = 0;
    virtual std::vector<std::vector<std::string>> GetOpponentFireBoard() override = 0;
};
#endif //BATTLESHIP_AIPLAYER_H
