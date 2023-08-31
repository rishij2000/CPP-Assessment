#pragma once
#include<iostream>
#include"policy.h"

using namespace std;

float payment(float prem);







float adb() {
	
	float initialCoverage;
	float resultadb;
	float monthlyp;
	float taxp;
	cout << "Enter Initial Coverage(Minimum Coverage 25,000): \n";
	cin >> initialCoverage;

	resultadb = 100000 + (initialCoverage/25000)*5;
	cout << "Total Premium Calculated After converage: " << resultadb << "\n";
	cout << "Monthly Premium: " << resultadb / 12 << "\n";
	cout << "Monthly Premium after tax (18%): " << (resultadb*(0.18)+ resultadb)/12<<"\n";

	return resultadb;


}

float cc() {
	float initialCoverage;
	float resultcc;
	cout << "\n\nEnter Initial Coverage(Minimum Coverage 2,00,000): \n";
	cin >> initialCoverage;

	if (initialCoverage == 200000) {
		resultcc = 100000 + 80;
	}
	else if(initialCoverage> 200000) {
		resultcc = 100000 + (initialCoverage / 300000) * (400*12);
	}

	cout << "Total Premium Calculated After converage: " << resultcc << "\n";
	cout << "Monthly Premium: " << resultcc / 12 << "\n";
	cout << "Monthly Premium after tax (18%): ";
	cout<< (resultcc * (0.18) + resultcc) / 12;
	cout << "\n";

	return resultcc;

}


float addrider() {

	int choice;
	cout << "\n\nSelect the rider\n";
	cout << "1. Accidental Death Benifit\n";
	cout << "2. Comprehensive Care\n";
	cout << "Enter choice: ";
	cin >> choice;
	if (choice == 1) {
		return payment(adb());
	}
	if (choice == 2) {
		return payment(cc());
	}

}

float payment(float prem) {
	string nserver = "tcp://127.0.0.1:3306";
	string nusername = "root";
	string npassword = "Rishij2000@";

	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::Statement* stmt;
	sql::ResultSet* result;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(nserver, nusername, npassword);
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


                          //Premium


	int mprem;
	float hprem;
	float yprem;

	cout << "\n\nChoose Payment Duration:\n";
	cout << "1. Monthly\n";
	cout << "2. Half-Yearly\n";
	cout << "3. Yearly\n";
	int choice;
	cin >> choice;
	
	if (choice == 1) {
		cout << "\n\nMonthly Premium: ";
		mprem = prem / 12;
		cout << mprem;

		return mprem;
		//pstmt = con->prepareStatement("UPDATE policies SET premium = (?) where p_num = (?)");
		//pstmt->setInt(1, mprem);
		//pstmt->setInt(2, p_num);
		//result = pstmt->executeQuery();

		//delete pstmt;
		//delete result;
		//delete con;
		
	}

	else if (choice == 2) {
		cout << "\n\nHalf-Yearly Premium with 10% reduction in total premium: ";
		hprem = (prem - prem * (0.10)) / 2;
		cout << hprem;
		return hprem;

	}

	else if (choice == 3) {
		cout << "\n\nYearly Premium with 15% reduction in total premium: ";
		yprem = (prem - prem * (0.15));
		cout << yprem;
		return yprem;

	}

	

	
	
	


}


