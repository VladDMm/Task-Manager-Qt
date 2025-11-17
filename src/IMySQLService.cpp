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

void MySQLService::add_user(User& user)
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
	pstmt->setString(4, sql::SQLString(task.get_task_status_to_string().data()));
	pstmt->setString(5, sql::SQLString(task.get_task_priority_to_string().data()));

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
		// return real id for category
		STMT stmt{ this->con->createStatement() };
		RES_SET res = RES_SET(stmt->executeQuery("SELECT LAST_INSERT_ID() AS id"));
		if (res->next())
			return res->getInt("id");
	}

	return 0;
}

void MySQLService::add_task_to_category(uint16_t& task_id, uint16_t& category_id)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"INSERT INTO task_category(task_id, category_id, user_id) VALUES (?, ?, ?)"
	));

	pstmt->setInt(1, task_id);
	pstmt->setInt(2, category_id);
	pstmt->setInt(3, current_user.get_id());

	pstmt->executeUpdate();
}

void MySQLService::update_category_for_task(uint16_t& task_id, uint16_t& category_id)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement("UPDATE task_category SET category_id=? WHERE task_id = ? AND user_id = ?"));
	pstmt->setInt(1, category_id);
	pstmt->setInt(2, task_id);
	pstmt->setInt(3, current_user.get_id());

	pstmt->executeUpdate();
}

void MySQLService::update_category(Category& category)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement("UPDATE categories SET title=? WHERE id = ? AND user_id = ?"));
	pstmt->setString(1, category.title);
	pstmt->setInt(2, category.id);
	pstmt->setInt(3, current_user.get_id());

	pstmt->executeUpdate();
}

void MySQLService::update_task(Task& task)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement("UPDATE tasks SET title=?, description=?, status=?, priority=? WHERE id = ? AND user_id = ?"));
	pstmt->setString(1, task.get_title().data());
	pstmt->setString(2, task.get_description().data());
	pstmt->setString(3, task.get_task_status_to_string().data());
	pstmt->setString(4, task.get_task_priority_to_string());
	pstmt->setInt(5, task.get_id());
	pstmt->setInt(6, current_user.get_id());

	pstmt->executeUpdate();
}

std::unordered_map<uint16_t, Category> MySQLService::get_categories()
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"SELECT id, title FROM categories WHERE user_id = ?"
	));
	pstmt->setInt(1, current_user.get_id());
	RES_SET res = RES_SET(pstmt->executeQuery());

	std::unordered_map<uint16_t, Category> local_result;
	while (res->next())
	{
		uint16_t id;
		std::string title;
		id = res->getUInt("id");
		title = res->getString("title");
		local_result.emplace(id, Category{ id, std::move(title) });
	}

	return local_result;
}

std::unordered_map<uint16_t, Comment> MySQLService::get_comments()
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"SELECT id, text FROM comments WHERE user_id = ?"
	));
	pstmt->setInt(1, current_user.get_id());
	RES_SET res = RES_SET(pstmt->executeQuery());

	std::unordered_map<uint16_t, Comment> local_result;
	while (res->next())
	{
		uint16_t id;
		std::string text;
		id = res->getUInt("id");
		text = res->getString("title");
		local_result.emplace(id, Comment{ id, std::move(text) });
	}

	return local_result;
}

std::unordered_map<uint16_t, Task> MySQLService::get_tasks()
{
	std::unordered_map<uint16_t, Task> local_result;

	// get all tasks for user
	{
		PSTMT pstmt = PSTMT(this->con->prepareStatement(
			"SELECT id, title, description, status, priority FROM tasks WHERE user_id = ?"
		));
		pstmt->setInt(1, current_user.get_id());
		RES_SET res = RES_SET(pstmt->executeQuery());

		while (res->next())
		{
			uint16_t id;
			std::string title;
			std::string description;
			std::string status;
			std::string priority;

			id = res->getUInt("id");
			title = res->getString("title");
			description = res->getString("description");
			status = res->getString("status");
			priority = res->getString("priority");

			uint16_t u_status, u_priority;
			switch (status[0])
			{
			case 'T': u_status = 0; break;
			case 'I': u_status = 1; break;
			case 'D': u_status = 2; break;
			default:
				u_status = 0;
				break;
			}

			switch (priority[0])
			{
			case 'L': u_priority = 0; break;
			case 'M': u_priority = 1; break;
			case 'H': u_priority = 2; break;
			default:
				break;
			}

			local_result.emplace(id, (Task{ id, title, description,
				static_cast<TaskStatus>(u_status), static_cast<TaskPriority>(u_priority) }));
		}

	}
	// inititalizing all task with his category
	{
		auto it = local_result.begin();

		while (it != local_result.end())
		{
			PSTMT pstmt = PSTMT(this->con->prepareStatement(
				"SELECT tk.category_id AS id, c.title AS title FROM categories c "
				" LEFT JOIN task_category tk ON tk.category_id = c.id "
				" WHERE tk.task_id = ? AND tk.user_id = ?"
			));
			pstmt->setInt(1, it->first);
			pstmt->setInt(2, current_user.get_id());
			RES_SET res = RES_SET(pstmt->executeQuery());

			while (res->next())
			{
				uint16_t id;
				std::string title;

				id = res->getUInt("id");
				title = res->getString("title");

				it->second.set_category(id, title);
			}
			++it;
		}
		
	}
	
	return local_result;
}

int16_t MySQLService::delete_task(uint16_t& task_id)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"DELETE FROM tasks WHERE id = ? AND user_id = ?"
	));

	pstmt->setInt(1, task_id);
	pstmt->setInt(2, current_user.get_id());
	
	return pstmt->executeUpdate();
}

int16_t MySQLService::delete_category(uint16_t& category_id)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"DELETE FROM categories WHERE id = ? AND user_id = ?"
	));

	pstmt->setInt(1, category_id);
	pstmt->setInt(2, current_user.get_id());

	return pstmt->executeUpdate();
}

void MySQLService::delete_task_from_category(uint16_t task_id, uint16_t category_id)
{
	PSTMT pstmt = PSTMT(this->con->prepareStatement(
		"DELETE FROM task_category WHERE task_id = ? AND category_id = ? AND user_id = ?"
	));

	pstmt->setInt(1, task_id);
	pstmt->setInt(2, category_id);
	pstmt->setInt(3, current_user.get_id());

	pstmt->executeUpdate();
}