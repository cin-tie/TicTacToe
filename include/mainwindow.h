#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startNewGame();
    void startNewGameWithSettings(int size, GameMode mode);
    void settingsOpen();
    
private:
    void createMenu();
    
    GameBoard *gameBoard;
    int currentSize = 3;
    GameMode currentMode = GameMode::PlayerVsPlayer;
};

#endif