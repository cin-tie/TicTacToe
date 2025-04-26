#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include "gameengine.h"

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    GameBoard(int size, GameMode mode, QWidget *parent = nullptr);
    void resetBoard();
    void replayGame(const std::vector<std::pair<int, int>>& moves);
    void saveGame(const QString& filename);
    bool loadGame(const QString& filename);

signals:
    void moveMade(int row, int col, Player player);

private slots:
    void handleButtonClick();
    void handleComputerMove();

private:
    void createBoard();
    void updateStatusLabel();
    void checkGameEnd();
    void makeMove(int row, int col);
    
    int boardSize;
    GameMode gameMode;
    GameEngine *gameEngine;
    QGridLayout *gridLayout;
    QVector<QVector<QPushButton*>> buttons;
    QLabel *statusLabel;
    QPushButton *resetButton;
};

#endif