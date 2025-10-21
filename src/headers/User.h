#pragma once
#ifndef USER_H
#define USER_H

#include <string>
#include <string_view>

class User
{
	friend class UserService;
	
private:
	int id;
	std::string username;
	std::string password_hash;

public:
	User() {}

	User(int id, std::string_view username, std::string_view password_hash)
		: id(id), username(username), password_hash(password_hash) {};

	User(std::string_view username, std::string_view password_hash)
		: username(username), password_hash(password_hash) {};

	operator bool() const
	{
		return !(username.empty() && password_hash.empty());
	}

	~User()
	{
		//std::cout << "[~User] Destructor called\n";
	}
};
extern User current_user;
#endif // !USER_H
