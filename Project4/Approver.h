#pragma once

#include<iostream>
#include "signIn.h"
using namespace std;
string aserver = "tcp://127.0.0.1:3306";
string ausername = "root";
string apassword = "Rishij2000@";


//Funtion to approve policy

void ApprovePolicy() {

	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::Statement* stmt;
	sql::ResultSet* res;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(aserver, ausername, apassword);
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



	cout << "List of policies to be approved:\n\n";
	con->setSchema("temp");
	pstmt = con->prepareStatement("SELECT * from policies where approved=0");            //Fetching data from database with
	res = pstmt->executeQuery();                                                         //policy approved status as 0.
	while (res->next()) {
		cout << "Client id:" << res->getInt(12) << "\n";
		cout << "Policy id:" << res->getInt(1) << "\n";
		cout << "Name: " << res->getString(2) << "\n\n";

	}

	cout << "Enter policy id that needs approval:";
	int p_num;
	cin >> p_num;
	pstmt = con->prepareStatement("SELECT * from policies where p_num = (?)");
	pstmt->setInt(1, p_num);
	res = pstmt->executeQuery();
	if (res->next()) {
		cout << "Client id:" << res->getInt(12) << "\n";
		cout << "First Name: " << res->getString(2) << "\n";
		cout << "Last Name: " << res->getString(3) << "\n";                 //Fething the data from database
		cout << "Age:" << res->getInt(4) << "\n";
		cout << "Tobacco Status: " << res->getString(8) << "\n";
		cout << "Gender : " << res->getString(7) << "\n";
		cout << "Sum assured: " << res->getInt(10) << "\n";
		cout << "Annual Income: " << res->getInt(9)<<"\n";
		cout << "Policy id:" << res->getInt(1) << "\n";
		
		

		cout << "Approve policy? (Press 1 to Approve)\n";
		bool approval = true;
		cin >> approval;
		if (approval) {
			pstmt = con->prepareStatement("UPDATE policies SET approved = (?) WHERE p_num = (?)");
			pstmt->setInt(1, 1);
			pstmt->setInt(2, p_num);            // Updating the approval status of that particular policy using its policy id
			pstmt->executeQuery();

			cout << "Policy of the user approved!\n\n\n";
		}
	}
	delete pstmt;
	delete res;
	delete con;
}


//Approver SignUp

void ApproverSignup() {

	//Connecting Database

	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::Statement* stmt;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(aserver, ausername, apassword);
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
	string password;
	cout << "Enter Name: ";
	cin >> name;
	cout << "Enter Password: ";
	cin >> password;


	//Inserting into database

	pstmt = con->prepareStatement("INSERT INTO approver(name, password) VALUES(?,?)");
	pstmt->setString(1, name);
	pstmt->setString(2, password);
	pstmt->execute();

	delete pstmt;
	delete con;

}

//Approver Signin

void ApproverSignin() {
	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	/*sql::Statement* stmt;*/
	sql::ResultSet* result;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(aserver, ausername, apassword);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("temp");

	bool success = false;
	//select  
	do {
		pstmt = con->prepareStatement("SELECT * FROM approver where aid=(?)");
		int aid;
		cout << "Enter Approver id(press 0 to exit): ";
		cin >> aid;
		if (!aid) {
			break;
		}
		pstmt->setInt(1, aid);
		result = pstmt->executeQuery();

		cout << "Reading from table\n";
		result->next();
		cout << result->getString(2);

		string inppwd;
		string password = result->getString(3);

		cout << "\nEnter Password: ";
		cin >> inppwd;
		if (inppwd.compare(password) == 0) {
			cout << "Login successful\n\n";
			success = true;
			ApprovePolicy();

		}

		else {
			cout << "Invalid Password\n";
		}
	} while (!success);


}



