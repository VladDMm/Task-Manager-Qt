#pragma once

#include <QWidget>

class QFrame;
class QListWidget;
class QVBoxLayout;

class DashboardWidget : public QWidget
{
    Q_OBJECT

private:
    QFrame* card_tasks_frame;
    QFrame* card_categories_frame;
    QFrame* card_comments_frame;
    // layout for objects in frame
    QVBoxLayout* vbox_categories;
    QVBoxLayout* vbox_comments;
    QVBoxLayout* vbox_tasks;
    //
    QListWidget* task_list;      // -> card_tasks_frame
    QListWidget* category_list;  // -> card_categories_frame
    QListWidget* comment_list;   // -> card_comments_frame


public:
    DashboardWidget(QWidget* parent = nullptr);


};