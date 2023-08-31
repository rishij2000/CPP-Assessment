//#pragma once
//
//#include<iostream>
//#include "signIn.h"
//using namespace std;
//string aserver = "tcp://127.0.0.1:3306";
//string ausername = "root";
//string apassword = "Rishij2000@";
//
//
//
//
//void ApprovePolicy() {
//
//	sql::Driver* driver;
//	sql::Connection* con;
//	sql::PreparedStatement* pstmt;
//	sql::Statement* stmt;
//	sql::ResultSet* res;
//
//	try
//	{
//		driver = get_driver_instance();
//		//for demonstration only. never save password in the code!
//		con = driver->connect(aserver, ausername, apassword);
//	}
//	catch (sql::SQLException e)
//	{
//		cout << "Could not connect to server. Error message: " << e.what() << endl;
//		system("pause");
//		exit(1);
//	}
//
//	con->setSchema("temp");
//	stmt = con->createStatement();
//	delete stmt;
//
//
//
//	cout << "List of policies to be approved:\n";
//	con->setSchema("temp");
//	pstmt = con->prepareStatement("SELECT * from policies where approved=0");
//	res = pstmt->executeQuery();
//	while (res->next()) {
//		cout << "Client id:" << res->getInt(12) << "\n";
//		cout << "Policy id:" << res->getInt(1) << "\n";
//		cout << "Name: " << res->getString(2) << "\n\n";
//
//	}
//
//	cout << "Enter policy id that needs approval:";
//	int p_num;
//	cin >> p_num;
//	pstmt = con->prepareStatement("SELECT * from policies where p_num = (?)");
//	pstmt->setInt(1, p_num);
//	res = pstmt->executeQuery();
//	if (res->next()) {
//		cout << "Client id:" << res->getInt(12) << "\n";
//		cout << "Age:" << res->getInt(4) << "\n";
//		cout << "Sum assured:" << res->getInt(10) << "\n";
//		cout << "Policy id:" << res->getInt(1) << "\n";
//		cout << "First Name: " << res->getString(2) << "\n";
//		cout << "Last Name: " << res->getString(3) << "\n\n";
//
//		cout << "Approve policy?\n";
//		bool approval = true;
//		cin >> approval;
//		if (approval) {
//			pstmt = con->prepareStatement("UPDATE policies SET approved = (?) WHERE p_num = (?)");
//			pstmt->setInt(1, 1);
//			pstmt->setInt(2, p_num);
//			pstmt->executeQuery();
//
//			cout << "Policy of the user approved!\n";
//		}
//	}
//	delete pstmt;
//	delete res;
//	delete con;
//}
//
//
//void ApproverSignup() {
//	sql::Driver* driver;
//	sql::Connection* con;
//	sql::PreparedStatement* pstmt;
//	sql::Statement* stmt;
//
//	try
//	{
//		driver = get_driver_instance();
//		//for demonstration only. never save password in the code!
//		con = driver->connect(aserver, ausername, apassword);
//	}
//	catch (sql::SQLException e)
//	{
//		cout << "Could not connect to server. Error message: " << e.what() << endl;
//		system("pause");
//		exit(1);
//	}
//
//	con->setSchema("temp");
//	stmt = con->createStatement();
//	delete stmt;
//
//	string name;
//	string password;
//	cout << "Enter Name: ";
//	cin >> name;
//	cout << "Enter Password: ";
//	cin >> password;
//
//
//
//	pstmt = con->prepareStatement("INSERT INTO approver(name, password) VALUES(?,?)");
//	pstmt->setString(1, name);
//	pstmt->setString(2, password);
//	pstmt->execute();
//
//	delete pstmt;
//	delete con;
//
//}
//
//
//
//void ApproverSignin() {
//	sql::Driver* driver;
//	sql::Connection* con;
//	sql::PreparedStatement* pstmt;
//	/*sql::Statement* stmt;*/
//	sql::ResultSet* result;
//
//	try
//	{
//		driver = get_driver_instance();
//		//for demonstration only. never save password in the code!
//		con = driver->connect(aserver, ausername, apassword);
//	}
//	catch (sql::SQLException e)
//	{
//		cout << "Could not connect to server. Error message: " << e.what() << endl;
//		system("pause");
//		exit(1);
//	}
//
//	con->setSchema("temp");
//
//	bool success = false;
//	//select  
//	do {
//		pstmt = con->prepareStatement("SELECT * FROM approver where aid=(?)");
//		int aid;
//		cout << "Enter Approver id(press 0 to exit): ";
//		cin >> aid;
//		if (!aid) {
//			break;
//		}
//		pstmt->setInt(1, aid);
//		result = pstmt->executeQuery();
//
//		cout << "Reading from table\n";
//		result->next();
//		cout << result->getString(2);
//
//		string inppwd;
//		string password = result->getString(3);
//
//		cout << "\nEnter Password: ";
//		cin >> inppwd;
//		if (inppwd.compare(password) == 0) {
//			cout << "Login successful\n";
//			success = true;
//			ApprovePolicy();
//
//
//
//			/*int choice;
//			cin >> choice;
//			if (choice == 1) {
//				createClient(userid);
//			}
//
//			else if (choice == 2) {
//				viewClient(userid);
//			}*/
//		}
//
//		else {
//			cout << "Invalid Password\n";
//		}
//	} while (!success);
//
//
//}

#pragma once
#include<iostream>
#include "signIn.h"
#include"Approver.h"
using namespace std;

void approverDashboard() {
	cout << "Welcome to Approver Dashboard\n";
	cout << "1. Approver SignUp\n";
	cout << "2. Approver SignIn\n";

	int choice;
	cout << "Enter your choice: ";
	cin >> choice;

	if (choice == 1) {
		ApproverSignup();
	}

	if (choice == 2) {
		ApproverSignin();
	}

}


