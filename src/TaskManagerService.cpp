#include "headers/TaskManagerService.h"
#include "headers/CentralDatabaseClass.h"

#include <algorithm>
#include <string>

//==============================================================================================
void TaskService::initializing_data()
{
	auto cat_map = get_categories();
	for (auto& [id, Category] : cat_map)
	{
		categories.emplace(id, std::move(Category));
	}

	auto comments_map = get_comments();
	for (auto& [id, Comment] : comments_map)
	{
		comments.emplace(id, std::move(Comment));
	}
	auto task_map = get_tasks();
	for (auto& [id, task] : task_map)
	{
		tasks.emplace(id, std::move(task));
	}
}

uint16_t TaskService::add_task(Task task)
{
	task.set_id(db.add_task(task));
	tasks[task.get_id()] = task;
	return task.get_id();
}

uint16_t TaskService::add_category(std::string_view category_title)
{
	uint16_t categ_id = db.add_category(category_title);
	categories[categ_id] = Category{ categ_id, category_title.data() };
	return categ_id;
}

void TaskService::add_task_to_category(uint16_t task_id, uint16_t category_id)
{
	// add to db
	db.add_task_to_category(task_id, category_id);
	// add local
	auto it = tasks.find(task_id);
	if (it != tasks.end())
	{
		it->second.task_category.first = task_id;
		it->second.task_category.second = categories.find(category_id)->second;
	}
}

void TaskService::change_category_for_task(uint16_t task_id, uint16_t category_id)
{
	
}

void TaskService::change_task(Task &)
{
	
}

void TaskService::change_categorie(uint16_t category_id, std::string_view category_title)
{
	
}

std::unordered_map<uint16_t, Category> TaskService::get_categories()
{
	if(categories.empty())
		return db.get_categories();

	return categories;
}

std::pair<uint16_t, Category> TaskService::get_category_by_id(uint16_t& id)
{
	auto it = categories.find(id);
	if (it != categories.end())
		return std::make_pair(it->first, std::move(it->second));

	throw ("Id not exist");
}

std::unordered_map<uint16_t, Comment> TaskService::get_comments()
{
	if(categories.empty())
		return db.get_comments();

	return comments;
}

std::unordered_map<uint16_t, Task> TaskService::get_tasks()
{
	if(tasks.empty())
		return db.get_tasks();

	return tasks;
}

Task TaskService::get_task(uint16_t id)
{
	auto it = tasks.find(id);
	return it != tasks.end() ? it->second : Task();
}

void TaskService::update_task_status(uint16_t id, const TaskStatus& new_status)
{
	auto it = tasks.find(id);
	if (it != tasks.end())
	{
		it->second.t_status = new_status;
	}
}

void TaskService::delete_task(uint16_t id)
{
	auto it = tasks.find(id);
	if (it != tasks.end())
	{
		db.delete_task(id);
		tasks.erase(id);
	}
}

void TaskService::delete_category(uint16_t category_id)
{
	
}

void TaskService::delete_task_from_category(uint16_t category_id)
{
	
}

