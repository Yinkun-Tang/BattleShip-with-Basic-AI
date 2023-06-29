#include <iostream>
#include "BlankBoard.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "CheatingAI.h"
#include "RandomAI.h"
#include "SearchAndDestroyAI.h"
#include "Game.h"
#include <random>
#include <fstream>
#include <map>

std::mt19937 AIPlayer::RandomNumberGenerator(time(nullptr));
int main(int argc, char* argv[]) {
    int SeedValue = time(nullptr);
    if(argc == 3){
        SeedValue = std::stoi(argv[2]);
    }
    AIPlayer::RandomNumberGenerator.seed(SeedValue);

    std::ifstream OpenConfigurationFile;
    std::string filepath = argv[1];
    int row;
    int col;
    int NumOfShip;
    OpenConfigurationFile.open(filepath);
    OpenConfigurationFile >> row;
    OpenConfigurationFile >> col;
    OpenConfigurationFile >> NumOfShip;

    std::string symbol_of_ship;
    int length_of_ship;
    std::pair<std::string, int> ship_information;
    std::map<std::string, int> ship_info;
    while(!OpenConfigurationFile.fail()){
        OpenConfigurationFile >> symbol_of_ship;
        OpenConfigurationFile >> length_of_ship;
        ship_information = std::make_pair(symbol_of_ship, length_of_ship);
        ship_info.emplace(ship_information);
    }
    if(!OpenConfigurationFile.eof()){
        OpenConfigurationFile.close();
    }

    BlankBoard Setup(row,col,NumOfShip,ship_info);

    int GameType = 0;
    int PossibleAIChoice1 = 0;
    int PossibleAIChoice2 = 0;
    std::cout << "What type of game do you want to play?" << std::endl;
    std::cout << "1. Human vs Human" << std::endl;
    std::cout << "2. Human vs AI" << std::endl;
    std::cout << "3. AI vs AI" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> GameType;

    if(GameType == 1){
        HumanPlayer Player1(1, Setup);
        Player1.SetPlacementBoardAndFiringBoard(Setup);
        HumanPlayer Player2(2,Setup);
        Player2.SetPlacementBoardAndFiringBoard(Setup);
        Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
        GameWithAI.GetHumanPlayer1Info(Player1);
        GameWithAI.GetHumanPlayer2Info(Player2);
        GameWithAI.game();
    } else if(GameType == 2){
        HumanPlayer Player1(1, Setup);
        Player1.SetPlacementBoardAndFiringBoard(Setup);
        std::cout << "What AI do you want?" << std::endl;
        std::cout << "1. Cheating AI" << std::endl;
        std::cout << "2. Random AI" << std::endl;
        std::cout << "3. Hunt Destroy AI" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> PossibleAIChoice1;
        if(PossibleAIChoice1 == 1){
            CheatingAI Player2(2,Setup);
            Player2.SetPlacementBoardAndFiringBoard(Setup);
            Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
            GameWithAI.GetHumanPlayer1Info(Player1);
            GameWithAI.GetCheatingAIPlayer2Info(Player2);
            GameWithAI.game();
        } else if(PossibleAIChoice1 == 2){
            RandomAI Player2(2,Setup);
            Player2.SetPlacementBoardAndFiringBoard(Setup);
            Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
            GameWithAI.GetHumanPlayer1Info(Player1);
            GameWithAI.GetRandomAIPlayer2info(Player2);
            GameWithAI.game();
        } else if(PossibleAIChoice1 == 3){
            SearchAndDestroyAI Player2(2, Setup);
            Player2.SetPlacementBoardAndFiringBoard(Setup);
            Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
            GameWithAI.GetHumanPlayer1Info(Player1);
            GameWithAI.GetHuntDestroyAIPlayer2Info(Player2);
            GameWithAI.game();
        }
    } else if (GameType == 3){
        std::cout << "What AI do you want?" << std::endl;
        std::cout << "1. Cheating AI" << std::endl;
        std::cout << "2. Random AI" << std::endl;
        std::cout << "3. Hunt Destroy AI" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> PossibleAIChoice1;
        if(PossibleAIChoice1 == 1){
            CheatingAI Player1(1,Setup);
            Player1.SetPlacementBoardAndFiringBoard(Setup);
            std::cout << "What AI do you want?" << std::endl;
            std::cout << "1. Cheating AI" << std::endl;
            std::cout << "2. Random AI" << std::endl;
            std::cout << "3. Hunt Destroy AI" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> PossibleAIChoice2;
            if(PossibleAIChoice2 == 1){
                CheatingAI Player2(2,Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetCheatingAIPlayer1Info(Player1);
                GameWithAI.GetCheatingAIPlayer2Info(Player2);
                GameWithAI.game();
            } else if(PossibleAIChoice2 == 2){
                RandomAI Player2(2,Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetCheatingAIPlayer1Info(Player1);
                GameWithAI.GetRandomAIPlayer2info(Player2);
                GameWithAI.game();
            } else if(PossibleAIChoice2 == 3){
                SearchAndDestroyAI Player2(2, Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetCheatingAIPlayer1Info(Player1);
                GameWithAI.GetHuntDestroyAIPlayer2Info(Player2);
                GameWithAI.game();
            }
        } else if(PossibleAIChoice1 == 2){
            RandomAI Player1(1,Setup);
            Player1.SetPlacementBoardAndFiringBoard(Setup);
            std::cout << "What AI do you want?" << std::endl;
            std::cout << "1. Cheating AI" << std::endl;
            std::cout << "2. Random AI" << std::endl;
            std::cout << "3. Hunt Destroy AI" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> PossibleAIChoice2;
            if(PossibleAIChoice2 == 1){
                CheatingAI Player2(2,Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetRandomAIPlayer1info(Player1);
                GameWithAI.GetCheatingAIPlayer2Info(Player2);
                GameWithAI.game();
            } else if(PossibleAIChoice2 == 2){
                RandomAI Player2(2,Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetRandomAIPlayer1info(Player1);
                GameWithAI.GetRandomAIPlayer2info(Player2);
                GameWithAI.game();
            } else if(PossibleAIChoice2 == 3){
                SearchAndDestroyAI Player2(2, Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetRandomAIPlayer1info(Player1);
                GameWithAI.GetHuntDestroyAIPlayer2Info(Player2);
                GameWithAI.game();
            }
        } else if(PossibleAIChoice1 == 3){
            SearchAndDestroyAI Player1(1, Setup);
            Player1.SetPlacementBoardAndFiringBoard(Setup);
            std::cout << "What AI do you want?" << std::endl;
            std::cout << "1. Cheating AI" << std::endl;
            std::cout << "2. Random AI" << std::endl;
            std::cout << "3. Hunt Destroy AI" << std::endl;
            std::cout << "Your choice: ";
            std::cin >> PossibleAIChoice2;
            if(PossibleAIChoice2 == 1){
                CheatingAI Player2(2,Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetHuntDestroyAIPlayer1Info(Player1);
                GameWithAI.GetCheatingAIPlayer2Info(Player2);
                GameWithAI.game();
            } else if(PossibleAIChoice2 == 2){
                RandomAI Player2(2,Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetHuntDestroyAIPlayer1Info(Player1);
                GameWithAI.GetRandomAIPlayer2info(Player2);
                GameWithAI.game();
            } else if(PossibleAIChoice2 == 3){
                SearchAndDestroyAI Player2(2, Setup);
                Player2.SetPlacementBoardAndFiringBoard(Setup);
                Game GameWithAI(GameType,PossibleAIChoice1,PossibleAIChoice2,Setup);
                GameWithAI.GetHuntDestroyAIPlayer1Info(Player1);
                GameWithAI.GetHuntDestroyAIPlayer2Info(Player2);
                GameWithAI.game();
            }
        }
    }

    return 0;
}
