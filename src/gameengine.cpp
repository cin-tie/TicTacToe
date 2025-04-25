#include "../include/gameengine.h"
#include <iostream>

GameEngine::GameEngine(int size, GameMode gameMode) : 
data_size(size), data_gameMode(gameMode), data_currentPlayer(Player::O), data_gameState(GameState::Ongoing), data_startPlayer(Player::O){
    reset();
}

void GameEngine::reset(){
    data_board.clear();
    data_board.resize(data_size, std::vector<Player>(data_size, Player::None));
    data_startPlayer = (data_startPlayer == Player::X) ? Player::O : Player::X;
    data_currentPlayer = data_startPlayer;
    data_gameState = GameState::Ongoing;
}

bool GameEngine::isCellEmpty(int row, int col) const{
    return data_board[row][col] == Player::None;
}

void GameEngine::makeMove(int row, int col){
    if(data_gameState != GameState::Ongoing || ! isCellEmpty(row, col)){
        return;
    }

    data_board[row][col] = data_currentPlayer;

    if(checkWin(data_currentPlayer)){
        data_gameState = (data_currentPlayer == Player::X) ? GameState::XWon : GameState::OWon;
    }
    else{
        bool draw = true;
        for(auto row : data_board){
            for(auto cell : row){
                if(cell == Player::None){
                    draw = false;
                    break;
                }
            }
            if(!draw)
                break;
        }
        if(draw){
            data_gameState = GameState::Draw;
        }
        else{
            data_currentPlayer = (data_currentPlayer == Player::X) ? Player::O : Player::X;
        }
    }
}

std::pair<int, int> GameEngine::getComputerMove() const{
    return findBestMove();
}

bool GameEngine::checkWin(Player player) const{
    for(int i = 0; i < data_size; ++i){
        if(checkLine(i, 0, 0, 1, player) || checkLine(0, i, 1, 0, player)){
            return true;
        }
    }
    if(checkLine(0, 0, 1, 1, player) || checkLine(0, data_size - 1, 1, -1, player)){
        return true;
    }
    return false;
}

bool GameEngine::checkLine(int startRow, int startCol, int rowDelta, int colDelta, Player player) const {
    for(int i = 0; i < data_size; ++i){
        if(data_board[startRow + i * rowDelta][startCol + i * colDelta] != player){
            return false;
        }
    }
    return true;
}

std::pair<int, int> GameEngine::findBestMove() const
{
    int a = rand() % data_size;
    int b = rand() % data_size;
    while(!isCellEmpty(a, b)){
        a = rand() % data_size;
        b = rand() % data_size;
    }
    std::pair<int, int> bestMove = {a, b};
    return bestMove;
}


Player GameEngine::currentPlayer() const
{
    return data_currentPlayer;
}

GameState GameEngine::gameState() const
{
    return data_gameState;
}

bool GameEngine::isGameOver() const
{
    return data_gameState != GameState::Ongoing;
}

int GameEngine::boardSize() const
{
    return data_size;
}