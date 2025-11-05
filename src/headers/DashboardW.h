#pragma once

#include <QWidget>

class QFrame;

class Dashboard_Widget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card;

public:
    Dashboard_Widget(QWidget* parent = nullptr);


};