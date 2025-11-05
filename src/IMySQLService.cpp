#include "headers/IMySQLService.h"
#include "sodium.h"

using STMT = std::unique_ptr<sql::Statement>;
using PSTMT = std::unique_ptr<sql::PreparedStatement>;
using RES_SET = std::unique_ptr<sql::ResultSet>;

User MySQLService::get_user(std::string_view user, std::string_view pass)
{
	if (sodium_init() < 0) 
	{
		throw std::runtime_error("sodium_init failed\n");
	}

	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"SELECT id, username, password_hash FROM users WHERE username = ? LIMIT 1;"
	));
	pstmt->setString(1, user.data());
	RES_SET res = RES_SET(pstmt->executeQuery());

	if (!res->next()) 
	{
		throw std::runtime_error("Invalid username or password!");
	}

	int id = res->getInt("id");
	std::string username = res->getString("username");
	std::string stored_hash = res->getString("password_hash");

	// Verificare parola
	if (crypto_pwhash_str_verify(
		stored_hash.c_str(),
		pass.data(),
		pass.size()) != 0)
	{
		throw std::runtime_error("Invalid username or password!");
	}

	return User(id, username, stored_hash);
}

void MySQLService::add_user(User &user)
{
	if (sodium_init() < 0)
	{
		throw std::runtime_error("sodium_init failed\n");
	}


	// crypto_pwhash_OPSLIMIT_INTERACTIVE / _MODERATE / _SENSITIVE
	// crypto_pwhash_MEMLIMIT_INTERACTIVE / _MODERATE / _SENSITIVE
	const unsigned long long opslimit = crypto_pwhash_OPSLIMIT_MODERATE;
	const size_t memlimit = crypto_pwhash_MEMLIMIT_MODERATE;

	// buffer hash
	char hashed[crypto_pwhash_STRBYTES];

	if (crypto_pwhash_str(
		hashed,
		user.get_password().data(),
		user.get_password().size(),
		opslimit,
		memlimit) != 0)
		throw std::runtime_error("Crypto_pwhash_str failed");
	
	if (this->con == nullptr)
	{
		throw std::runtime_error("Con = nullptr!");

	}
	try {
		PSTMT pstmt = PSTMT(this->con->prepareStatement("INSERT INTO users(username, password_hash) VALUES (?, ?);"));
		pstmt->setString(1, user.get_username().data());
		pstmt->setString(2, hashed);
		pstmt->execute();
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what() << std::endl;
		std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
		std::cerr << "SQLState: " << e.getSQLStateCStr() << std::endl;

	}
}

void MySQLService::change_username(std::string_view usern)
{
}

void MySQLService::change_password(std::string_view pw)
{
}

uint16_t MySQLService::add_task(const Task& task)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
	"INSERT INTO tasks(user_id, title, description, status, priority) VALUES (?, ?, ?, ?, ?)"
	));
	
	pstmt->setInt(1, current_user.get_id());
	pstmt->setString(2, sql::SQLString(task.get_title().data()));
	pstmt->setString(3, sql::SQLString(task.get_description().data()));
	pstmt->setString(4, sql::SQLString(task.get_task_status().data()));
	pstmt->setString(5, sql::SQLString(task.get_task_priority().data()));
	
	if (pstmt->executeUpdate())
	{
		// return real id for task
		STMT stmt{ this->con->createStatement() };
		RES_SET res = RES_SET(stmt->executeQuery("SELECT LAST_INSERT_ID() AS id"));
		if (res->next())
			return res->getInt("id");
	}

	return 0;
}

uint16_t MySQLService::add_category(std::string_view category_title)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"INSERT INTO categories(title, user_id) VALUES (?, ?)"
	));

	pstmt->setString(1, sql::SQLString(category_title.data()));
	pstmt->setInt(2, current_user.get_id());

	if (pstmt->executeUpdate())
	{
		// return real id for task
		STMT stmt{ this->con->createStatement() };
		RES_SET res = RES_SET(stmt->executeQuery("SELECT LAST_INSERT_ID() AS id"));
		if (res->next())
			return res->getInt("id");
	}

	return 0;
}

void MySQLService::add_task_to_category(uint16_t task_id, uint16_t category_id)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"INSERT INTO task_categories(task_id, category_id, user_id) VALUES (?, ?, ?)"
	));

	pstmt->setInt(1, task_id);
	pstmt->setInt(2, category_id);
	pstmt->setInt(3, current_user.get_id());

	pstmt->executeUpdate();
}

void MySQLService::change_category_for_task(TaskService &)
{
 
}

void MySQLService::change_task(TaskService &)
{
   
}

std::unordered_map<uint16_t, Category> MySQLService::get_categories()
{
	STMT stmt = STMT(con->createStatement());

	RES_SET res = RES_SET(stmt->executeQuery("SELECT id, title FROM categories"));
	std::unordered_map<uint16_t, Category> local_res;
	
	while (res->next())
	{
		uint16_t id;
		std::string title;
		id = res->getUInt("id");
		title = res->getString("title");
		local_res.emplace(id, Category{ id, std::move(title) });
	}

	return local_res;
}

void MySQLService::delete_task(TaskService &)
{
   
}

void MySQLService::delete_category(TaskService &)
{
  
}



