#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "mainwindow.h"
#include "gameengine.h"

class Settings : public QDialog {
    
    Q_OBJECT

    private:
        QSpinBox* sizeSpinBox;
        QComboBox* modeComboBox;

    public:

        Settings(QWidget* parent = nullptr);
        int getSize() const;
        GameMode getGameMode() const;
        void setSize(int size);
        void setGameMode(GameMode mode);
};

#endif