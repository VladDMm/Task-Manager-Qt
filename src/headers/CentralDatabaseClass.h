#pragma once

#include "src/headers/IMySQLService.h"
#include <string_view>

class IDatabaseService;
class TaskService;
class User;
class UserService;

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
	void add_user(UserService &u);
	void change_username(UserService &u, std::string_view usern);
	void change_password(UserService &u, std::string_view pw);

	void add_task(std::unordered_map<int, Task> &tasks);
	void add_category(TaskService &t);
	void add_task_to_category(TaskService &t);
	void change_category_for_task(TaskService &t);
	void change_task(TaskService &t);

	void delete_task(TaskService &t);
	void delete_category(TaskService &t);

	~Database() {
		//std::cout << "[~Database] Destructor called\n";
	}
};

extern Database db;
