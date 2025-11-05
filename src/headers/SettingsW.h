#pragma once

#include <QWidget>

class QFrame;

class Settings_Widget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card;

public:
    Settings_Widget(QWidget* parent = nullptr);

};