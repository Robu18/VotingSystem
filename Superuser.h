#pragma once
#include <string>
#include <iostream>
#include "User.h"
#include "globals.h"

class Superuser: public User {
	std::string username = "Undefined";
	std::string password = "Undefined";
	static Superuser* super_user;
	Superuser();
public:
	static Superuser* getSuperuser();
	void setSuperuser(std::string first_name, std::string last_name, std::string pin, unsigned int age, std::string username, std::string password);
	const std::string getUsername();
	const std::string getPassword();
	void setUsername(std::string username);
	void setPassword(std::string password);
	void print() const;
};