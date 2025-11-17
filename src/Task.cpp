#include "headers/Task.h"


std::string_view Task::get_title() const
{
	return this->title;
}

std::string_view Task::get_description() const
{
	return this->description;
}

std::string Task::get_task_status_to_string() const
{
	switch (this->t_status)
	{
	case TaskStatus::TO_DO:
		return "To do";
	case TaskStatus::IN_PROGRESS:
		return "In Progress";
	case TaskStatus::DONE:
		return "Done";
	default:
		return "UNKNOW";
	}
}

uint16_t Task::get_task_status_to_uint() const
{
	return static_cast<uint16_t>(t_status);
}

std::string Task::get_task_priority_to_string() const
{
	switch (this->t_priority)
	{
	case TaskPriority::LOW:
		return "Low";
	case TaskPriority::MEDIUM:
		return "Medium";
	case TaskPriority::HIGH:
		return "High";
	default:
		return "UNKNOW";
	}
}

uint16_t Task::get_task_priority_to_uint() const
{
	return static_cast<uint16_t>(t_priority);
}

uint16_t Task::get_id_category() const
{
	return task_category.id;
}

void Task::set_id(const uint16_t &id)
{
	this->task_id = id;
}

void Task::set_category(const uint16_t& id, std::string_view title)
{
	task_category = { id, title.data() };
}

void Task::set_category_id(const uint16_t& id)
{
	task_category.id = id;
}
