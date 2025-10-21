#include "headers/TaskManagerService.h"
#include "headers/CentralDatabaseClass.h"

int TaskService::task_id_cache = 0;
int TaskService::category_id_cache = 0;
int TaskService::task_categories_id_cache = 0;

void TaskService::add_task(Task &t)
{
    t.task_id = ++task_id_cache;
    tasks[task_id_cache] = t;
}

void TaskService::add_category(std::string_view category_title)
{
	
}

void TaskService::add_task_to_category(int task_id, int category_id)
{
	
}

void TaskService::change_category_for_task(int task_id, int category_id)
{
	
}

void TaskService::change_task(Task &)
{
	
}

void TaskService::change_categorie(int category_id, std::string_view category_title)
{
	
}

int TaskService::get_task_id()
{
    return 0;
}

int TaskService::get_user_id()
{
    return 0;
}

std::string_view TaskService::get_title()
{
    return 0;
}

std::string_view TaskService::get_description()
{
    return 0;
}

std::string TaskService::get_task_status()
{
	//switch (this->task_->t_status)
	//{
	//case 0:
	//	return "todo";
	//case 1:
	//	return "in_progress";
	//case 2:
	//	return "done";
	//default:
	//	return "UNKNOW";
	//}
    return 0;
}

std::string TaskService::get_task_priority()
{
	//switch (this->task_->t_priority)
	//{
	//case 0:
	//	return "low";
	//case 1: 
	//	return "medium";
	//case 2:
	//	return "high";
	//default:
	//	return "UNKNOW";
	//}
    return 0;
}

std::string_view TaskService::get_due_date()
{
	//return this->task_->due_date;
    return 0;
}

std::string_view TaskService::get_created_at()
{
	//return this->task_->created_at;
    return 0;
}

std::string_view TaskService::get_updated_at()
{
	//return this->task_->updated_at;
    return 0;
}

void TaskService::delete_task(int task_id)
{

}

void TaskService::delete_category(int category_id)
{
	
}

void TaskService::delete_task_from_category(int category_id)
{
	
}

