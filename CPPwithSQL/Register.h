#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable: 4996)
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

class Register
{
private:
	string phone;
	string name;
	string gender;
public:
	Register(string phone, string name, string gender);
	bool localDataForLoginAndConnectDatabaseAndinsertNewCustomer();
	
};


