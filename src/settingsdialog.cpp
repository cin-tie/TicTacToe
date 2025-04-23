#include "../include/settingsdialog.h"
#include <QVBoxLayout>
#include <QLabel>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Настройки игры");
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    QLabel *sizeLabel = new QLabel("Размер поля:", this);
    layout->addWidget(sizeLabel);
    
    sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setRange(3, 10);
    sizeSpinBox->setValue(3);
    layout->addWidget(sizeSpinBox);
    
    QLabel *modeLabel = new QLabel("Режим игры:", this);
    layout->addWidget(modeLabel);
    
    modeComboBox = new QComboBox(this);
    modeComboBox->addItem("Игрок против игрока", static_cast<int>(GameMode::PlayerVsPlayer));
    modeComboBox->addItem("Игрок против компьютера", static_cast<int>(GameMode::PlayerVsComputer));
    layout->addWidget(modeComboBox);
    
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    layout->addWidget(buttonBox);
}

int SettingsDialog::getBoardSize() const
{
    return sizeSpinBox->value();
}

GameMode SettingsDialog::getGameMode() const
{
    return static_cast<GameMode>(modeComboBox->currentData().toInt());
}