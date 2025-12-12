#include "headers/TaskManagerService.h"
#include <algorithm>
#include <string>

//==============================================================================================
void TaskService::initializing_data()
{
	// initializing categories
	auto cat_map = get_categories();
	for (auto& [id, Category] : cat_map)
	{
		categories.emplace(id, std::move(Category));
	}
	// initializing comments
	auto comments_map = get_comments();
	for (auto& [id, Comment] : comments_map)
	{
		comments.emplace(id, std::move(Comment));
	}
	// initializing tasks
	auto task_map = get_tasks();
	for (auto& [id, task] : task_map)
	{
		tasks.emplace(id, std::move(task));
	}
}
//==============================================================================================
uint16_t TaskService::add_task(Task task)
{
	try
	{
		task.set_id(db_service->add_task(task));
		tasks[task.get_id()] = task;
		return task.get_id();
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
}
//==============================================================================================
uint16_t TaskService::add_category(std::string_view category_title)
{
	try
	{
		uint16_t categ_id = db_service->add_category(category_title);
		categories[categ_id] = Category{ categ_id, category_title.data() };
		return categ_id;
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
	
}
//==============================================================================================
void TaskService::add_comment(std::string_view text)
{
	try
	{
		auto comment_id = db_service->add_comment(text);
		comments[comment_id] = Comment{ comment_id, text.data() };
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error (e.what());
	}
}
//==============================================================================================
void TaskService::add_task_to_category(uint16_t task_id, Category category)
{
	try
	{
		db_service->add_task_to_category(task_id, category.id);
		// add local
		auto it = tasks.find(task_id);
		if (it != tasks.end())
		{
			it->second.task_category = categories.find(category.id)->second;
		}
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
}
//==============================================================================================
void TaskService::update_category_for_task(uint16_t task_id, Category category)
{
	try
	{
		db_service->update_category_for_task(task_id, category.id);
		auto it = tasks.find(task_id);
		it->second.task_category = std::move(category);
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
}
//==============================================================================================
void TaskService::update_task(Task& task)
{
	try
	{
		db_service->update_task(task);
		tasks[task.get_id()] = std::move(task);
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
}
//==============================================================================================
void TaskService::update_category(Category& category)
{
	try
	{
		db_service->update_category(category);
		categories[category.id] = std::move(category);
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}

}
//==============================================================================================
void TaskService::update_comment(Comment& comment)
{
	try
	{
		db_service->update_comment(comment);
		comments[comment.id] = std::move(comment);

	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
}
//==============================================================================================
std::unordered_map<uint16_t, Category> TaskService::get_categories()
{
	try
	{
		if (categories.empty())
			return db_service->get_categories();

		return categories;
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
	
}
//==============================================================================================
std::pair<uint16_t, Category> TaskService::get_category_by_id(uint16_t& id)
{
	try
	{
		auto it = categories.find(id);
		if (it != categories.end())
			return std::make_pair(it->first, it->second);
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}


	
}
//==============================================================================================
std::unordered_map<uint16_t, Comment> TaskService::get_comments()
{
	try
	{
		if (comments.empty())
			return db_service->get_comments();

		return comments;
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
}
//==============================================================================================
std::unordered_map<uint16_t, Task> TaskService::get_tasks()
{
	try
	{
		if (tasks.empty())
			return db_service->get_tasks();

		return tasks;
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
	
}
//==============================================================================================
Task TaskService::get_task(uint16_t id)
{
	auto it = tasks.find(id);
	return it->second;
}
//==============================================================================================
void TaskService::update_task_status(uint16_t id, const TaskStatus& new_status)
{
	auto it = tasks.find(id);
	if (it != tasks.end())
	{
		it->second.t_status = new_status;
	}
}
//==============================================================================================
void TaskService::delete_task(uint16_t id)
{
	try
	{
		auto it = tasks.find(id);
		if (it != tasks.end())
		{
			db_service->delete_task(id);
			tasks.erase(id);
		}
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
	
}
//==============================================================================================
void TaskService::delete_category(uint16_t category_id)
{
	try
	{
		db_service->delete_category(category_id);
		categories.erase(category_id);

		for (auto& obj : tasks) {
			if (obj.second.task_category.id == category_id) {
				obj.second.task_category = { 0, "" };
			}
		}
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
	
}
//==============================================================================================
void TaskService::delete_comment(uint16_t comment_id)
{
	try
	{
		db_service->delete_comment(comment_id);
		comments.erase(comment_id);
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}
}
//==============================================================================================
void TaskService::delete_task_from_category(uint16_t task_id, uint16_t category_id)
{
	try
	{
		db_service->delete_task_from_category(task_id, category_id);
		auto it = tasks.find(task_id);
		it->second.task_category = { 0, "" };
	}
	catch (const sql::SQLException& e)
	{
		throw std::runtime_error(e.what());
	}

}
//==============================================================================================
