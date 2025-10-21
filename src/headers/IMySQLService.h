#pragma once

#include "UserService.h"
#include "TaskManagerService.h"
#include "mysql/jdbc.h"
#include "User.h"

class IDatabaseService
{
public:
	// Users Methods
	virtual User get_user(std::string_view user, std::string_view pass) = 0;
	virtual void add_user(UserService &)								= 0;
	virtual void change_password(std::string_view pw)					= 0;
	virtual void change_username(std::string_view usern)				= 0;

	// Tasks Methods
	virtual void add_task(std::unordered_map<int, Task> &)				= 0;
	virtual void add_category(TaskService &)							= 0;
	virtual void add_task_to_category(TaskService &)					= 0;
	virtual void change_category_for_task(TaskService &)				= 0;
	virtual void change_task(TaskService &)								= 0;
	virtual void delete_task(TaskService &)								= 0;
	virtual void delete_category(TaskService &)							= 0;

	virtual ~IDatabaseService()											= default;
};


class MySQLService : public IDatabaseService
{
private:
	std::shared_ptr<sql::Connection> con;

public:
	MySQLService(std::shared_ptr<sql::Connection> conn) : con(std::move(conn)) {}

	User get_user(std::string_view user, std::string_view pass)	override;

	void add_user(UserService &)								override;
	void change_username(std::string_view usern)				override;
	void change_password(std::string_view pw)					override;
														
	void add_task(std::unordered_map<int, Task> &tasks)			override;
	void add_category(TaskService &)							override;
	void add_task_to_category(TaskService &)					override;
	void change_category_for_task(TaskService &)				override;
	void change_task(TaskService &)								override;
														
	void delete_task(TaskService &)								override;
	void delete_category(TaskService &)							override;

	~MySQLService() = default;
};	

extern MySQLService msql_srv;