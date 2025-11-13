#pragma once

#include <QWidget>

class QFrame;
class QVBoxLayout;
class QPushButton;
class QListWidget;
class AddTaskWindow;
class AddCategoryWindow;
class EditTaskWindow;

class MyTasksWidget : public QWidget
{
    Q_OBJECT

private:
    AddTaskWindow*      task_window;
    AddCategoryWindow*  category_window;
    EditTaskWindow*     edit_task_window;

    QFrame*             card_tasks_frame;
    QFrame*             card_categories_frame;
    QFrame*             card_comments_frame;
    // layout for objects in frame
    QVBoxLayout*        vbox_categories;
    QVBoxLayout*        vbox_comments;
    QVBoxLayout*        vbox_tasks;
    // 
    QPushButton*        new_categorie_btn;
    QPushButton*        new_comment_btn;
    QPushButton*        new_task_btn;
    //
    QListWidget*        task_list;
    QListWidget*        category_list;
    QListWidget*        comment_list;

signals:
    void new_task_btn_clicked();
    void new_categorie_btn_clicked();
    void new_comment_btn_clicked();

public slots:
    void show_add_task_window();
    void show_add_category_window();
    void show_edit_task_window();
    void refresh_task_list();
    void refresh_category_list();
private slots:
    void showContextMenu(const QPoint& pos);

public:
    MyTasksWidget(QWidget* parent = nullptr);


};