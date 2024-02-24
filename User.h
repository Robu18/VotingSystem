#pragma once
#include "globals.h"
#include <string>
#include <iostream>

class User {
protected:
	std::string first_name = "Undefined";
	std::string last_name = "Undefined";
	std::string pin = "Undefined"; // Personal Identification Number
	bool voted = false;
	unsigned int age = User::minimum_age;
	static unsigned int minimum_age;
public:
	User();
	User(std::string first_name, std::string last_name, std::string pin, unsigned int age);
	User(const User& user);
	const std::string getFirstName();
	const std::string getLastName();
	const std::string getPin();
	const bool getVoted();
	const unsigned int getAge();
	static const unsigned int getMinimumAge();
	void setFirstName(std::string first_name);
	void setLastName(std::string last_name);
	void setPin(std::string pin);
	void setVoted();
	void setAge(unsigned int age);
	static void setMinimumAge(unsigned int minimum_age);
	User& operator=(const User& user);
	bool operator==(const User& user);
	void print() const;
	void read();
};