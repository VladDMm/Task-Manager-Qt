#pragma once

#include <QWidget>

class QFrame;
class QHBoxLayout;

class My_Tasks_Widget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card_tasks_frame;
    QFrame* card_categories_frame;
    QFrame* card_comments_frame;
    // layout for objects in frame
    QHBoxLayout* hrz_card_categories_objects;
    QHBoxLayout* hrz_card_comments_objects;
    QHBoxLayout* hrz_card_tasks_objects;

public:
    My_Tasks_Widget(QWidget* parent = nullptr);


};