#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include<conio.h>
#include"signin.h"
#include"insurer.h"
#include"approverdashboard.h"
#include"Approver.h"
#include"client.h"
#include"policy.h"

using namespace std;

int main()
{
	int choice;
	do {
		cout << " *************************************** Welcome to Dashboard ***************************************\n";
		cout << "1. Insurer\n";
		cout << "2. Approver\n";
		cout << "0. Exit\n";
		cout << "Enter choice:";
		cin >> choice;

		if (choice == 1) {
			insurer();
		}
		else if (choice == 2) {
			approverDashboard();
		}
		else if (choice != 0) {
			cout << "Incorrect Option\n";
		}

	} while (choice != 0);

	cout << " Goood bye";

	_getch();
}