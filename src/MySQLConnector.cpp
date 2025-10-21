#include "headers/MySQLConnector.h"
#include <windows.h>
#include <fstream>

std::string getExeDirectory()
{
	char buffer[260];
	GetModuleFileNameA(NULL, buffer, 260);
	std::string fullPath(buffer);

	size_t pos = fullPath.find_last_of("\\/");
	return (pos == std::string::npos) ? "" : fullPath.substr(0, pos);
}

void MySQLConnector::get_credentials_from_file(std::map<std::string, std::string> &conn_parameters)
{
	std::string line = "";
	std::string exeDir = getExeDirectory();
    std::ifstream is(exeDir + "\\db_settings.conf");

	if (!is.is_open())
	{
		throw std::runtime_error("Exception opening/reading file!");
	}
	while (std::getline(is, line))
	{
		if (line.empty() || line[0] == '#' || line[0] == '[')
			continue;
		auto delimiterPos = line.find("=");

		if (delimiterPos != std::string::npos)
		{
			std::string key = line.substr(0, delimiterPos);
			std::string value = line.substr(delimiterPos + 1);
			conn_parameters[key] = value;
		}
	}
	is.close();
	if (conn_parameters.empty())
		throw std::runtime_error("File db_settings.conf is empty! No data for connection");
}

void MySQLConnector::connect()
{
	try
	{
		this->get_credentials_from_file(this->conn_parameters);

		driver = sql::mysql::get_driver_instance();
		con = std::unique_ptr<sql::Connection>(driver->connect(conn_parameters["url"] +
			":" + conn_parameters["port"], conn_parameters["user"], conn_parameters["password"]));

		if (!con)
			throw std::runtime_error("Connection failed");

		con->setSchema(conn_parameters["db_name"]);
	}
	catch (const sql::SQLException &e)
	{
		std::cout << e.what() << std::endl;
		std::cout << e.getSQLState() << std::endl;
		exit(1);
	}
	catch (std::bad_alloc &e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}
	catch (const std::ifstream::failure &e)
	{
		std::cerr << "Exception opening/reading file!\n";
		std::cerr << e.what();
		exit(1);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what();
		exit(1);
	}
}

std::shared_ptr<sql::Connection> MySQLConnector::get_connection() {
	sql::Driver* driver = get_driver_instance();
	sql::Connection* raw = driver->connect(this->conn_parameters["url"] +
		":" + conn_parameters["port"], conn_parameters["user"], conn_parameters["password"]);
	raw->setSchema(conn_parameters["db_name"]);

	return std::shared_ptr<sql::Connection>(raw);
}

sql::Driver* MySQLConnector::get_driver()
{
	return driver;
}
