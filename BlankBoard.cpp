//
// Created by 人之初 on 2021/6/12.
//

#include "BlankBoard.h"
BlankBoard::BlankBoard(const int &row, const int &col, const int &NumOfShip, std::map<std::string, int>& ShipInfo) {
    this->row = row;
    this->col = col;
    this->NumOfShip = NumOfShip;
    this->ShipInfo = ShipInfo;
    for(int i = 0; i < this->row + 1; ++i){
        std::vector<std::string> temp;
        for(int j = 0; j < this->col + 1; ++j){
            temp.push_back("*");
        }
        this->initial_board.push_back(temp);
    }
    this->initial_board.at(0).at(0) = " ";
    for(int i = 1; i < col + 1; ++i){
        this->initial_board.at(0).at(i) = std::to_string(i-1);
    }
    for(int i = 1; i < row + 1; ++i){
        this->initial_board.at(i).at(0) = std::to_string(i-1);
    }
}

std::map<std::string, int> BlankBoard::GetShipInfo() {
    return ShipInfo;
}

int BlankBoard::GetColNumber() {
    return col;
}

int BlankBoard::GetRowNumber() {
    return row;
}

int BlankBoard::GetShipNum() {
    return NumOfShip;
}

std::vector<std::vector<std::string>> BlankBoard::Get_Initial_Board() {
    return initial_board;
}