#include "headers/User.h"
#include "headers/IMySQLService.h"

void User::change_password(std::string_view password)
{
	db_service->change_password(password);
}

void User::change_username(std::string_view username)
{
	db_service->change_username(username);
}
void User::add_user()
{
	db_service->add_user(*this);
}