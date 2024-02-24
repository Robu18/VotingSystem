#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include "Candidate.h"
#include "User.h"
#include "Superuser.h"

Superuser* super_user = Superuser::getSuperuser();

struct CompareCandidates {
	bool operator()(Candidate* lhs, Candidate* rhs) const {
		return lhs->getNrVotes() < rhs->getNrVotes();
	}
};

std::set<Candidate*, CompareCandidates> candidates;
std::vector<User*> users;

void userMenu(User* user) {
	system("cls");
	std::cout << "Welcome, " << user->getFirstName() << " " << user->getLastName() << "\n\n";
	std::cout << "-------------\n\n";
	if (user->getVoted() == true) {
		std::cout << "You already expressed you right to vote!";
	}
	else {
		if (candidates.empty()) std::cout << "No candidates!";
		else {
			int i = 1;
			std::set<Candidate*>::iterator it;
			for (it = candidates.begin(); it != candidates.end(); it++) {
				std::cout << "Candidate no. " << i << "\n";
				(*it)->print();
				i++;
				std::cout << "\n";
			}
			std::cout << "\n-------------\n";
			std::cout << "\n\tEnter your option: ";
			unsigned short option;
			std::cin >> option;
			if (option > candidates.size() || option < 1) throw std::exception("\nOption out of range!\n");
			else {
				i = 1;
				std::set<Candidate*>::iterator it;
				for (it = candidates.begin(); it != candidates.end(); it++) {
					if (i == option) {
						*it++;
						break;
					}
					i++;
				}
				std::cout << "Your vote is registered!\n";
			}
		}
	}
}

void superuserMenu() {
	bool retry = true;
	while (retry) {
		system("cls");
		std::cout << "Welcome, " << super_user->getFirstName() << " " << super_user->getLastName() << "\n\n";
		std::cout << "Your options: \n";
		std::cout << "1. Add a candidate\n";
		std::cout << "2. Add a user\n";
		std::cout << "3. Change your username\n";
		std::cout << "4. Change your password\n";
		std::cout << "5. View results\n";
		std::cout << "6. Export results as .csv\n";
		std::cout << "7. View all candidates\n";
		std::cout << "8. View all users\n";
		std::cout << "9. Update minimum age\n";
		std::cout << "\n\t Your option: ";
		char option;
		std::cin >> option;
		switch (option)
		{
		case '1': {
			system("cls");
			std::cout << "Add a candidate\n\n";
			std::cout << "Minimum age: " << Candidate::getMinimumAge() << "\n\n";
			try {
				Candidate* candidate = new Candidate();
				candidate->read();
				if (Candidate::verifyCandidate(*candidate)) candidates.insert(candidate);
				else std::cout << "Wrong input for candidate!\n";
			}
			catch (std::exception& e) {
				std::cerr << e.what() << "\n";
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '2': {
			system("cls");
			std::cout << "Add a user\n\n";
			std::cout << "Minimum age: " << User::getMinimumAge() << "\n";
			try {
				User* user = new User();
				user->read();
				users.push_back(user);
			}
			catch (std::exception& e) {
				std::cerr << e.what() << "\n";
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '3': {
			system("cls");
			std::cout << "Change username\n\n";
			try {
				std::string username;
				std::cout << "Enter the new username: ";
				std::cin >> username;
				super_user->setUsername(username);
			}
			catch (std::exception& e) {
				std::cerr << e.what() << "\n";
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '4': {
			system("cls");
			std::cout << "Change password\n\n";
			try {
				std::string password;
				std::cout << "Password must have at least 6 characters, one uppercase and one digit\n";
				std::cout << "Enter the new password: ";
				std::cin >> password;
				super_user->setPassword(password);
			}
			catch (std::exception& e) {
				std::cerr << e.what() << "\n";
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '5': {
			system("cls");
			std::cout << "Results\n\n";
			try {
				if (candidates.empty()) {
					std::cout << "\nNo candidates\n";
				}
				else {
					double place = 1, total_votes = 0;
					for (std::set<Candidate*>::iterator it = candidates.begin(); it != candidates.end(); it++)
						total_votes += (*it)->getNrVotes();
					for (auto it = candidates.rbegin(); it != candidates.rend(); it++) {
						std::cout << "\nPlace: no. " << place << ": " << (*it)->getName() << "\n";
						std::cout << "\tPercentage: " << ((*it)->getNrVotes() / total_votes) * 100 << "%\n";
						place++;
					}
				}
			}
			catch (std::exception& e) {
				std::cerr << e.what() << "\n";
			}
			std::cout << "\nPress y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '6': {
			system("cls");
			std::cout << "Results exported in results.csv\n\n";
			std::fstream csv("results.csv", std::ios::out);
			if (csv.is_open()) {
				csv.seekg(0);
				csv << "Place,Name,Percentage\n";
				double place = 1, total_votes = 0;
				for (std::set<Candidate*>::iterator it = candidates.begin(); it != candidates.end(); it++)
					total_votes += (*it)->getNrVotes();
				for (auto it = candidates.rbegin(); it != candidates.rend(); it++) {
					csv << place << ",";
					csv << (*it)->getName() << ",";
					csv << ((*it)->getNrVotes() / total_votes) * 100 << "%\n";
					place++;
				}
				csv.close();
			}
			else {
				std::cout << "Error opening file!\n";
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '7': {
			system("cls");
			std::cout << "View all candidates\n\n";
			if (candidates.empty()) std::cout << "No candidates\n";
			else {
				for (std::set<Candidate*>::iterator it = candidates.begin(); it != candidates.end(); it++) {
					(*it)->print();
					std::cout << "\n";
				}
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '8': {
			system("cls");
			std::cout << "View all users\n\n";
			if (users.empty()) std::cout << "No users\n";
			else {
				for (std::vector<User*>::iterator it = users.begin(); it != users.end(); it++) {
					(*it)->print();
					std::cout << "\n";
				}
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		case '9': {
			system("cls");
			std::cout << "Update minimum age\n";
			std::cout << "1. Update minimum age for voteing\n";
			std::cout << "2. Update minimum age for candidacy\n";
			std::cout << "\n\tYour option: ";
			unsigned int new_age;
			char age_option;
			std::cin >> age_option;
			if (age_option == '1') {
				system("cls");
				std::cout << "Enter the new age for voteing: ";
				std::cin >> new_age;
				User::setMinimumAge(new_age);
			}
			else if (age_option == '2') {
				system("cls");
				std::cout << "Enter the new age for candidacy: ";
				std::cin >> new_age;
				Candidate::setMinimumAge(new_age);
			}
			else {
				system("cls");
				std::cout << "Wrong option!\n";
			}
			std::cout << "Press y if you want to make another action... ";
			char option_retry;
			std::cin >> option_retry;
			if (option_retry != 'y' && option_retry != 'Y') retry = false;
			break;
		}
		default:
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	super_user->setSuperuser("Super", "User", "1234-56-78-9012", 47, "superuser", "Password1");
	Candidate c1("First", "Candidate", "FRS", 34);
	c1++; c1++;
	Candidate c2("Second", "Candidate", "SCN", 37);
	c2++;
	Candidate c3("Third", "Candidate", "THR", 27);
	c3++; c3++; c3++; c3++;
	candidates.insert(&c1);
	candidates.insert(&c2);
	candidates.insert(&c3);
	User u1("First", "User", "5673-12-54-1234", 19);
	User u2("Second", "User", "1345-12-56-1235", 20);
	users.push_back(&u1);
	users.push_back(&u2);
	bool retry = true;
	while (retry) {
		system("cls");
		std::string pin, last_name;
		std::cout << "Last name: ";
		std::cin >> last_name;
		std::cout << "Personal Identification Number (format: XXXX-XX-XX-XXXX): ";
		std::cin >> pin;
		for (auto user : users) {
			try {
				if (verifyName(last_name) == user->getLastName() && pin == user->getPin()) {
					userMenu(user);
					retry = false;
					break;
				}
			}
			catch (std::exception& e) {
				system("cls");
				std::cerr << e.what() << "\n";
				std::cout << "Press any key to retry!";
				getchar(); getchar();
			}
		}
		try {
			if (last_name == super_user->getUsername() && pin == super_user->getPassword()) {
				superuserMenu();
				retry = false;
				break;
			}
		}
		catch (std::exception& e) {
			system("cls");
			std::cerr << e.what() << "\n";
			std::cout << "Press any key to retry!";
			getchar(); getchar();
		}
		system("cls");
		std::cout << "Wrong credential!\n";
		std::cout << "Press any key to retry!";
		retry = true;
		getchar(); getchar();
	}
	return 0;
}