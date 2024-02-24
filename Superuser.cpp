#include "Superuser.h"

Superuser* Superuser::super_user = nullptr;

Superuser::Superuser() {};
Superuser* Superuser::getSuperuser() {
	if (Superuser::super_user == NULL) Superuser::super_user = new Superuser();
	return Superuser::super_user;
}
void Superuser::setSuperuser(std::string first_name, std::string last_name, std::string pin, unsigned int age, std::string username, std::string password) {
	if (verifyName(first_name) != " ") this->first_name = verifyName(first_name);
	if (verifyName(last_name) != " ") this->last_name = verifyName(last_name);
	if (std::regex_match(pin, pin_pattern)) this->pin = pin;
	if (age >= User::minimum_age) this->age = age;
	if (username.length() >= 3) this->username = username;
	if (std::regex_match(password, password_pattern)) this->password = password;

}
const std::string Superuser::getUsername() {
	return this->username;
}
const std::string Superuser::getPassword() {
	return this->password;
}
void Superuser::setUsername(std::string username) {
	if (username.length() < 3) throw std::exception("\nUsername has to have at least 3 characters!\n");
	this->username = username;
}
void Superuser::setPassword(std::string password) {
	if (!std::regex_match(password, password_pattern)) throw std::exception("\nPassword must have at least 6 characters, an uppercase and a digit\n");
	this->password = password;
}
void Superuser::print() const {
	static_cast<User>(*this).print();
}