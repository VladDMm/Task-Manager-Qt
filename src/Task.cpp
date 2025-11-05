#include "headers/Task.h"


std::string_view Task::get_title() const
{
	return this->title;
}
std::string_view Task::get_description() const
{
	return this->description;
}
std::string Task::get_task_status() const
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
std::string Task::get_task_priority() const
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

uint16_t Task::get_id_category() const
{
	return task_category.second.id;
}

void Task::set_id(const uint16_t &id)
{
	this->task_id = id;
}