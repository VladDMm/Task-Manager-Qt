#include "headers/User.h"
#include "headers/CentralDatabaseClass.h"

void User::change_password(std::string_view password)
{
	db.change_password(password);
}

void User::change_username(std::string_view username)
{
	db.change_username(username);
}
void User::add_user()
{
	db.add_user(*this);
}