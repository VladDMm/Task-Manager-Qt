#pragma once

#include <QWidget>
#include "MainWindow.h"

class QFrame;
class QToolButton;
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;

class Top_Bar_Widget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card;
    QToolButton* profileButton = nullptr;
    //QToolButton* notifButton;
    QPushButton* newTask = nullptr;
    QHBoxLayout* cardLayout;
    QVBoxLayout* mainLayout;

public:
    explicit Top_Bar_Widget(QWidget* parent = nullptr);

public slots:
    void show_buttons_in_top_bar();
    void clear_top_bar_buttons();
};