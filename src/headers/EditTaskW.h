#pragma once

#include <QWidget>

class QFrame;
class QPushButton;
class QLineEdit;
class QComboBox;
class QTextEdit;
class QListWidgetItem;
struct Category;

class EditTaskWindow : public QWidget
{
    Q_OBJECT

private:
    uint16_t        priority_id;
    // se foloseste pentru a pastra id-ul original la categorie pentru a opera cu update in DB corect
    uint16_t        original_category_id; 
    // se foloseste in caz ca se selecteaza alta categorie
    uint16_t        temporar_category_id; 
    QString         category_name;
    uint16_t        status_id;

    QFrame*         edit_frame;
    QLineEdit*      title_line;
    QTextEdit*      description_line;
    QComboBox*      categorie_item;
    QComboBox*      priority_lvl_item;
    QComboBox*      status_lvl_item;
    QPushButton*    cancel_btn;
    QPushButton*    confirm_btn;

    QListWidgetItem* task_item;

private slots:
    void confirm_btn_pushed();
    void closeEvent(QCloseEvent* event);

public slots:
    void initialize_components();

signals:
    void windowClosed();

public:
    EditTaskWindow(QWidget* parent = nullptr);
    void set_task_item(QListWidgetItem* item);

};