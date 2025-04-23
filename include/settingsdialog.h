#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include "gameengine.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    
    int getBoardSize() const;
    GameMode getGameMode() const;

private:
    QSpinBox *sizeSpinBox;
    QComboBox *modeComboBox;
};

#endif