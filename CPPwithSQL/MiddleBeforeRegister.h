#pragma once
#include <iostream>
using namespace std;
class MiddleBeforeRegister
{

private:
	string phone;

public:
	MiddleBeforeRegister(const string phone);
	bool checkPhone(const string phone);
	bool checkInDatabase();
};

