#pragma once


#include<iostream>
#include "signIn.h"
using namespace std;


void insurer() {
	int choice;

	do {
		cout << "\n\n1. SignUp";
		cout << "\n2. SignIn";
		cout << "\n0.Exit\n\n";
		cout << "Enter Choice: ";
		cin >> choice;
		if (choice == 1) {
			string name;
			string password;
			cout << "Enter name: ";
			cin >> name;
			cout << "Enter password: ";
			cin >> password;
			SignUp(password, name);
			cout << "Sign up successful!\n";
		}

		else if (choice == 2) {
			SignIn();
		}

		else if (choice != 0) {
			cout << "Invalid Options";
		}
	} while (choice != 0);
}
