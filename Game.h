//
// Created by 人之初 on 2021/6/12.
//

#ifndef BATTLESHIP_GAME_H
#define BATTLESHIP_GAME_H
#include "BlankBoard.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "RandomAI.h"
#include "CheatingAI.h"
#include "SearchAndDestroyAI.h"
class Game{
public:
    Game(int GameChoice, int PossibleAIChoice1, int PossibleAIChoice2, BlankBoard& InitialBoard);
    void GetHumanPlayer1Info(HumanPlayer& Player);
    void GetRandomAIPlayer1info(RandomAI& Player);
    void GetCheatingAIPlayer1Info(CheatingAI& Player);
    void GetHuntDestroyAIPlayer1Info(SearchAndDestroyAI& Player);
    void GetHumanPlayer2Info(HumanPlayer& Player);
    void GetRandomAIPlayer2info(RandomAI& Player);
    void GetCheatingAIPlayer2Info(CheatingAI& Player);
    void GetHuntDestroyAIPlayer2Info(SearchAndDestroyAI& Player);
    void PrintBoard(std::vector<std::vector<std::string>>& Board);
    void PrintPlayer1PlacementBoard();
    void PrintPlayer2PlacementBoard();
    void PrintPlayer1FiringBoard();
    void PrintPlayer2FiringBoard();
    void HumanPlayer1Move();
    void HumanPlayer2Move();
    void CheatingAIPlayer1Move();
    void CheatingAIPlayer2Move();
    void RandomAIPlayer1Move();
    void RandomAIPlayer2Move();
    void HuntDestroyPlayer1Move();
    void HuntDestroyPlayer2Move();
    void game();
private:
    int GameChoice;
    int PossibleAIChoice1;
    int PossibleAIChoice2;
    std::string Player1Name;
    std::string Player2Name;
    int row;
    int col;
    int RoundNum;
    std::vector<std::vector<std::string>> Player1_Self_Board;
    std::vector<std::vector<std::string>> Player1_Opponent_Fire_Board;
    std::vector<std::pair<int, int>> Player1_Self_Valid_Board;
    std::vector<std::vector<std::string>> Player2_Self_Board;
    std::vector<std::vector<std::string>> Player2_Opponent_Fire_Board;
    std::vector<std::pair<int, int>> Player2_Self_Valid_Board;
    std::vector<std::pair<int, int>> Player1_RandomShootList;
    std::vector<std::pair<int, int>> Player2_RandomShootList;
    std::vector<std::pair<int, int>> Player1_DestroyList_FireAround;
    std::vector<std::pair<int, int>> Player1_DestroyList;
    std::vector<std::pair<int, int>> Player2_DestroyList_FireAround;
    std::vector<std::pair<int, int>> Player2_DestroyList;
    int Player1HuntOrDestroy;
    int Player2HuntOrDestroy;
    int Player1Left;
    int Player2Left;
    std::map<std::string, int> player1_loss_detail;
    std::map<std::string, int> player2_loss_detail;
    int CheatingAIPlayer1ReadIndex = 0;
    int CheatingAIPlayer2ReadIndex = 0;
};
#endif //BATTLESHIP_GAME_H
