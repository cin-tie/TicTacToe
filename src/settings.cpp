#include "../include/settings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

Settings::Settings(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Настройки игры");
    resize(400, 200);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    QHBoxLayout *sizeLayout = new QHBoxLayout();
    QLabel *sizeLabel = new QLabel("Размер поля (3-10):", this);
    sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setRange(3, 10);
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(sizeSpinBox);
    mainLayout->addLayout(sizeLayout);

    QHBoxLayout *modeLayout = new QHBoxLayout();
    QLabel *modeLabel = new QLabel("Режим игры:", this);
    modeComboBox = new QComboBox(this);
    modeComboBox->addItem("Игрок против игрока", static_cast<int>(GameMode::PlayerVsPlayer));
    modeComboBox->addItem("Игрок против компьютера", static_cast<int>(GameMode::PlayerVsComputer));
    modeLayout->addWidget(modeLabel);
    modeLayout->addWidget(modeComboBox);
    mainLayout->addLayout(modeLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    setLayout(mainLayout);
}

int Settings::getSize() const {
    return sizeSpinBox->value();
}

GameMode Settings::getGameMode() const {
    return static_cast<GameMode>(modeComboBox->currentData().toInt());
}

void Settings::setSize(int size) {
    sizeSpinBox->setValue(size);
}

void Settings::setGameMode(GameMode mode) {
    modeComboBox->setCurrentIndex(static_cast<int>(mode));
}