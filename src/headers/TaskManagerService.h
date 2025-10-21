#pragma once
#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

#include <string_view>
#include <string>
#include <unordered_map>

class Task;

enum class EntityState 
{
	NEW,
	MODIFIED,
	DELETED,
	SYNCED
};

class TaskService
{
private:
	static int task_id_cache;
	static int task_categories_id_cache;
	static int category_id_cache;

	std::unordered_map<int, Task> tasks;
	std::unordered_map<int, int> task_categories;
	std::unordered_map<int, std::string> categories;

	TaskService() = default;

public:

	TaskService(const TaskService&) = delete;
	TaskService &operator=(const TaskService &) = delete;

	static TaskService &get_instance()
	{
		static TaskService instance;
		return instance;
	}

	void add_task(Task &);
	void add_category(std::string_view category_title);
	void add_task_to_category(int task_id, int category_id);

	void change_category_for_task(int task_id, int category_id);
	void change_task(Task &);
	void change_categorie(int category_id, std::string_view category_title);

	int get_task_id();
	int get_user_id();
	std::string_view get_title();
	std::string_view get_description();
	std::string get_task_status();
	std::string get_task_priority();
	std::string_view get_due_date();
	std::string_view get_created_at();
	std::string_view get_updated_at();

	void delete_task(int task_id);
	void delete_category(int category_id);
	void delete_task_from_category(int category_id);
};

class Task
{
	friend class TaskService;
	enum task_status { todo, in_progress, done };
	enum priority	 { low, medium, high };

private:
	int				 task_id;
	int				 user_id;
	std::string		 title;
	std::string		 description;
	task_status		 t_status;
	priority		 t_priority;

	EntityState state = EntityState::NEW;

public:

	Task(int user_id, std::string_view title, std::string_view description)
		: user_id(user_id), title(title.data()), description(description.data()), t_status(todo), t_priority(low) {}

    Task() {}

	void mark_modified() { if (state == EntityState::SYNCED) state = EntityState::MODIFIED; }
	void mark_deleted() { state = EntityState::DELETED; }
	void mark_synced() { state = EntityState::SYNCED; }

	EntityState get_state() const { return state; }
};


#endif // !TASK_SERVICE_H
