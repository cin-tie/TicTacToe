#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"
#include "settingsdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showSettingsDialog();
    void startNewGame(int size, GameMode mode);

private:
    void createMenu();
    GameBoard *gameBoard;
    SettingsDialog *settingsDialog;
};

#endif