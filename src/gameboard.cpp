#include "../include/gameboard.h"
#include <QMessageBox>
#include <QTimer>

GameBoard::GameBoard(int size, GameMode mode, QWidget *parent)
    : QWidget(parent), boardSize(size), gameMode(mode)
{
    gameEngine = new GameEngine(size, mode);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    statusLabel = new QLabel(this);
    updateStatusLabel();
    mainLayout->addWidget(statusLabel);
    
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(5);
    mainLayout->addLayout(gridLayout);
    createBoard();
    
    resetButton = new QPushButton("Новая игра", this);
    connect(resetButton, &QPushButton::clicked, this, &GameBoard::resetBoard);
    mainLayout->addWidget(resetButton);
    
    
    if (gameMode == GameMode::PlayerVsComputer && gameEngine->currentPlayer() == Player::O) {
        QTimer::singleShot(500, this, &GameBoard::handleComputerMove);
    }
}

void GameBoard::createBoard()
{
    buttons.resize(boardSize);
    for (int row = 0; row < boardSize; ++row) {
        buttons[row].resize(boardSize);
        for (int col = 0; col < boardSize; ++col) {
            QPushButton *button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setStyleSheet("font-size: 24px; min-width: 50px; min-height: 50px");
            gridLayout->addWidget(button, row, col);
            buttons[row][col] = button;
            connect(button, &QPushButton::clicked, this, &GameBoard::handleButtonClick);
        }
    }
}

void GameBoard::handleButtonClick()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            if (buttons[row][col] == button && gameEngine->isCellEmpty(row, col)) {
                makeMove(row, col);
                return;
            }
        }
    }
}

void GameBoard::makeMove(int row, int col)
{
    buttons[row][col]->setText(gameEngine->currentPlayer() == Player::X ? "X" : "O");
    buttons[row][col]->setEnabled(false);
    gameEngine->makeMove(row, col);
    
    checkGameEnd();
    
    if (gameMode == GameMode::PlayerVsComputer && !gameEngine->isGameOver() && gameEngine->currentPlayer() == Player::O) {
        QTimer::singleShot(500, this, &GameBoard::handleComputerMove);
    }
}

void GameBoard::handleComputerMove()
{
    auto [row, col] = gameEngine->getComputerMove();
    makeMove(row, col);
}

void GameBoard::updateStatusLabel()
{
    QString status;
    if (gameEngine->isGameOver()) {
        GameState state = gameEngine->gameState();
        if (state == GameState::XWon) {
            status = "Игрок X победил!";
        } else if (state == GameState::OWon) {
            status = gameMode == GameMode::PlayerVsPlayer ? "Игрок O победил!" : "Компьютер победил!";
        } else {
            status = "Ничья!";
        }
    } else {
        status = gameEngine->currentPlayer() == Player::X ? 
            "Ход игрока X" : 
            (gameMode == GameMode::PlayerVsPlayer ? "Ход игрока O" : "Ход компьютера");
    }
    statusLabel->setText(status);
}


void GameBoard::checkGameEnd() {
    updateStatusLabel();
    
    if (gameEngine->isGameOver()) {
        highlightWinningLine();
        
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                buttons[row][col]->setEnabled(false);
            }
        }
        
        QMessageBox::information(this, "Игра окончена", statusLabel->text());
    }
}

void GameBoard::resetBoard()
{
    gameEngine->reset();
    
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            buttons[row][col]->setText("");
            buttons[row][col]->setEnabled(true);
            buttons[row][col]->setStyleSheet(
                "font-size: 24px; min-width: 50px; min-height: 50px"
            );
        }
    }
    
    updateStatusLabel();
    
    if (gameMode == GameMode::PlayerVsComputer && gameEngine->currentPlayer() == Player::O) {
        QTimer::singleShot(500, this, &GameBoard::handleComputerMove);
    }
}
void GameBoard::replayGame(const std::vector<std::pair<int, int>>& moves) {
    resetBoard();
    gameEngine->clearMoveHistory();
    
    for (size_t i = 0; i < moves.size(); ++i) {
        const auto& [row, col] = moves[i];
        QTimer::singleShot(500 * (i + 1), this, [this, row, col]() {
            makeMove(row, col);
        });
    }
}

void GameBoard::highlightWinningLine() {
    if (!gameEngine->isGameOver() || gameEngine->gameState() == GameState::Draw) {
        return;
    }
    
    Player winner = gameEngine->gameState() == GameState::XWon ? Player::X : Player::O;
    auto winningLine = gameEngine->getWinningLine(winner);
    
    for (const auto& [row, col] : winningLine) {
        buttons[row][col]->setStyleSheet(
            "font-size: 24px; min-width: 50px; min-height: 50px; "
            "background-color: #aaffaa; color: #ff0000; font-weight: bold;"
        );
    }
}

void GameBoard::saveGame(const QString& filename) {
    try {
        gameEngine->saveGame(filename.toStdString());
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", "Не удалось сохранить игру");
    }
}

bool GameBoard::loadGame(const QString& filename) {
    if (gameEngine->loadGame(filename.toStdString())) {
        gameEngine->reset();
        gameEngine->clearMoveHistory();
        
        const auto& moves = gameEngine->getMoveHistory();
        replayGame(moves);
        return true;
    }
    return false;
}
