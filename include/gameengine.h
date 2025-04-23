#pragma once

#include <vector>
#include <utility>

enum class Player { None, X, O };
enum class GameState { Ongoing, XWon, OWon, Draw };
enum class GameMode { PlayerVsPlayer, PlayerVsComputer };

class GameEngine{
    private:
        int data_size;
        GameMode data_gameMode;
        Player data_currentPlayer;
        GameState data_gameState;
        std::vector<std::vector<Player>> data_board;

        bool checkWin(Player) const;
        bool checkLine(int, int, int, int, Player) const;
        std::pair<int, int> findBestMove() const;
    public:
        GameEngine(int, GameMode);

        bool isCellEmpty(int, int) const;
        void makeMove(int, int);
        std::pair<int, int> getComputerMove() const;
        void reset();

        Player currentPlayer() const;
        GameState gameState() const;
        bool isGameOver() const;
        int boardSize() const;
};