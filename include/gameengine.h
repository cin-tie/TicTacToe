#pragma once

#include <vector>
#include <utility>
#include <string>

enum class Player { None, X, O };
enum class GameState { Ongoing, XWon, OWon, Draw };
enum class GameMode { PlayerVsPlayer, PlayerVsComputer };



class GameEngine{
    private:
        struct GameSave {
            int size;
            GameMode mode;
            std::vector<std::pair<int, int>> moves;
            Player currentPlayer;
        };

        int data_size;
        GameMode data_gameMode;
        Player data_currentPlayer;
        GameState data_gameState;
        Player data_startPlayer;
        std::vector<std::vector<Player>> data_board;
        std::vector<std::pair<int, int>> moveHistory;
        
        bool checkWin(Player) const;
        bool checkLine(int, int, int, int, Player) const;
        std::pair<int, int> findBestMove() const;
        public:
        GameEngine(int, GameMode);
        
        bool isCellEmpty(int, int) const;
        void makeMove(int, int);
        std::pair<int, int> getComputerMove() const;
        void reset();
        
        void saveGame(const std::string& filename) const;
        bool loadGame(const std::string& filename);
        const std::vector<std::pair<int, int>>& getMoveHistory() const { return moveHistory; }
        void clearMoveHistory() { moveHistory.clear(); }
        Player currentPlayer() const;
        GameState gameState() const;
        bool isGameOver() const;
        int boardSize() const;
};