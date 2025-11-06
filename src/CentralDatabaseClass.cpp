#include "headers/CentralDatabaseClass.h"

User Database::get_user(std::string_view user, std::string_view pass)
{
	return db_service->get_user(user, pass);
}

void Database::add_user(User &u)
{
	db_service->add_user(u);
}

void Database::change_username(std::string_view username)
{
}

void Database::change_password(std::string_view password)
{
}

uint16_t Database::add_task(const Task& task)
{
	return db_service->add_task(task);
}

uint16_t Database::add_category(std::string_view category_title)
{
    return db_service->add_category(category_title);
}

void Database::add_task_to_category(uint16_t task_id, uint16_t category_id)
{
    db_service->add_task_to_category(task_id, category_id);
}

void Database::change_category_for_task(TaskService & t)
{
  
}

void Database::change_task(TaskService & t)
{
   
}

std::unordered_map<uint16_t, Category> Database::get_categories()
{
    return db_service->get_categories();
}

std::unordered_map<uint16_t, Comment> Database::get_comments()
{
    return db_service->get_comments();
}

std::unordered_map<uint16_t, Task> Database::get_tasks()
{
    return db_service->get_tasks();
}

void Database::delete_task(TaskService & t)
{
    
}

void Database::delete_category(TaskService & t)
{
    
}
