#include "MiddleBeforeRegister.h"


MiddleBeforeRegister::MiddleBeforeRegister(const string phone)
{
	checkPhone(phone);
}


bool MiddleBeforeRegister::checkPhone(const string phone)
{
	if (int(phone.length()) == 10)
	{
		for (int i = 0; i<int(phone.length()); i++)
		{
			if (phone[i] >= '0' && phone[i] <= '9')
			{
				continue;
			}
			else {
				cout << "A phone number should only contain digits" << endl;
				return false;
			}
		}
		this->phone = phone;
		return true;
	}
	else
	{
		cout << "A phone number should contain 10 digits" << endl;
		return false;
	}
}
bool MiddleBeforeRegister::checkInDatabase()
{

}