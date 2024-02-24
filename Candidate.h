#pragma once
#include <string>
#include <iostream>
#include "globals.h"


class Candidate {
	std::string first_name = "Undefined";
	std::string last_name = "Undefined";
	std::string party = "Undefined";
	unsigned int age = Candidate::minimum_age;
	unsigned int votes = 0;
	static unsigned int minimum_age;
public:
	Candidate();
	Candidate(std::string first_name, std::string last_name, std::string party, unsigned int age);
	Candidate(const Candidate& candidate);
	const std::string getName();
	const std::string getParty();
	const unsigned int getAge();
	const unsigned int getNrVotes();
	static const unsigned int getMinimumAge();
	void setFirstName(std::string first_name);
	void setLastName(std::string last_name);
	void setParty(std::string party);
	void setAge(unsigned int age);
	void setNrVotes(unsigned int votes);
	static void setMinimumAge(unsigned int minimum_age);
	static bool verifyCandidate(const Candidate& candidate);
	Candidate& operator=(const Candidate& candidate);
	Candidate& operator++(int);
	Candidate& operator++();
	bool operator==(const Candidate& candidate);
	bool operator<(const Candidate& candidate);
	bool operator>(const Candidate& candidate);
	void print() const;
	void read();
};