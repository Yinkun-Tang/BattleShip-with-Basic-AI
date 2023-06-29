//
// Created by 人之初 on 2021/6/12.
//

#include "HumanPlayer.h"
#include <iostream>
#include <utility>
#include <cctype>
HumanPlayer::HumanPlayer(int PlayerOrder, BlankBoard& InitialBoard) {
    this->Player_Order = PlayerOrder;
    std::cout << "Player " << Player_Order << " please enter your name: ";
    std::cin >> this->Player_Name;
    this->Self_Board = InitialBoard.Get_Initial_Board();
    this->row = InitialBoard.GetRowNumber();
    this->col = InitialBoard.GetColNumber();
}

void HumanPlayer::SetPlacementBoardAndFiringBoard(BlankBoard& InitialBoard) {
    this->PrintOutPlacementBoard();
    for (const auto &pairs : InitialBoard.GetShipInfo()) {
        std::string DirectionChoice;
        std::string what_is_left;
        int HorizontalCoordinateChoice = -1;
        int VerticalCoordinateChoice = -1;
        int CheckInput = 0;
        while (CheckInput == 0) {
            DirectionChoice = "?";
            HorizontalCoordinateChoice = -1;
            VerticalCoordinateChoice = -1;
            std::cout << this->Player_Name << ", do you want to place " << pairs.first << " horizontally or vertically?"
                      << std::endl;
            std::cout << "Enter h for horizontal or v for vertical" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> DirectionChoice;
            for (auto &character : DirectionChoice) {
                if (isalpha(character)) {
                    character = tolower(character);
                }
            }
            if ((DirectionChoice != "h") && (DirectionChoice != "v")) {
                CheckInput = 0;
            } else if ((DirectionChoice == "h") || (DirectionChoice == "v")) {
                CheckInput = 1;
            }
            std::getline(std::cin, what_is_left);
            for (auto &character : what_is_left) {
                if (not isspace(character)) {
                    CheckInput = 0;
                }
            }
            what_is_left.clear();
            std::cin.clear();
            if (CheckInput != 0) {
                std::cout << this->Player_Name << ", enter the row and column you want to place " << pairs.first
                          << ", which is " << pairs.second << " long, at with a space in between row and col: ";
                std::cin >> HorizontalCoordinateChoice >> VerticalCoordinateChoice;
                getline(std::cin, what_is_left);
                for (auto &character : what_is_left) {
                    if (not isspace(character)) {
                        CheckInput = 0;
                    }
                }
                if (HorizontalCoordinateChoice < 0) {
                    CheckInput = 0;
                }
                if (VerticalCoordinateChoice < 0) {
                    CheckInput = 0;
                }
                std::cin.clear();
                if (CheckInput != 0) {
                    if (DirectionChoice == "h") {
                        if (!(HorizontalCoordinateChoice < InitialBoard.GetRowNumber()) ||
                            !(VerticalCoordinateChoice + pairs.second - 1 < InitialBoard.GetColNumber())) {
                            CheckInput = 0;
                        }
                    } else if (DirectionChoice == "v") {
                        if (!(HorizontalCoordinateChoice + pairs.second - 1 < InitialBoard.GetRowNumber()) ||
                            !(VerticalCoordinateChoice < InitialBoard.GetColNumber())) {
                            CheckInput = 0;
                        }
                    }
                    std::cin.clear();
                    if (CheckInput != 0) {
                        if (DirectionChoice == "h") {
                            for (int i = 0; i < pairs.second; ++i) {
                                if (this->Self_Board.at(HorizontalCoordinateChoice + 1).at(
                                        VerticalCoordinateChoice + 1 + i) != "*") {
                                    CheckInput = 0;
                                }
                            }
                        } else if (DirectionChoice == "v") {
                            for (int i = 0; i < pairs.second; ++i) {
                                if (this->Self_Board.at(HorizontalCoordinateChoice + 1 + i).at(
                                        VerticalCoordinateChoice + 1) != "*") {
                                    CheckInput = 0;
                                }
                            }
                        }
                        std::cin.clear();
                        if (CheckInput != 0) {
                            if (DirectionChoice == "h") {
                                for (int i = 0; i < pairs.second; ++i) {
                                    this->Self_Board.at(HorizontalCoordinateChoice + 1).at(
                                            VerticalCoordinateChoice + 1 + i) = pairs.first;
                                }
                            } else if (DirectionChoice == "v") {
                                for (int i = 0; i < pairs.second; ++i) {
                                    this->Self_Board.at(HorizontalCoordinateChoice + 1 + i).at(
                                            VerticalCoordinateChoice + 1) = pairs.first;
                                }
                            }
                            this->PrintOutPlacementBoard();
                            std::cin.clear();
                        }
                    }
                }
            }
            std::cin.clear();
        }
    }
    this->Opponent_Fire_Board = InitialBoard.Get_Initial_Board();
}

void HumanPlayer::PrintOutPlacementBoard() {
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

void HumanPlayer::PrintOutFiringBoard() {
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

std::vector<std::pair<int, int>> HumanPlayer::GetVectorOfSelfValidCoordinates() {
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

std::string HumanPlayer::GetName() {
    return this->Player_Name;
}

std::vector<std::vector<std::string>> HumanPlayer::GetSelfBoard() {
    return this->Self_Board;
}

std::vector<std::vector<std::string>> HumanPlayer::GetOpponentFireBoard() {
    return this->Opponent_Fire_Board;
}