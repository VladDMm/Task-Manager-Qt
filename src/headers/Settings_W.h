#pragma once

#include <QWidget>

class QFrame;

class Settings_Widget : public QWidget
{
    Q_OBJECT
public:
    Settings_Widget(QWidget* parent = nullptr);

private:
    QFrame* card;
};