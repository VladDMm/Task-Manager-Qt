#pragma once
#ifndef IUSER_SERVICE_H
#define IUSER_SERVICE_H

#include <string_view>

#include "User.h"

class User;

class UserService
{
private:
	User *user_;
public:
	UserService(User &user) : user_(&user) {}
	UserService() {}
	UserService& operator=(User &u);

	std::string_view get_username() const;
	std::string_view get_password()	const;
	void add_user();
	void change_password(std::string_view pw);
	void change_username(std::string_view usern);

};
extern UserService user_srv;
#endif // !IUSER_SERVICE_H
