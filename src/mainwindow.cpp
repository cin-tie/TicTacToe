#include "../include/mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QFileDialog>
#include "../include/settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameBoard(nullptr)
{
    setWindowTitle("Крестики-нолики");
    setWindowIcon(QIcon("../resources/icon.png"));
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
    QAction *saveAction = new QAction("Сохранить игру", this);
    QAction *loadAction = new QAction("Загрузить игру", this);
    QAction *settingsAction = new QAction("Настройки", this);
    QAction *exitAction = new QAction("Выход", this);
    
    connect(newGameAction, &QAction::triggered, this, &MainWindow::startNewGame);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::settingsOpen);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveGame);
    connect(loadAction, &QAction::triggered, this, &MainWindow::loadGame);
    
    gameMenu->addAction(newGameAction);
    gameMenu->addAction(saveAction);
    gameMenu->addAction(loadAction);
    gameMenu->addAction(settingsAction);
    gameMenu->addSeparator();
    gameMenu->addAction(exitAction);
}

void MainWindow::saveGame() {
    QString filename = getSaveFileName(true);
    if (!filename.isEmpty()) {
        gameBoard->saveGame(filename);
    }
}

void MainWindow::loadGame() {
    QString filename = getSaveFileName(false);
    if (!filename.isEmpty()) {
        gameBoard->loadGame(filename);
    }
}

QString MainWindow::getSaveFileName(bool isSave) {
    QFileDialog dialog(this);
    dialog.setNameFilter("Файлы сохранения (*.tictac)");
    dialog.setDefaultSuffix("tictac");
    
    if (isSave) {
        return dialog.getSaveFileName(this, "Сохранить игру", "", "Файлы сохранения (*.tictac)");
    } else {
        return dialog.getOpenFileName(this, "Загрузить игру", "", "Файлы сохранения (*.tictac)");
    }
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