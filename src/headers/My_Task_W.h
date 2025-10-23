#pragma once

#include <QWidget>

class QFrame;

class My_Tasks_Widget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card;

public:
    My_Tasks_Widget(QWidget* parent = nullptr);


};