#pragma once

#include <memory>
#include <map>
#include "mysql/jdbc.h"

class MySQLConnector
{
private:
	sql::Driver							*driver;
	std::shared_ptr<sql::Connection>	con;
	std::map<std::string, std::string>  conn_parameters; /* url; port; user; password; db_name */

	void get_credentials_from_file(std::map<std::string, std::string> &conn_parameters);

public:
	MySQLConnector() { connect(); }

	void connect();

	std::shared_ptr<sql::Connection> get_connection();
	sql::Driver *get_driver();

	~MySQLConnector() {
		//std::cout << "[~MySQLConnector] Destructor called\n";
	}
};

extern MySQLConnector my_sql;
