#pragma once

#include "src/headers/IMySQLService.h"
#include <string_view>

class IDatabaseService;
class TaskService;
class User;

class Database
{
private:
	IDatabaseService *db_service;

public:
	Database(IDatabaseService &service) : db_service(&service) {}

	Database(const Database&) = delete;
	Database& operator=(const Database&) = delete;

	// get-eri ; set-eri alte functii cu operatiuni pe baza de date care apeleaza ulterior functii din mysqlservice sau alt service
	User get_user(std::string_view user, std::string_view pass);
	void add_user(User &u);
	void change_username(std::string_view username);
	void change_password(std::string_view password);

	uint16_t add_task(const Task& task);
	uint16_t add_category(std::string_view category_title);
	void add_task_to_category(uint16_t task_id, uint16_t category_id);
	void change_category_for_task(TaskService &t);
	void change_task(TaskService &t);
	std::unordered_map<uint16_t, Category> get_categories();
	std::unordered_map<uint16_t, Comment> get_comments();
	std::unordered_map<uint16_t, Task> get_tasks();
	void delete_task(TaskService &t);
	void delete_category(TaskService &t);

	~Database() {
		//std::cout << "[~Database] Destructor called\n";
	}
};

extern Database db;
