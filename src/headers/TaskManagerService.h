#pragma once
#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include "EnumTypes.h"
#include "Task.h"

#include <string_view>
#include <unordered_map>
#include <vector>
#include <memory>

class Task;
struct Category;
struct Comment;

class TaskService
{
private:
	std::unordered_map<uint16_t, Task>		tasks;
	std::unordered_map<uint16_t, Category>	categories;
	std::unordered_map<uint16_t, Comment>	comments;
public:
	TaskService() { }

	//====== Task Methods =======
	void initializing_data();

	uint16_t add_task(Task task);
	uint16_t add_category(std::string_view category_title);
	void add_task_to_category(uint16_t task_id, Category category);
	void update_category_for_task(uint16_t task_id, Category category);
	void update_task(Task&);
	void update_category(Category& category);
	std::unordered_map<uint16_t, Category> get_categories();
	std::pair<uint16_t, Category> get_category_by_id(uint16_t& id);
	std::unordered_map<uint16_t, Comment> get_comments();
	std::unordered_map<uint16_t, Task> get_tasks();
	Task get_task(uint16_t id);

	void update_task_status(uint16_t id, const TaskStatus& new_status);
	// to do implement update task details

	void delete_task(uint16_t task_id);
	void delete_category(uint16_t category_id);
	void delete_task_from_category(uint16_t task_id, uint16_t category_id);

};	extern TaskService taskService_;

#endif // !TASK_SERVICE_H
