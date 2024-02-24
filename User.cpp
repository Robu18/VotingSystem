#include "User.h"

unsigned int User::minimum_age = 18;

User::User() {};
User::User(std::string first_name, std::string last_name, std::string pin, unsigned int age) {
	if (verifyName(first_name) != " ") this->first_name = verifyName(first_name);
	if (verifyName(last_name) != " ") this->last_name = verifyName(last_name);
	if (std::regex_match(pin, pin_pattern)) this->pin = pin;
	if (age >= User::minimum_age) this->age = age;
}
User::User(const User& user) {
	this->first_name = user.first_name;
	this->last_name = user.last_name;
	this->pin = user.pin;
	this->age = user.age;
	this->voted = user.voted;
}
const std::string User::getFirstName() {
	return this->first_name;
}
const std::string User::getLastName() {
	return this->last_name;
}
const std::string User::getPin() {
	return this->pin;
}
const unsigned int User::getAge() {
	return this->age;
}
const bool User::getVoted() {
	return this->voted;
}
const unsigned int User::getMinimumAge() {
	return User::minimum_age;
}
void User::setFirstName(std::string first_name) {
	if (verifyName(first_name) == " ") throw std::exception("\nInvalid name!\n");
	this->first_name = first_name;
}
void User::setLastName(std::string last_name) {
	if (verifyName(last_name) == " ") throw std::exception("\nInvalid name!\n");
	this->last_name = last_name;
}
void User::setPin(std::string pin) {
	if (!std::regex_match(pin, pin_pattern)) throw std::exception("\nPIN format has to be: XXXX-XX-XX-XXXX!\n");
	this->pin = pin;
}
void User::setAge(unsigned int age) {
	if (age < User::minimum_age) throw std::exception("\nAge must be over the minimum one!\n");
	this->age = age;
}
void User::setVoted() {
	this->voted = true;
}
void User::setMinimumAge(unsigned int minimum_age) {
	if (minimum_age < 14) throw std::exception("\nMinimum age must be over 14!\n");
	User::minimum_age = minimum_age;
}
User& User::operator=(const User& user) {
	if (this == &user) return *this;
	this->first_name = user.first_name;
	this->last_name = user.last_name;
	this->pin = user.pin;
	this->age = user.age;
	this->voted = user.voted;
}
bool User::operator==(const User& user) {
	if (this->first_name != user.first_name) return false;
	if (this->last_name != user.last_name) return false;
	if (this->pin != user.pin) return false;
	if (this->age != user.age) return false;
	return true;
}
void User::print() const {
	std::cout << "First name: " << this->first_name << "\n";
	std::cout << "Last name: " << this->last_name << "\n";
	std::cout << "Personal Identification Number: " << this->pin << "\n";
	std::cout << "Age: " << this->age << "\n";
	std::cout << "Voted: ";
	if (this->voted) std::cout << "True\n";
	else std::cout << "False\n";
}
void User::read() {
	std::string first_name, last_name, pin;
	std::cout << "First name: ";
	std::cin >> first_name;
	if (verifyName(first_name) == " ") throw std::exception("\nInvalid name!\n");
	this->first_name = verifyName(first_name);
	std::cout << "Last name: ";
	std::cin >> last_name;
	if (verifyName(last_name) == " ") throw std::exception("\nInvalid name!\n");
	this->last_name = verifyName(last_name);
	std::cout << "Personal Identification Number (XXXX-XX-XX-XXXX): ";
	std::cin >> pin;
	if (!std::regex_match(pin, pin_pattern)) throw std::exception("\nPIN format has to be: XXXX-XX-XX-XXXX!\n");
	this->pin = pin;
	unsigned int age;
	std::cout << "Age: ";
	std::cin >> age;
	if (age < User::minimum_age) throw std::exception("\nAge has to be over the minimum one!\n");
}