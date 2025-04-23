#include "../include/mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameBoard(nullptr), settingsDialog(new SettingsDialog(this))
{
    setWindowTitle("Крестики-нолики");
    resize(600, 600);

    createMenu();
    showSettingsDialog();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenu()
{
    QMenu *gameMenu = menuBar()->addMenu("Игра");
    
    QAction *newGameAction = new QAction("Новая игра", this);
    connect(newGameAction, &QAction::triggered, this, &MainWindow::showSettingsDialog);
    gameMenu->addAction(newGameAction);
    
    QAction *exitAction = new QAction("Выход", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    gameMenu->addAction(exitAction);
}

void MainWindow::showSettingsDialog()
{
    if (settingsDialog->exec() == QDialog::Accepted) {
        int size = settingsDialog->getBoardSize();
        GameMode mode = settingsDialog->getGameMode();
        
        if (gameBoard) {
            centralWidget()->deleteLater();
        }
        
        gameBoard = new GameBoard(size, mode, this);
        setCentralWidget(gameBoard);
    }
}

void MainWindow::startNewGame(int size, GameMode mode)
{
    if (gameBoard) {
        centralWidget()->deleteLater();
    }
    
    gameBoard = new GameBoard(size, mode, this);
    setCentralWidget(gameBoard);
}