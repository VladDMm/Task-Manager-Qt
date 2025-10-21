#pragma once

#include <QWidget>

class QFrame;
class QToolButton;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class Top_Bar_Widget : public QWidget
{
    Q_OBJECT
public:
    Top_Bar_Widget(QWidget* parent = nullptr);

private:
    QFrame* card;
    QToolButton* profileButton;
    //QToolButton* notifButton;
    QPushButton* newTask;
    QHBoxLayout* cardLayout;
    QVBoxLayout* mainLayout;

};