#pragma once

#include <QWidget>

class QFrame;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTextEdit;
class QListWidgetItem;
struct Category;

class EditCategoryWindow : public QWidget
{
    Q_OBJECT

private:
    uint16_t        priority_id;
    QString         priority_name;
    uint16_t        category_id;
    QString         category_name;

    QFrame*         edit_frame;
    QLineEdit*      title_line;
    QTextEdit*      description_line;
    QComboBox*      categorie_item;
    QComboBox*      priority_lvl_item;
    QComboBox*      status_lvl_item;
    QPushButton*    cancel_btn;
    QPushButton*    confirm_btn;
    QListWidgetItem* category_item;

private slots:
    void add_btn_pushed();
    void closeEvent(QCloseEvent* event);

public slots:
    void initialize_components();

signals:
    void windowClosed();

public:
    EditCategoryWindow(QWidget* parent = nullptr);
    void set_category_item(QListWidgetItem* item);
};