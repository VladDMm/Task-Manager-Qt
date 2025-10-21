#pragma once

#include <QWidget>

class QFrame;

class My_Tasks_Widget : public QWidget
{
    Q_OBJECT
public:
    My_Tasks_Widget(QWidget* parent = nullptr);

private:
    QFrame* card;
};