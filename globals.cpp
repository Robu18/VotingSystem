#include "globals.h"

std::string verifyName(std::string name) {
	if (name.length() < 3) return " ";
	name[0] = toupper(name[0]);
	for (int i = 1; i < name.length(); i++) {
		name[i] = tolower(name[i]);
		if (name[i - 1] == ' ' || name[i - 1] == '-') name[i] = toupper(name[i]);
	}
	bool ok = true;
	for (auto ch : name)
		if (isdigit(ch)) ok = false;
	if (ok == false) return " ";
	return name;
}

std::regex pin_pattern("^\\d{4}-\\d{2}-\\d{2}-\\d{4}$");
std::regex password_pattern("^(?=.*[A-Z])(?=.*[0-9]).{6,}$");