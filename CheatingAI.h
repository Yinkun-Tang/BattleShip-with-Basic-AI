//
// Created by 人之初 on 2021/6/12.
//

#ifndef BATTLESHIP_CHEATINGAI_H
#define BATTLESHIP_CHEATINGAI_H
#include "AIPlayer.h"
class CheatingAI : public AIPlayer{
public:
    CheatingAI(int PlayerOrder, BlankBoard& InitialBoard);
    virtual void SetPlacementBoardAndFiringBoard(BlankBoard& InitialBoard) override;
    virtual void PrintOutPlacementBoard() override;
    virtual void PrintOutFiringBoard() override;
    virtual std::vector<std::pair<int, int>> GetVectorOfSelfValidCoordinates() override;
    virtual std::string GetName() override;
    virtual std::vector<std::vector<std::string>> GetSelfBoard() override;
    virtual std::vector<std::vector<std::string>> GetOpponentFireBoard() override;
private:
    std::string Player_Name;
    int Player_Order;
    std::vector<std::vector<std::string>> Self_Board;
    std::vector<std::vector<std::string>> Opponent_Fire_Board;
    std::vector<std::pair<int, int>> Self_Valid_Board;
    int row;
    int col;
};
#endif //BATTLESHIP_CHEATINGAI_H
