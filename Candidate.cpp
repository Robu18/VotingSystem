#include "Candidate.h"

unsigned int Candidate::minimum_age = 25;

Candidate::Candidate() {};
Candidate::Candidate(std::string first_name, std::string last_name, std::string party, unsigned int age) {
	if (verifyName(first_name) != " ") this->first_name = verifyName(first_name);
	if (verifyName(last_name) != " ") this->last_name = verifyName(last_name);
	if (party.length() >= 1) this->party = party;
	if (age >= Candidate::minimum_age) this->age = age;
}
Candidate::Candidate(const Candidate& candidate) {
	this->first_name = candidate.first_name;
	this->last_name = candidate.last_name;
	this->party = candidate.party;
	this->age = candidate.age;
	this->votes = candidate.votes;
}
const std::string Candidate::getName() {
	return this->first_name + " " + this->last_name;
}
const std::string Candidate::getParty() {
	return this->party;
}
const unsigned int Candidate::getAge() {
	return this->age;
}
const unsigned int Candidate::getNrVotes() {
	return this->votes;
}
const unsigned int Candidate::getMinimumAge() {
	return Candidate::minimum_age;
}
void Candidate::setFirstName(std::string first_name) {
	if (verifyName(first_name) == " ") throw std::exception("\nInvalid name!\n");
	this->first_name = first_name;
}
void Candidate::setLastName(std::string last_name) {
	if (verifyName(last_name) == " ") throw std::exception("\nInvalid name!\n");
	this->last_name = last_name;
}
void Candidate::setAge(unsigned int age) {
	if (age < Candidate::minimum_age) throw std::exception("\nAge has to be over the minimum one!\n");
	this->age = age;
}
void Candidate::setParty(std::string party) {
	if (party.length() < 1) throw std::exception("\nInvalid party name!\n");
	this->party = party;
}
void Candidate::setNrVotes(unsigned int votes) {
	if (votes < 0) throw std::exception("\nNumber of votes has to be over 0!\n");
	this->votes = votes;
}
void Candidate::setMinimumAge(unsigned int minimum_age) {
	if (minimum_age < 18) throw std::exception("\nMinimum age for a candidate has to be over 18!\n");
	Candidate::minimum_age = minimum_age;
}
Candidate& Candidate::operator=(const Candidate& candidate) {
	if (&candidate == this) return *this;
	this->first_name = candidate.first_name;
	this->last_name = candidate.last_name;
	this->party = candidate.party;
	this->age = candidate.age;
	this->votes = candidate.votes;
	return *this;
}
Candidate& Candidate::operator++(int) {
	Candidate temp = *this;
	this->votes++;
	return temp;
}
Candidate& Candidate::operator++() {
	this->votes++;
	return *this;
}
bool Candidate::operator==(const Candidate& candidate) {
	if (this->first_name != candidate.first_name) return false;
	if (this->last_name != candidate.last_name) return false;
	if (this->party != candidate.party) return false;
	if (this->age != candidate.age) return false;
	return true;
}
bool Candidate::operator<(const Candidate& candidate) {
	return this->votes < candidate.votes;
}
bool Candidate::operator>(const Candidate& candidate) {
	return this->votes > candidate.votes;
}
void Candidate::print() const {
	std::cout << "First Name: " << this->first_name << "\n";
	std::cout << "Last Name: " << this->last_name << "\n";
	std::cout << "Party: " << this->party << "\n";
	std::cout << "Age: " << this->age << "\n";
	std::cout << "Number of votes: " << this->votes << "\n";
}
void Candidate::read() {
	std::string first_name, last_name, party;
	unsigned int age;
	std::cout << "First Name: "; 
	std::cin >> first_name;
	if (verifyName(first_name) == " ") throw std::exception("\nInvalid Name!\n");
	this->first_name = verifyName(first_name);
	std::cout << "Last Name: ";
	std::cin >> last_name;
	if (verifyName(last_name) == " ") throw std::exception("\nInvalid name\n");
	this->last_name = verifyName(last_name);
	std::cout << "Party: ";
	std::cin >> party;
	if (party.length() < 1) throw std::exception("\nInvalid party name!\n");
	this->party = party;
	std::cout << "Age: ";
	std::cin >> age;
	if (age < Candidate::minimum_age) throw std::exception("\nAge has to be over the minimum one!\n");
	this->age = age;
}

bool Candidate::verifyCandidate(const Candidate& candidate) {
	if (candidate.first_name == "Undefined") return false;
	if (candidate.last_name == "Undefined") return false;
	if (candidate.party == "Undefined") return false;
	return true;
}