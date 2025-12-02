#pragma once

#include <QWidget>

class QFrame;

class SettingsWidget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card;

public:
    SettingsWidget(QWidget* parent = nullptr);

};