#include "../include/mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include "../include/settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameBoard(nullptr)
{
    setWindowTitle("Крестики-нолики");
    resize(600, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    createMenu();
    startNewGame();
}

MainWindow::~MainWindow()
{
    
}
void MainWindow::createMenu()
{
    QMenu *gameMenu = menuBar()->addMenu("Игра");
    
    QAction *newGameAction = new QAction("Новая игра", this);
    QAction *settingsAction = new QAction("Настройки", this);
    QAction *exitAction = new QAction("Выход", this);
    
    connect(newGameAction, &QAction::triggered, this, &MainWindow::startNewGame);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::settingsOpen);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    
    gameMenu->addAction(newGameAction);
    gameMenu->addAction(settingsAction);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAction);
}

void MainWindow::settingsOpen()
{
    Settings dialog(this);
    dialog.setSize(currentSize);
    dialog.setGameMode(currentMode);
    
    if(dialog.exec() == QDialog::Accepted)
    {
        currentSize = dialog.getSize();
        currentMode = dialog.getGameMode();
        startNewGameWithSettings(currentSize, currentMode);
    }
}

void MainWindow::startNewGame()
{
    startNewGameWithSettings(currentSize, currentMode);
}

void MainWindow::startNewGameWithSettings(int size, GameMode mode)
{
    if (gameBoard) {
        centralWidget()->layout()->removeWidget(gameBoard);
        delete gameBoard;
        gameBoard = nullptr;
    }
    
    gameBoard = new GameBoard(size, mode, this);
    centralWidget()->layout()->addWidget(gameBoard);
}