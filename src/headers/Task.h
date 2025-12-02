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
	uint16_t		 task_id;
	std::string		 title;
	std::string		 description;
	TaskStatus		 t_status;
	TaskPriority	 t_priority;

	Category task_category; // id category, name category

public:

	//Task() {}

	//Task(uint16_t id, std::string_view title, std::string_view description,
	//	TaskStatus status = TaskStatus::TO_DO, TaskPriority priority = TaskPriority::LOW)
	//	:task_id(id), title(title.data()), description(description.data()), t_status(status), t_priority(priority) 
	//{
	//	task_category = { 0, "" };
	//}
	
	Task(uint16_t id = 0, std::string_view title = "", std::string_view description = "", TaskStatus status = TaskStatus::TO_DO, 
		TaskPriority priority = TaskPriority::LOW, std::string_view category_name = "", uint16_t category_id = 0 )
		:task_id(id), title(title.data()), description(description.data()), t_status(status), t_priority(priority)
	{
		task_category = { category_id, category_name.data() };
	}

	uint16_t get_id() const { return task_id; }
	std::string_view get_title() const;
	std::string_view get_description() const;
	std::string get_task_status_to_string() const;
	std::uint16_t get_task_status_to_uint() const;
	std::string get_task_priority_to_string() const;
	uint16_t get_task_priority_to_uint() const;
	uint16_t get_id_category() const;

	void set_id(const uint16_t &id);
	void set_category(const uint16_t& id, std::string_view title);
	void set_category_id(const uint16_t& id);
};