#pragma once

#include "EnumTypes.h"
#include "TaskManagerService.h"

#include <string_view>
#include <string>
#include <unordered_map>

struct Category
{
	uint16_t	id;
	std::string title;
};

struct Comment {
	uint16_t	id;
	std::string description;
};

class Task
{
	friend class TaskService;

private:
	int				 task_id;
	std::string		 title;
	std::string		 description;
	TaskStatus		 t_status;
	TaskPriority	 t_priority;

	std::pair<uint16_t, Category> task_category; // id task + (id category, name category)

public:

	Task() {}

	Task(uint16_t id, std::string_view title, std::string_view description, TaskStatus status = TaskStatus::TO_DO, TaskPriority priority = TaskPriority::LOW)
		:task_id(id), title(title.data()), description(description.data()), t_status(TaskStatus::TO_DO), t_priority(priority) {}
	
	Task(uint16_t id, std::string_view title, std::string_view description, std::string_view category_name = "", uint16_t category_id = 0, TaskStatus status = TaskStatus::TO_DO, TaskPriority priority = TaskPriority::LOW)
		:task_id(id), title(title.data()), description(description.data()), t_status(status), t_priority(priority)
	{
		task_category.first = task_id;
		task_category.second = { category_id, category_name.data() };
	}

	int16_t get_id() const { return task_id; }
	std::string_view get_title() const;
	std::string_view get_description() const;
	std::string get_task_status() const;
	std::string get_task_priority() const;
	uint16_t get_id_category() const;

	void set_id(const uint16_t &id);
};