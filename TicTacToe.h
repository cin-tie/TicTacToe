#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QPair>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class TicTacToe : public QWidget {
    Q_OBJECT

    private:
        size_t sizeOfField = 3;
        QGridLayout*** buttons = nullptr;

        QLabel* statusLabel = nullptr;
        QPushButton* clearButton = nullptr;
        QGridLayout* gridLayout = nullptr;
        QVBoxLayout* mainLayout = nullptr;

        bool personToStart = false;
        bool currentPlayer = false;
        bool vsComputer = false;

        void setupUI();
        void createButtons();
        void highlightWinningLine(QVector<QPair<int16_t, int16_t>> line);
        void computerMove();

    public:
        TicTacToe(QWidget* parent = nullptr);
        ~TicTacToe();

    private slots:
        void handleButtonClick();
        void resetGame();
        bool checkDraw();
        bool checkWin();
        bool checkWin(bool showMessage);
        void disableButtons();
        void setGameMode(bool computerMode);
        void setSizeOfField(size_t size);
};
