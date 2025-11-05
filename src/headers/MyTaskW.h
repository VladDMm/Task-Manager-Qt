#pragma once

#include <QWidget>

class QFrame;
class QHBoxLayout;
class QPushButton;

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

    QPushButton* new_categorie_btn;
    QPushButton* new_comment_btn;
    QPushButton* new_task_btn;

signals:
    void new_task_btn_clicked();
    void new_categorie_btn_clicked();
    void new_comment_btn_clicked();

private slots:
    void show_add_task_window();
    void show_add_category_window();

public:
    My_Tasks_Widget(QWidget* parent = nullptr);


};