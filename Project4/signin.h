#pragma once
#pragma once
#include <iostream>
#include"client.h"


using namespace std;
string iserver = "tcp://127.0.0.1:3306";
string iusername = "root";
string ipassword = "Rishij2000@";



//Insurer Signup


int SignUp(string pwd, string name) {
	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::Statement* stmt;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(iserver, iusername, ipassword);
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

	pstmt = con->prepareStatement("INSERT INTO insurer(name, pwd) VALUES(?,?)");
	pstmt->setString(1, name);
	pstmt->setString(2, pwd);
	pstmt->execute();

	delete pstmt;
	delete con;

	return 1;

}


//Insurer SignIn

int SignIn() {

	//Connecting Database
	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	/*sql::Statement* stmt;*/
	sql::ResultSet* result;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(iserver, iusername, ipassword);
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
		pstmt = con->prepareStatement("SELECT * FROM insurer where iid=(?)");
		int userid;
		cout << "\nEnter userid(press 0 to exit): ";                      
		cin >> userid;
		if (!userid) {
			break;
		}
	
		pstmt->setInt(1, userid);                                  //Inserting into database
		result = pstmt->executeQuery();

		cout << "\n\nReading from table\n\n";
		result->next();
		cout<<"Username: " << result->getString(2);                //Reading from database

		string inppwd;
		string password = result->getString(3);

		cout << "\nEnter Password: ";
		cin >> inppwd;
		if (inppwd.compare(password) == 0) {                      //Validating the password from the database
			cout << "\nLogin successful\n\n";
			success = true;

			cout << "1. New Client\n";
			cout << "2. Existing Client\n";                       //Client dashboard for insurer
			cout << "0. Exit\n";

			int choice;
			cin >> choice;
			if (choice == 1) {
				createClient(userid);
			}

			else if (choice == 2) {
				viewClient(userid);
			}
		}

		else {
			cout << "Invalid Password\n";
		}
	} while (!success);


}

