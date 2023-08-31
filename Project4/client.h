#pragma once

#include <iostream> 
#include "Policy.h"
using namespace std;



string cserver = "tcp://127.0.0.1:3306";
string cusername = "root";
string cpassword = "Rishij2000@";


void viewClient(int userid) {
	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::Statement* stmt;
	sql::ResultSet* result;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(cserver, cusername, cpassword);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("temp");
	stmt = con->createStatement();
	delete stmt;

	//Existing List of Clients

	pstmt = con->prepareStatement("SELECT * FROM client where iid = (?);");
	pstmt->setInt(1, userid);
	result = pstmt->executeQuery();
	while (result->next()) {
		cout << "Client Id:" << result->getInt(1) << "   Client Name: " << result->getString(2) << "\n";
	}

	//Going to a particular client

	int Clientid;
	pstmt = con->prepareStatement("SELECT * FROM client where iid = (?) and cid = (?);");
	cout << "Enter Client id(press 0 to exit): ";
	cin >> Clientid;
	cout << "\n";

	pstmt->setInt(1, userid);
	pstmt->setInt(2, Clientid);
	result = pstmt->executeQuery();

	cout << "Reading from table\n\n";
	if (result->next()) {
		//cout << result->getString(2);
		cout << " *************************************** Welcome to " << result->getString(2) << " dashboard *************************************** \n";
		dashboard(Clientid);




	}
	else {
		cout << "Invalid choice";
	}

}



void createClient(int userid) {

	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::Statement* stmt;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(cserver, cusername, cpassword);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("temp");
	stmt = con->createStatement();
	delete stmt;


	string name;
	int age;

	cout << "\nEnter name: ";
	cin >> name;
	cout << "Enter age: \n";
	cin >> age;

	pstmt = con->prepareStatement("INSERT INTO client(name, age, iid) VALUES(?,?,?)");
	pstmt->setString(1, name);
	pstmt->setInt(2, age);
	pstmt->setInt(3, userid);
	pstmt->execute();

	cout << "Client created successffully\n";


	delete pstmt;
	delete con;


}


