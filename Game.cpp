//
// Created by 人之初 on 2021/6/12.
//

#include "Game.h"
Game::Game(int GameChoice, int PossibleAIChoice1, int PossibleAIChoice2, BlankBoard &InitialBoard) {
    this->GameChoice = GameChoice;
    this->PossibleAIChoice1 = PossibleAIChoice1;
    this->PossibleAIChoice2 = PossibleAIChoice2;
    this->RoundNum = 0;
    row = InitialBoard.GetRowNumber();
    col = InitialBoard.GetColNumber();
    int sum = 0;
    for(const auto& pairs : InitialBoard.GetShipInfo()){
        sum += pairs.second;
    }
    this->Player1Left = sum;
    this->Player2Left = sum;
    this->player1_loss_detail = InitialBoard.GetShipInfo();
    this->player2_loss_detail = InitialBoard.GetShipInfo();
}

void Game::GetHumanPlayer1Info(HumanPlayer &Player) {
    this->Player1Name = Player.GetName();
    this->Player1_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player1_Self_Board = Player.GetSelfBoard();
    this->Player1_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
}

void Game::GetHumanPlayer2Info(HumanPlayer &Player) {
    this->Player2Name = Player.GetName();
    this->Player2_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player2_Self_Board = Player.GetSelfBoard();
    this->Player2_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
}

void Game::GetCheatingAIPlayer1Info(CheatingAI &Player) {
    this->Player1Name = Player.GetName();
    this->Player1_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player1_Self_Board = Player.GetSelfBoard();
    this->Player1_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
}

void Game::GetCheatingAIPlayer2Info(CheatingAI &Player) {
    this->Player2Name = Player.GetName();
    this->Player2_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player2_Self_Board = Player.GetSelfBoard();
    this->Player2_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
}

void Game::GetRandomAIPlayer1info(RandomAI &Player) {
    this->Player1Name = Player.GetName();
    this->Player1_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player1_Self_Board = Player.GetSelfBoard();
    this->Player1_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
    this->Player1_RandomShootList = Player.GenerateOrGetRandomShootList();
}

void Game::GetRandomAIPlayer2info(RandomAI &Player) {
    this->Player2Name = Player.GetName();
    this->Player2_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player2_Self_Board = Player.GetSelfBoard();
    this->Player2_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
    this->Player2_RandomShootList = Player.GenerateOrGetRandomShootList();
}

void Game::GetHuntDestroyAIPlayer1Info(SearchAndDestroyAI &Player) {
    this->Player1Name = Player.GetName();
    this->Player1_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player1_Self_Board = Player.GetSelfBoard();
    this->Player1_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
    this->Player1_RandomShootList = Player.GenerateOrGetRandomShootList();
    this->Player1HuntOrDestroy = 0;
}

void Game::GetHuntDestroyAIPlayer2Info(SearchAndDestroyAI &Player) {
    this->Player2Name = Player.GetName();
    this->Player2_Opponent_Fire_Board = Player.GetOpponentFireBoard();
    this->Player2_Self_Board = Player.GetSelfBoard();
    this->Player2_Self_Valid_Board = Player.GetVectorOfSelfValidCoordinates();
    this->Player2_RandomShootList = Player.GenerateOrGetRandomShootList();
    this->Player2HuntOrDestroy = 0;
}

void Game::PrintBoard(std::vector<std::vector<std::string>> &Board) {
    for(const auto& element : Board){
        std::string for_print;
        for(const auto& item : element){
            for_print += item;
            for_print += " ";
        }
        for_print.pop_back();
        std::cout << for_print << std::endl;
    }
}

void Game::PrintPlayer1PlacementBoard() {
    PrintBoard(this->Player1_Self_Board);
}

void Game::PrintPlayer1FiringBoard() {
    PrintBoard(this->Player1_Opponent_Fire_Board);
}

void Game::PrintPlayer2PlacementBoard() {
    PrintBoard(this->Player2_Self_Board);
}

void Game::PrintPlayer2FiringBoard() {
    PrintBoard(this->Player2_Opponent_Fire_Board);
}

void Game::game() {
    int winner = 0;
    while(winner == 0){
        if(GameChoice == 1){
            if(this->RoundNum%2 == 0){
                HumanPlayer1Move();
            } else if(this->RoundNum%2 == 1){
                HumanPlayer2Move();
            }
        } else if(GameChoice == 2){
            if(this->RoundNum%2 == 0){
                HumanPlayer1Move();
            } else if(this->RoundNum%2 == 1){
                if(PossibleAIChoice1 == 1){
                    CheatingAIPlayer2Move();
                } else if(PossibleAIChoice1 ==2){
                    RandomAIPlayer2Move();
                } else if(PossibleAIChoice1 == 3){
                    HuntDestroyPlayer2Move();
                }
            }
        } else if(GameChoice == 3){
            if(this->RoundNum%2 == 0){
                if(PossibleAIChoice1 == 1){
                    CheatingAIPlayer1Move();
                } else if(PossibleAIChoice1 ==2){
                    RandomAIPlayer1Move();
                } else if(PossibleAIChoice1 == 3){
                    HuntDestroyPlayer1Move();
                }
            } else if(this->RoundNum%2 == 1){
                if(PossibleAIChoice2 == 1){
                    CheatingAIPlayer2Move();
                } else if(PossibleAIChoice2 ==2){
                    RandomAIPlayer2Move();
                } else if(PossibleAIChoice2 == 3){
                    HuntDestroyPlayer2Move();
                }
            }
        }
        if(this->Player1Left == 0){
            std::cout << this->Player2Name << " won the game!" << std::endl;
            winner = 1;
        }
        if(this->Player2Left == 0){
            std::cout << this->Player1Name << " won the game!" << std::endl;
            winner = 1;
        }
        this->RoundNum += 1;
    }
}

void Game::HumanPlayer1Move() {
    int CheckInput = 0;
    int HorizontalCoordinate = -100;
    int VerticalCoordinate = -100;
    std::string what_is_left;
    while (CheckInput == 0){
        std::cout << this->Player1Name << "'s Firing Board" << std::endl;
        this->PrintPlayer1FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player1Name << "'s Placement Board" << std::endl;
        this->PrintPlayer1PlacementBoard();
        std::cout << Player1Name << ", where would you like to fire?" << std::endl;
        std::cout << "Enter your attack coordinate in the form row col: ";
        while(!(std::cin >> HorizontalCoordinate >> VerticalCoordinate)){
            std::cin.clear();
            std::getline(std::cin, what_is_left);
            std::cout << Player1Name << ", where would you like to fire?" << std::endl;
            std::cout << "Enter your attack coordinate in the form row col: ";
        }
        CheckInput = 2;
        std::cin.clear();
        std::getline(std::cin, what_is_left);
        for (auto &character : what_is_left) {
            if (not isspace(character)) {
                CheckInput = 0;
            }
        }
        std::cin.clear();
        if(CheckInput == 0){
            std::cin.clear();
        }
        what_is_left.clear();
        if(CheckInput > 0){
            if(HorizontalCoordinate < 0){
                CheckInput = 0;
            }
            if(VerticalCoordinate < 0){
                CheckInput = 0;
            }
            if(!(HorizontalCoordinate < this->row)){
                CheckInput = 0;
            }
            if(!(VerticalCoordinate < this->col)){
                CheckInput = 0;
            }
            std::cin.clear();
            if(CheckInput > 0){
                if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "O"){
                    CheckInput = 0;
                }
                if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "X"){
                    CheckInput = 0;
                }
                std::cin.clear();
            }
        }
        std::cin.clear();
    }
    if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*"){
        this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        std::cout << this->Player1Name << "'s Firing Board" << std::endl;
        this->PrintPlayer1FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player1Name << "'s Placement Board" << std::endl;
        this->PrintPlayer1PlacementBoard();
        std::cout << "Missed." << std::endl;
        std::cout << std::endl;
    }else if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*"){
        this->Player2Left -= 1;
        std::string hit_symbol;
        for(auto& pairs : this->player2_loss_detail){
            if(pairs.first == this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
                pairs.second -= 1;
                hit_symbol = pairs.first;
            }
        }
        this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        std::cout << this->Player1Name << "'s Firing Board" << std::endl;
        this->PrintPlayer1FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player1Name << "'s Placement Board" << std::endl;
        this->PrintPlayer1PlacementBoard();
        std::cout << this->Player1Name << " hit " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
        for(auto& pairs : this->player2_loss_detail){
            if(pairs.first == hit_symbol){
                if(pairs.second == 0){
                    std::cout << this->Player1Name << " destroyed " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
}

void Game::HumanPlayer2Move() {
    int CheckInput = 0;
    int HorizontalCoordinate = -1;
    int VerticalCoordinate = -1;
    std::string what_is_left;
    while (CheckInput == 0){
        std::cout << this->Player2Name << "'s Firing Board" << std::endl;
        this->PrintPlayer2FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player2Name << "'s Placement Board" << std::endl;
        this->PrintPlayer2PlacementBoard();
        std::cout << Player2Name << ", where would you like to fire?" << std::endl;
        std::cout << "Enter your attack coordinate in the form row col: ";
        while(!(std::cin >> HorizontalCoordinate >> VerticalCoordinate)){
            std::cin.clear();
            std::getline(std::cin, what_is_left);
            std::cout << Player2Name << ", where would you like to fire?" << std::endl;
            std::cout << "Enter your attack coordinate in the form row col: ";
        }
        CheckInput = 2;
        std::cin.clear();
        std::getline(std::cin, what_is_left);
        for (auto &character : what_is_left) {
            if (not isspace(character)) {
                CheckInput = 0;
            }
        }
        std::cin.clear();
        if(CheckInput == 0){
            std::cin.clear();
        }
        what_is_left.clear();
        if(CheckInput > 0){
            if(HorizontalCoordinate < 0){
                CheckInput = 0;
            }
            if(VerticalCoordinate < 0){
                CheckInput = 0;
            }
            if(!(HorizontalCoordinate < this->row)){
                CheckInput = 0;
            }
            if(!(VerticalCoordinate < this->col)){
                CheckInput = 0;
            }
            std::cin.clear();
            if(CheckInput > 0){
                if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "O"){
                    CheckInput = 0;
                }
                if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "X"){
                    CheckInput = 0;
                }
            }
        }
        std::cin.clear();
    }
    if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*"){
        this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        std::cout << this->Player2Name << "'s Firing Board" << std::endl;
        this->PrintPlayer2FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player2Name << "'s Placement Board" << std::endl;
        this->PrintPlayer2PlacementBoard();
        std::cout << "Missed." << std::endl;
        std::cout << std::endl;
    } else if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*"){
        this->Player1Left -= 1;
        std::string hit_symbol;
        for(auto& pairs : this->player1_loss_detail){
            if(pairs.first == this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
                pairs.second -= 1;
                hit_symbol = pairs.first;
            }
        }
        this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        std::cout << this->Player2Name << "'s Firing Board" << std::endl;
        this->PrintPlayer2FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player2Name << "'s Placement Board" << std::endl;
        this->PrintPlayer2PlacementBoard();
        std::cout << this->Player2Name << " hit " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
        for(auto& pairs : this->player1_loss_detail){
            if(pairs.first == hit_symbol){
                if(pairs.second == 0){
                    std::cout << this->Player2Name << " destroyed " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
}

void Game::CheatingAIPlayer1Move() {
    int HorizontalCoordinate = Player2_Self_Valid_Board.at(this->CheatingAIPlayer1ReadIndex).first;
    int VerticalCoordinate = Player2_Self_Valid_Board.at(this->CheatingAIPlayer1ReadIndex).second;
    this->CheatingAIPlayer1ReadIndex += 1;
    this->Player2Left -= 1;
    std::string hit_symbol;
    for(auto& pairs : this->player2_loss_detail){
        if(pairs.first == this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
            pairs.second -= 1;
            hit_symbol = pairs.first;
        }
    }
    this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
    this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
    std::cout << this->Player1Name << "'s Firing Board" << std::endl;
    this->PrintPlayer1FiringBoard();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << this->Player1Name << "'s Placement Board" << std::endl;
    this->PrintPlayer1PlacementBoard();
    std::cout << this->Player1Name << " hit " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
    for(auto& pairs : this->player2_loss_detail){
        if(pairs.first == hit_symbol){
            if(pairs.second == 0){
                std::cout << this->Player1Name << " destroyed " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void Game::CheatingAIPlayer2Move() {
    int HorizontalCoordinate = Player1_Self_Valid_Board.at(this->CheatingAIPlayer2ReadIndex).first;
    int VerticalCoordinate = Player1_Self_Valid_Board.at(this->CheatingAIPlayer2ReadIndex).second;
    this->CheatingAIPlayer2ReadIndex += 1;
    this->Player1Left -= 1;
    std::string hit_symbol;
    for(auto& pairs : this->player1_loss_detail){
        if(pairs.first == this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
            pairs.second -= 1;
            hit_symbol = pairs.first;
        }
    }
    this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
    this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
    std::cout << this->Player2Name << "'s Firing Board" << std::endl;
    this->PrintPlayer2FiringBoard();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << this->Player2Name << "'s Placement Board" << std::endl;
    this->PrintPlayer2PlacementBoard();
    std::cout << this->Player2Name << " hit " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
    for(auto& pairs : this->player1_loss_detail){
        if(pairs.first == hit_symbol){
            if(pairs.second == 0){
                std::cout << this->Player2Name << " destroyed " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

void Game::RandomAIPlayer1Move() {
    int index;
    std::uniform_int_distribution<int> Index(0, Player1_RandomShootList.size()-1);
    index = Index(AIPlayer::RandomNumberGenerator);
    std::pair<int, int> Coordinates;
    Coordinates = Player1_RandomShootList.at(index);
    int HorizontalCoordinate;
    int VerticalCoordinate;
    HorizontalCoordinate = Coordinates.first;
    VerticalCoordinate = Coordinates.second;
    Player1_RandomShootList.erase((Player1_RandomShootList.begin() + index));
    if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*"){
        this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        std::cout << this->Player1Name << "'s Firing Board" << std::endl;
        this->PrintPlayer1FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player1Name << "'s Placement Board" << std::endl;
        this->PrintPlayer1PlacementBoard();
        std::cout << "Missed." << std::endl;
        std::cout << std::endl;
    }else if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*"){
        this->Player2Left -= 1;
        std::string hit_symbol;
        for(auto& pairs : this->player2_loss_detail){
            if(pairs.first == this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
                pairs.second -= 1;
                hit_symbol = pairs.first;
            }
        }
        this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        std::cout << this->Player1Name << "'s Firing Board" << std::endl;
        this->PrintPlayer1FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player1Name << "'s Placement Board" << std::endl;
        this->PrintPlayer1PlacementBoard();
        std::cout << this->Player1Name << " hit " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
        for(auto& pairs : this->player2_loss_detail){
            if(pairs.first == hit_symbol){
                if(pairs.second == 0){
                    std::cout << this->Player1Name << " destroyed " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
}

void Game::RandomAIPlayer2Move() {
    int index;
    std::uniform_int_distribution<int> Index(0, Player2_RandomShootList.size()-1);
    index = Index(AIPlayer::RandomNumberGenerator);
    std::pair<int, int> Coordinates;
    Coordinates = Player2_RandomShootList.at(index);
    int HorizontalCoordinate;
    int VerticalCoordinate;
    HorizontalCoordinate = Coordinates.first;
    VerticalCoordinate = Coordinates.second;
    Player2_RandomShootList.erase((Player2_RandomShootList.begin() + index));
    if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*"){
        this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
        std::cout << this->Player2Name << "'s Firing Board" << std::endl;
        this->PrintPlayer2FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player2Name << "'s Placement Board" << std::endl;
        this->PrintPlayer2PlacementBoard();
        std::cout << "Missed." << std::endl;
        std::cout << std::endl;
    }else if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*"){
        this->Player1Left -= 1;
        std::string hit_symbol;
        for(auto& pairs : this->player1_loss_detail){
            if(pairs.first == this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
                pairs.second -= 1;
                hit_symbol = pairs.first;
            }
        }
        this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
        std::cout << this->Player2Name << "'s Firing Board" << std::endl;
        this->PrintPlayer2FiringBoard();
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << this->Player2Name << "'s Placement Board" << std::endl;
        this->PrintPlayer2PlacementBoard();
        std::cout << this->Player2Name << " hit " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
        for(auto& pairs : this->player1_loss_detail){
            if(pairs.first == hit_symbol){
                if(pairs.second == 0){
                    std::cout << this->Player2Name << " destroyed " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }
}

void Game::HuntDestroyPlayer1Move() {
    if(Player1HuntOrDestroy == 0){
        int index;
        std::uniform_int_distribution<int> Index(0, Player1_RandomShootList.size()-1);
        index = Index(AIPlayer::RandomNumberGenerator);
        std::pair<int, int> Coordinates;
        Coordinates = Player1_RandomShootList.at(index);
        int HorizontalCoordinate;
        int VerticalCoordinate;
        HorizontalCoordinate = Coordinates.first;
        VerticalCoordinate = Coordinates.second;
        Player1_RandomShootList.erase((Player1_RandomShootList.begin() + index));
        if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*"){
            this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
            this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
            std::cout << this->Player1Name << "'s Firing Board" << std::endl;
            this->PrintPlayer1FiringBoard();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << this->Player1Name << "'s Placement Board" << std::endl;
            this->PrintPlayer1PlacementBoard();
            std::cout << "Missed." << std::endl;
            std::cout << std::endl;
        }else if(this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*"){
            this->Player1HuntOrDestroy = 1;
            this->Player1_DestroyList.push_back(Coordinates);
            this->Player2Left -= 1;
            std::string hit_symbol;
            for(auto& pairs : this->player2_loss_detail){
                if(pairs.first == this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
                    pairs.second -= 1;
                    hit_symbol = pairs.first;
                }
            }
            this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
            this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
            std::cout << this->Player1Name << "'s Firing Board" << std::endl;
            this->PrintPlayer1FiringBoard();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << this->Player1Name << "'s Placement Board" << std::endl;
            this->PrintPlayer1PlacementBoard();
            std::cout << this->Player1Name << " hit " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
            for(auto& pairs : this->player2_loss_detail){
                if(pairs.first == hit_symbol){
                    if(pairs.second == 0){
                        std::cout << this->Player1Name << " destroyed " << this->Player2Name << "'s " << hit_symbol << "!" << std::endl;
                    }
                }
            }
            std::cout << std::endl;
        }
    } else if(Player1HuntOrDestroy == 1){
        if(!(Player1_DestroyList_FireAround.empty())) {
            std::pair<int, int> Coordinates;
            Coordinates = Player1_DestroyList_FireAround.at(0);
            int HorizontalCoordinate;
            int VerticalCoordinate;
            HorizontalCoordinate = Coordinates.first;
            VerticalCoordinate = Coordinates.second;
            Player1_DestroyList_FireAround.erase(Player1_DestroyList_FireAround.begin());
            if (this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*") {
                this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
                this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
                std::cout << this->Player1Name << "'s Firing Board" << std::endl;
                this->PrintPlayer1FiringBoard();
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << this->Player1Name << "'s Placement Board" << std::endl;
                this->PrintPlayer1PlacementBoard();
                std::cout << "Missed." << std::endl;
                std::cout << std::endl;
            } else if (this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*") {
                this->Player1HuntOrDestroy = 1;
                this->Player1_DestroyList.push_back(Coordinates);
                this->Player2Left -= 1;
                std::string hit_symbol;
                for (auto &pairs : this->player2_loss_detail) {
                    if (pairs.first ==
                        this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)) {
                        pairs.second -= 1;
                        hit_symbol = pairs.first;
                    }
                }
                this->Player2_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
                this->Player1_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
                std::cout << this->Player1Name << "'s Firing Board" << std::endl;
                this->PrintPlayer1FiringBoard();
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << this->Player1Name << "'s Placement Board" << std::endl;
                this->PrintPlayer1PlacementBoard();
                std::cout << this->Player1Name << " hit " << this->Player2Name << "'s " << hit_symbol << "!"
                          << std::endl;
                for (auto &pairs : this->player2_loss_detail) {
                    if (pairs.first == hit_symbol) {
                        if (pairs.second == 0) {
                            std::cout << this->Player1Name << " destroyed " << this->Player2Name << "'s " << hit_symbol
                                      << "!" << std::endl;
                        }
                    }
                }
                std::cout << std::endl;
            }
        } else if (!(Player1_DestroyList.empty()) && (Player1_DestroyList_FireAround.empty())) {
            while(!(Player1_DestroyList.empty()) && (Player1_DestroyList_FireAround.empty())){
                std::pair<int, int> Coordinates = Player1_DestroyList.at(0);
                int OriginalHorizontal = Coordinates.first;
                int OriginalVertical = Coordinates.second;
                Player1_DestroyList.erase(Player1_DestroyList.begin());
                int LeftH = OriginalHorizontal;
                int LeftV = OriginalVertical - 1;
                int CheckMatch = 0;
                for(auto& element : Player1_RandomShootList){
                    if(element.first == LeftH && element.second == LeftV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> LeftCoordinate = std::make_pair(LeftH, LeftV);
                    Player1_DestroyList_FireAround.push_back(LeftCoordinate);
                    int Lindex;
                    for(int i = 0; i < Player1_RandomShootList.size(); ++ i){
                        if(Player1_RandomShootList.at(i).first == LeftH && Player1_RandomShootList.at(i).second == LeftV){
                            Lindex = i;
                        }
                    }
                    Player1_RandomShootList.erase(Player1_RandomShootList.begin() + Lindex);
                    CheckMatch = 0;
                }
                int UpH = OriginalHorizontal - 1;
                int UpV = OriginalVertical;
                CheckMatch = 0;
                for(auto& element : Player1_RandomShootList){
                    if(element.first == UpH && element.second == UpV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> UpCoordinate = std::make_pair(UpH, UpV);
                    Player1_DestroyList_FireAround.push_back(UpCoordinate);
                    int Uindex;
                    for(int i = 0; i < Player1_RandomShootList.size(); ++i){
                        if(Player1_RandomShootList.at(i).first == UpH && Player1_RandomShootList.at(i).second == UpV){
                            Uindex = i;
                        }
                    }
                    Player1_RandomShootList.erase(Player1_RandomShootList.begin() + Uindex);
                    CheckMatch = 0;
                }
                int RightH = OriginalHorizontal;
                int RightV = OriginalVertical + 1;
                CheckMatch = 0;
                for(auto& element : Player1_RandomShootList){
                    if(element.first == RightH && element.second == RightV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> RightCoordinate = std::make_pair(RightH, RightV);
                    Player1_DestroyList_FireAround.push_back(RightCoordinate);
                    int Rindex;
                    for(int i = 0; i < Player1_RandomShootList.size(); ++ i){
                        if(Player1_RandomShootList.at(i).first == RightH && Player1_RandomShootList.at(i).second == RightV){
                            Rindex = i;
                        }
                    }
                    Player1_RandomShootList.erase(Player1_RandomShootList.begin() + Rindex);
                    CheckMatch = 0;
                }
                int DownH = OriginalHorizontal + 1;
                int DownV = OriginalVertical;
                CheckMatch = 0;
                for(auto& element : Player1_RandomShootList){
                    if(element.first == DownH && element.second == DownV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> DownCoordinate = std::make_pair(DownH, DownV);
                    Player1_DestroyList_FireAround.push_back(DownCoordinate);
                    int Dindex;
                    for(int i = 0; i < Player1_RandomShootList.size(); ++i){
                        if(Player1_RandomShootList.at(i).first == DownH && Player1_RandomShootList.at(i).second == DownV){
                            Dindex = i;
                        }
                    }
                    Player1_RandomShootList.erase(Player1_RandomShootList.begin() + Dindex);
                    CheckMatch = 0;
                }
            }
            if(!(Player1_DestroyList_FireAround.empty())){
                Player1HuntOrDestroy = 1;
                HuntDestroyPlayer1Move();
            } else if(Player1_DestroyList.empty() && Player1_DestroyList_FireAround.empty()){
                Player1HuntOrDestroy = 0;
                HuntDestroyPlayer1Move();
            }
        } else if(Player1_DestroyList.empty() && Player1_DestroyList_FireAround.empty()){
            Player1HuntOrDestroy = 0;
            HuntDestroyPlayer1Move();
        }
    }
}

void Game::HuntDestroyPlayer2Move() {
    if(Player2HuntOrDestroy == 0){
        int index;
        std::uniform_int_distribution<int> Index(0, Player2_RandomShootList.size()-1);
        index = Index(AIPlayer::RandomNumberGenerator);
        std::pair<int, int> Coordinates;
        Coordinates = Player2_RandomShootList.at(index);
        int HorizontalCoordinate;
        int VerticalCoordinate;
        HorizontalCoordinate = Coordinates.first;
        VerticalCoordinate = Coordinates.second;
        Player2_RandomShootList.erase((Player2_RandomShootList.begin() + index));
        if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*"){
            this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
            this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
            std::cout << this->Player2Name << "'s Firing Board" << std::endl;
            this->PrintPlayer2FiringBoard();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << this->Player2Name << "'s Placement Board" << std::endl;
            this->PrintPlayer2PlacementBoard();
            std::cout << "Missed." << std::endl;
            std::cout << std::endl;
        }else if(this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*"){
            this->Player2HuntOrDestroy = 1;
            this->Player2_DestroyList.push_back(Coordinates);
            this->Player1Left -= 1;
            std::string hit_symbol;
            for(auto& pairs : this->player1_loss_detail){
                if(pairs.first == this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)){
                    pairs.second -= 1;
                    hit_symbol = pairs.first;
                }
            }
            this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
            this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
            std::cout << this->Player2Name << "'s Firing Board" << std::endl;
            this->PrintPlayer2FiringBoard();
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << this->Player2Name << "'s Placement Board" << std::endl;
            this->PrintPlayer2PlacementBoard();
            std::cout << this->Player2Name << " hit " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
            for(auto& pairs : this->player1_loss_detail){
                if(pairs.first == hit_symbol){
                    if(pairs.second == 0){
                        std::cout << this->Player2Name << " destroyed " << this->Player1Name << "'s " << hit_symbol << "!" << std::endl;
                    }
                }
            }
            std::cout << std::endl;
        }
    } else if(Player2HuntOrDestroy == 1){
        if(!(Player2_DestroyList_FireAround.empty())) {
            std::pair<int, int> Coordinates;
            Coordinates = Player2_DestroyList_FireAround.at(0);
            int HorizontalCoordinate;
            int VerticalCoordinate;
            HorizontalCoordinate = Coordinates.first;
            VerticalCoordinate = Coordinates.second;
            Player2_DestroyList_FireAround.erase(Player2_DestroyList_FireAround.begin());
            if (this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) == "*") {
                this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
                this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "O";
                std::cout << this->Player2Name << "'s Firing Board" << std::endl;
                this->PrintPlayer2FiringBoard();
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << this->Player2Name << "'s Placement Board" << std::endl;
                this->PrintPlayer2PlacementBoard();
                std::cout << "Missed." << std::endl;
                std::cout << std::endl;
            } else if (this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) != "*") {
                this->Player2HuntOrDestroy = 1;
                this->Player2_DestroyList.push_back(Coordinates);
                this->Player1Left -= 1;
                std::string hit_symbol;
                for (auto &pairs : this->player1_loss_detail) {
                    if (pairs.first ==
                        this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1)) {
                        pairs.second -= 1;
                        hit_symbol = pairs.first;
                    }
                }
                this->Player1_Self_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
                this->Player2_Opponent_Fire_Board.at(HorizontalCoordinate + 1).at(VerticalCoordinate + 1) = "X";
                std::cout << this->Player2Name << "'s Firing Board" << std::endl;
                this->PrintPlayer2FiringBoard();
                std::cout << std::endl;
                std::cout << std::endl;
                std::cout << this->Player2Name << "'s Placement Board" << std::endl;
                this->PrintPlayer2PlacementBoard();
                std::cout << this->Player2Name << " hit " << this->Player1Name << "'s " << hit_symbol << "!"
                          << std::endl;
                for (auto &pairs : this->player1_loss_detail) {
                    if (pairs.first == hit_symbol) {
                        if (pairs.second == 0) {
                            std::cout << this->Player2Name << " destroyed " << this->Player1Name << "'s " << hit_symbol
                                      << "!" << std::endl;
                        }
                    }
                }
                std::cout << std::endl;
            }
        } else if (!(Player2_DestroyList.empty()) && (Player2_DestroyList_FireAround.empty())) {
            while(!(Player2_DestroyList.empty()) && (Player2_DestroyList_FireAround.empty())){
                std::pair<int, int> Coordinates = Player2_DestroyList.at(0);
                int OriginalHorizontal = Coordinates.first;
                int OriginalVertical = Coordinates.second;
                int LeftH = OriginalHorizontal;
                int LeftV = OriginalVertical - 1;
                int CheckMatch = 0;
                Player2_DestroyList.erase(Player2_DestroyList.begin());
                for(auto& element : Player2_RandomShootList){
                    if(element.first == LeftH && element.second == LeftV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> LeftCoordinate = std::make_pair(LeftH, LeftV);
                    Player2_DestroyList_FireAround.push_back(LeftCoordinate);
                    int Lindex;
                    for(int i = 0; i < Player2_RandomShootList.size(); ++ i){
                        if(Player2_RandomShootList.at(i).first == LeftH && Player2_RandomShootList.at(i).second == LeftV){
                            Lindex = i;
                        }
                    }
                    Player2_RandomShootList.erase(Player2_RandomShootList.begin() + Lindex);
                    CheckMatch = 0;
                }
                int UpH = OriginalHorizontal - 1;
                int UpV = OriginalVertical;
                CheckMatch = 0;
                for(auto& element : Player2_RandomShootList){
                    if(element.first == UpH && element.second == UpV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> UpCoordinate = std::make_pair(UpH, UpV);
                    Player2_DestroyList_FireAround.push_back(UpCoordinate);
                    int Uindex;
                    for(int i = 0; i < Player2_RandomShootList.size(); ++i){
                        if(Player2_RandomShootList.at(i).first == UpH && Player2_RandomShootList.at(i).second == UpV){
                            Uindex = i;
                        }
                    }
                    Player2_RandomShootList.erase(Player2_RandomShootList.begin() + Uindex);
                    CheckMatch = 0;
                }
                int RightH = OriginalHorizontal;
                int RightV = OriginalVertical + 1;
                CheckMatch = 0;
                for(auto& element : Player2_RandomShootList){
                    if(element.first == RightH && element.second == RightV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> RightCoordinate = std::make_pair(RightH, RightV);
                    Player2_DestroyList_FireAround.push_back(RightCoordinate);
                    int Rindex;
                    for(int i = 0; i < Player2_RandomShootList.size(); ++ i){
                        if(Player2_RandomShootList.at(i).first == RightH && Player2_RandomShootList.at(i).second == RightV){
                            Rindex = i;
                        }
                    }
                    Player2_RandomShootList.erase(Player2_RandomShootList.begin() + Rindex);
                    CheckMatch = 0;
                }
                int DownH = OriginalHorizontal + 1;
                int DownV = OriginalVertical;
                CheckMatch = 0;
                for(auto& element : Player2_RandomShootList){
                    if(element.first == DownH && element.second == DownV){
                        CheckMatch = 1;
                    }
                }
                if(CheckMatch == 1){
                    std::pair<int, int> DownCoordinate = std::make_pair(DownH, DownV);
                    Player2_DestroyList_FireAround.push_back(DownCoordinate);
                    int Dindex;
                    for(int i = 0; i < Player2_RandomShootList.size(); ++i){
                        if(Player2_RandomShootList.at(i).first == DownH && Player2_RandomShootList.at(i).second == DownV){
                            Dindex = i;
                        }
                    }
                    Player2_RandomShootList.erase(Player2_RandomShootList.begin() + Dindex);
                    CheckMatch = 0;
                }
            }
            if(!(Player2_DestroyList_FireAround.empty())){
                Player2HuntOrDestroy = 1;
                HuntDestroyPlayer2Move();
            } else if(Player2_DestroyList.empty() && Player2_DestroyList_FireAround.empty()){
                Player2HuntOrDestroy = 0;
                HuntDestroyPlayer2Move();
            }
        } else if(Player2_DestroyList.empty() && Player2_DestroyList_FireAround.empty()){
            Player2HuntOrDestroy = 0;
            HuntDestroyPlayer2Move();
        }
    }
}