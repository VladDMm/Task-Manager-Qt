#pragma once

#include <QWidget>

class QFrame;

class Dashboard_Widget : public QWidget
{
    Q_OBJECT
public:
    Dashboard_Widget(QWidget* parent = nullptr);

private:
    QFrame* card;
};