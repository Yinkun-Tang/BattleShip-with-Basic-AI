//
// Created by 人之初 on 2021/6/12.
//

#ifndef BATTLESHIP_BLANKBOARD_H
#define BATTLESHIP_BLANKBOARD_H
#include <string>
#include <map>
#include <vector>
class BlankBoard{
public:
    BlankBoard(const int& row, const int& col, const int& NumOfShip, std::map<std::string, int>& ShipInfo);
    std::map<std::string, int> GetShipInfo();
    std::vector<std::vector<std::string>> Get_Initial_Board();
    int GetRowNumber();
    int GetColNumber();
    int GetShipNum();
private:
    int row;
    int col;
    int NumOfShip;
    std::map<std::string, int> ShipInfo;
    std::vector<std::vector<std::string>> initial_board;
};
#endif //BATTLESHIP_BLANKBOARD_H
