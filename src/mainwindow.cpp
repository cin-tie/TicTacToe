#include "../include/mainwindow.h"
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include "../include/gameengine.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), gameBoard(nullptr)
{
    setWindowTitle("Крестики-нолики");
    resize(600, 600);

    createMenu();
    createControls();
    startNewGame();
}

MainWindow::~MainWindow(){}

void MainWindow::createMenu()
{
    QMenu *gameMenu = menuBar()->addMenu("Игра");
    
    QAction *exitAction = new QAction("Выход", this);
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    gameMenu->addAction(exitAction);
}

void MainWindow::createControls()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    
    QLabel *sizeLabel = new QLabel("Размер поля:", this);
    controlsLayout->addWidget(sizeLabel);
    
    sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setRange(3, 10);
    sizeSpinBox->setValue(3);
    controlsLayout->addWidget(sizeSpinBox);
    
    QLabel *modeLabel = new QLabel("Режим игры:", this);
    controlsLayout->addWidget(modeLabel);
    
    modeComboBox = new QComboBox(this);
    modeComboBox->addItem("Игрок против игрока", static_cast<int>(GameMode::PlayerVsPlayer));
    modeComboBox->addItem("Игрок против компьютера", static_cast<int>(GameMode::PlayerVsComputer));
    controlsLayout->addWidget(modeComboBox);
    
    connect(sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::updateGameSettings);
    connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::updateGameSettings);
    
    mainLayout->addLayout(controlsLayout);
    
    setCentralWidget(centralWidget);
}

void MainWindow::startNewGame()
{
    if (gameBoard) {
        centralWidget()->layout()->removeWidget(gameBoard);
        gameBoard->deleteLater();
    }
    
    int size = sizeSpinBox->value();
    GameMode mode = static_cast<GameMode>(modeComboBox->currentData().toInt());
    
    gameBoard = new GameBoard(size, mode, this);
    centralWidget()->layout()->addWidget(gameBoard);
}

void MainWindow::updateGameSettings()
{
    startNewGame();
}