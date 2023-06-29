//
// Created by 人之初 on 2021/6/12.
//

#ifndef BATTLESHIP_SEARCHANDDESTROYAI_H
#define BATTLESHIP_SEARCHANDDESTROYAI_H
#include "Player.h"
#include "AIPlayer.h"
#include "RandomAI.h"
class SearchAndDestroyAI : public RandomAI{
public:
    SearchAndDestroyAI(int PlayerOrder, BlankBoard& InitialBoard);
    void SetPlacementBoardAndFiringBoard(BlankBoard& InitialBoard);
    void PrintOutPlacementBoard();
    void PrintOutFiringBoard();
    std::vector<std::pair<int, int>> GetVectorOfSelfValidCoordinates();
    std::vector<std::pair<int, int>> GenerateOrGetRandomShootList();
    virtual std::string GetName();
    virtual std::vector<std::vector<std::string>> GetSelfBoard() override;
    virtual std::vector<std::vector<std::string>> GetOpponentFireBoard() override;
private:
    std::string PlayerName;
    int Player_Order;
    std::vector<std::vector<std::string>> Self_Board;
    std::vector<std::vector<std::string>> Opponent_Fire_Board;
    std::vector<std::pair<int, int>> Self_Valid_Board;
    std::vector<std::pair<int, int>> RandomShootList;
    int row;
    int col;
};
#endif //BATTLESHIP_SEARCHANDDESTROYAI_H
