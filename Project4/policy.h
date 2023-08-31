#pragma once
#pragma once
#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include"premium.h"



using namespace std;
string pserver = "tcp://127.0.0.1:3306";
string pusername = "root";
string ppassword = "Rishij2000@";




void dashboard(int Clientid) {
	int choice;
	string fname;
	string lname;
	int dob;
	int mobnum;
	string email;
	string gender;
	string tobacco;
	int annualinc;
	int sum;
	string rider;
	int premium = 100000;


	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::Statement* stmt;
	sql::ResultSet* result;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(pserver, pusername, ppassword);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("temp");
	stmt = con->createStatement();
	

	cout << "\n\n1. List of policies\n";
	cout << "2. Create new policy\n";
	cout << "3. Cancel Policy\n";
	cout << "Enter your choice: ";

	cin >> choice;


	if (choice == 1) {
		//Shows list of policies for the client

		cout << "List of policies:\n";

		pstmt = con->prepareStatement("SELECT * from policies where cid=(?)");
		pstmt->setInt(1, Clientid);
		result = pstmt->executeQuery();
		bool bFound = false;
		while (result->next()) {
			bFound = true;
			cout << "Policy id: " << result->getInt(1) << "\n";
			cout << "Policy status: ";

			 if(result->getInt(13)){             
			 	cout<<"Cancelled";             
			 }
			 else if(result->getInt(11)){
			 	cout<<"Inforce";
			 }
			 else{
			 	cout<<"Pending";
			 }
			cout << endl;
		}
	}


	//Create New Client
	else if (choice == 2) {

		/*cout << "cid: ";
		cin >> cid;*/
		cout << "\n\nSelect insurance type\n" << "1. Term Life Insurance\n" << "2. Whole Life Insurance\n" << "3. Money Back Policy\n";
		int input, mprem;
		cin >> input;
		cout << "\nFirst Name: \n";
		cin >> fname;
		cout << "Last Name: \n";
		cin >> lname;
		cout << "Age: \n";
		cin >> dob;
		cout << "Mobile Number: \n";
		cin >> mobnum;
		cout << "Email: \n";
		cin >> email;
		cout << "Gender: \n";
		cin >> gender;
		cout << "Tobacco(Y/N): \n";
		cin >> tobacco;
		cout << "Annual Income: \n";
		cin >> annualinc;
		cout << "Sum Assured: \n";
		cin >> sum;
		cout << "\n";
		cout << "Premium: " << premium<<"\n\n";
		cout << "\nWant to Add Riders?(Yes/No)\n\n ";
		cin >> rider;
		if (rider == "Yes") {
			mprem = addrider();

		}
		else if (rider == "No") {
			mprem = payment(premium);
		}

		/*cout << "Total premium: premium()";*/
		
		//Inserting the values into table
		pstmt = con->prepareStatement("INSERT INTO policies (fname, lname, dob, mobnum, email, gender ,tobacco ,annualinc ,sum,cid,premium) VALUES (?,?,?,?,?,?,?,?,?,?,?)");

		pstmt->setString(1, fname);
		pstmt->setString(2, lname);
		pstmt->setInt(3, dob);
		pstmt->setInt(4, mobnum);
		pstmt->setString(5, email);
		pstmt->setString(6, gender);
		pstmt->setString(7, tobacco);
		pstmt->setInt(8, annualinc);
		pstmt->setInt(9, sum);
		pstmt->setInt(10, Clientid);
		pstmt->setInt(11, mprem);

		result = pstmt->executeQuery();
		

		cout << "\nPolicy created for approval\n";

		pstmt = con->prepareStatement("SELECT * from policies");
		result = pstmt->executeQuery();
		int id = 0;
		while (result->next())
			id = result->getInt(1);
		cout << "Policy number: " << id << "\n";

		delete pstmt;
		delete result;
		delete con;

	}

	else if (choice == 3) {
		cout << "List of policies:\n";
		con->setSchema("temp");
		sql::Statement* stmt;
		sql::PreparedStatement* pstmt;
		sql::ResultSet* result;
		pstmt = con->prepareStatement("SELECT * from policies where cid=(?)");
		pstmt->setInt(1, Clientid);
		result = pstmt->executeQuery();
		bool bFound = false;
		while (result->next()) {
			bFound = true;
			cout << "Policy id: " << result->getInt(1) << "\n";
			cout << "Policy status: ";

			if (result->getInt(13)) {
				cout << "Cancelled";
			}
			else if (result->getInt(11)) {
				cout << "Inforce";
			}
			else {
				cout << "Pending";
			}


			cout << endl;
		}
		if (!bFound) {
			cout << "\nNo policies found";
			cout << "\nPress any key to continue.....\n";
			_getch();
		}
		cout << "Enter the policy id to be cancelled: ";
		int p_num;
		cin >> p_num;
		cout << "Cancel policy?\n";
		bool cancelled = true;
		cin >> cancelled;
		if (cancelled) {
			pstmt = con->prepareStatement("UPDATE policies SET cancelled = (?) WHERE p_num = (?)");
			pstmt->setInt(1, 1);
			pstmt->setInt(2, p_num);
			pstmt->executeQuery();
		}
		delete pstmt;
		delete result;
		delete con;
	}
}



	

