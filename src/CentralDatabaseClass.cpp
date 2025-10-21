#include "headers/CentralDatabaseClass.h"

User Database::get_user(std::string_view user, std::string_view pass)
{
	return db_service->get_user(user, pass);
}

void Database::add_user(UserService &u)
{
	db_service->add_user(u);
}

void Database::change_username(UserService &u, std::string_view usern)
{
}

void Database::change_password(UserService &u, std::string_view pw)
{
}

void Database::add_task(std::unordered_map<int, Task> &tasks)
{
	if (tasks.empty())
		return;
	db_service->add_task(tasks);
}

void Database::add_category(TaskService & t)
{
    
}

void Database::add_task_to_category(TaskService & t)
{
    
}

void Database::change_category_for_task(TaskService & t)
{
  
}

void Database::change_task(TaskService & t)
{
   
}

void Database::delete_task(TaskService & t)
{
    
}

void Database::delete_category(TaskService & t)
{
    
}
