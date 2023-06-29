//
// Created by 人之初 on 2021/6/12.
//

#include "SearchAndDestroyAI.h"
#include <iostream>
SearchAndDestroyAI::SearchAndDestroyAI(int PlayerOrder, BlankBoard &InitialBoard) : RandomAI(PlayerOrder, InitialBoard){
    this->Player_Order = PlayerOrder;
    if(PlayerOrder == 1){
        this->PlayerName = "AI 1";
    } else {
        this->PlayerName = "AI 2";
    }
    this->Self_Board = InitialBoard.Get_Initial_Board();
    this->row = InitialBoard.GetRowNumber();
    this->col = InitialBoard.GetColNumber();
}

void SearchAndDestroyAI::SetPlacementBoardAndFiringBoard(BlankBoard &InitialBoard) {
    for (const auto &pairs : InitialBoard.GetShipInfo()) {
        int DirectionChoice = -1;
        int HorizontalCoordinateChoice = -1;
        int VerticalCoordinateChoice = -1;
        int CheckInput = 0;
        while (CheckInput == 0){
            HorizontalCoordinateChoice = -1;
            VerticalCoordinateChoice = -1;
            std::uniform_int_distribution<int> dist(0, 1);
            DirectionChoice = dist(RandomNumberGenerator);
            if(DirectionChoice == 0){
                std::uniform_int_distribution<int> ForRow(0, row - 1);
                HorizontalCoordinateChoice = ForRow(RandomNumberGenerator);
                std::uniform_int_distribution<int> ForCol(0, col - pairs.second);
                VerticalCoordinateChoice = ForCol(RandomNumberGenerator);
            } else if(DirectionChoice = 1){
                std::uniform_int_distribution<int> ForRow(0, row - pairs.second);
                HorizontalCoordinateChoice = ForRow(RandomNumberGenerator);
                std::uniform_int_distribution<int> ForCol(0, col - 1);
                VerticalCoordinateChoice = ForCol(RandomNumberGenerator);
            }
            CheckInput = 1;
            if (DirectionChoice == 0) {
                for (int i = 0; i < pairs.second; ++i) {
                    if (this->Self_Board.at(HorizontalCoordinateChoice + 1).at(
                            VerticalCoordinateChoice + 1 + i) != "*") {
                        CheckInput = 0;
                    }
                }
            } else if (DirectionChoice == 1) {
                for (int i = 0; i < pairs.second; ++i) {
                    if (this->Self_Board.at(HorizontalCoordinateChoice + 1 + i).at(
                            VerticalCoordinateChoice + 1) != "*") {
                        CheckInput = 0;
                    }
                }
            }
            if (CheckInput != 0) {
                if (DirectionChoice == 0) {
                    for (int i = 0; i < pairs.second; ++i) {
                        this->Self_Board.at(HorizontalCoordinateChoice + 1).at(
                                VerticalCoordinateChoice + 1 + i) = pairs.first;
                    }
                } else if (DirectionChoice == 1) {
                    for (int i = 0; i < pairs.second; ++i) {
                        this->Self_Board.at(HorizontalCoordinateChoice + 1 + i).at(
                                VerticalCoordinateChoice + 1) = pairs.first;
                    }
                }
                std::cout << PlayerName << "'s Board" << std::endl;
                PrintOutPlacementBoard();
                std::cout << std::endl;
            }
        }
    }
    Opponent_Fire_Board = InitialBoard.Get_Initial_Board();
}

void SearchAndDestroyAI::PrintOutPlacementBoard() {
    for(const auto& element : Self_Board){
        std::string for_print;
        for(const auto& item : element){
            for_print += item;
            for_print += " ";
        }
        for_print.pop_back();
        std::cout << for_print << std::endl;
    }
}

void SearchAndDestroyAI::PrintOutFiringBoard() {
    for(const auto& element : Opponent_Fire_Board){
        std::string for_print;
        for(const auto& item : element){
            for_print += item;
            for_print += " ";
        }
        for_print.pop_back();
        std::cout << for_print << std::endl;
    }
}

std::vector<std::pair<int, int>> SearchAndDestroyAI::GetVectorOfSelfValidCoordinates() {
    if(Self_Valid_Board.empty()){
        std::pair<int, int> ValidCoordinate;
        for(int i = 1; i < row + 1; ++i){
            for(int j = 1; j < col + 1; ++j){
                if(Self_Board.at(i).at(j) != "*"){
                    ValidCoordinate = std::make_pair(i - 1 ,j - 1);
                    Self_Valid_Board.push_back(ValidCoordinate);
                }
            }
        }
    }
    return Self_Valid_Board;
}

std::vector<std::pair<int, int>> SearchAndDestroyAI::GenerateOrGetRandomShootList() {
    if(RandomShootList.empty()){
        std::pair<int, int> Coordinate;
        for(int i = 0; i < row; ++i){
            for(int j = 0; j < col; ++j){
                Coordinate = std::make_pair(i,j);
                RandomShootList.push_back(Coordinate);
            }
        }
    }
    return RandomShootList;
}

std::string SearchAndDestroyAI::GetName() {
    return this->PlayerName;
}

std::vector<std::vector<std::string>> SearchAndDestroyAI::GetSelfBoard() {
    return this->Self_Board;
}

std::vector<std::vector<std::string>> SearchAndDestroyAI::GetOpponentFireBoard() {
    return this->Opponent_Fire_Board;
}