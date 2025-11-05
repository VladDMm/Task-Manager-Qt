#pragma once

#include "TaskManagerService.h"
#include "Task.h"
#include "mysql/jdbc.h"
#include "User.h"

#include <unordered_map>

struct Category;

class IDatabaseService
{
public:
	// Users Methods
	virtual User get_user(std::string_view user, std::string_view pass) = 0;
	virtual void add_user(User &)										= 0;
	virtual void change_password(std::string_view password)				= 0;
	virtual void change_username(std::string_view username)				= 0;

	// Tasks Methods
	virtual uint16_t add_task(const Task&)								= 0;
	virtual uint16_t add_category(std::string_view category_title)		= 0;
	virtual void add_task_to_category(uint16_t, uint16_t)				= 0;
	virtual void change_category_for_task(TaskService &)				= 0;
	virtual std::unordered_map<uint16_t, Category> get_categories()		= 0;
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

	void add_user(User &)										override;
	void change_username(std::string_view usern)				override;
	void change_password(std::string_view pw)					override;
														
	uint16_t add_task(const Task& task)							override;
	uint16_t add_category(std::string_view category_title)		override;
	void add_task_to_category(uint16_t, uint16_t)				override;
	void change_category_for_task(TaskService &)				override;
	void change_task(TaskService &)								override;
	std::unordered_map<uint16_t, Category> get_categories()		override;
	void delete_task(TaskService &)								override;
	void delete_category(TaskService &)							override;

	~MySQLService() = default;
};	

extern MySQLService msql_srv;