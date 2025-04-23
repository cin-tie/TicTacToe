#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"

class QSpinBox;
class QComboBox;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startNewGame();
    void updateGameSettings();

private:
    void createMenu();
    void createControls();
    
    GameBoard *gameBoard;
    QSpinBox *sizeSpinBox;
    QComboBox *modeComboBox;
    //QPushButton *newGameButton;
};

#endif