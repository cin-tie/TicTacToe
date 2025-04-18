#include <QApplication>

#include "TicTacToe.h"

int main(int argc, char* argv[]){

    QApplication app(argc, argv);

    TicTacToe ticTacToe;
    ticTacToe.show();

    return app.exec();
    
}