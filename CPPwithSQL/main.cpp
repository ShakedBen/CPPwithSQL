#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable: 4996)
using namespace std;
void DropTable();
void createTable();
bool localDataForLogin(string& server, string& username, string& password);
bool newRegister(string phone, string name, string gender);
bool checkPhone(const string phone);
bool checkIfPhoneNumberExists(const string phone);
bool nameWithOnlyChar(const string name);

string nameData = "quickstartdb";


int main()
{

    string phone;
    string name;
    string gender[2] = { "male","female"};
    int pickGender = 0;
     //DropTable();
      createTable();
    while (checkPhone(phone))
    {
        cout << "Enter phone number" << endl;
        cin >> phone;
    }
    if (checkIfPhoneNumberExists(phone))
    {
        /*Choice of services*/
    }
    else
    {
        while (nameWithOnlyChar(name))
        {
            cout << "Enter name :";
            cin >> name;
        }
        while (pickGender>2 ||pickGender<1)
        {
            cout << "Enter you gender (1)-male (2)-female";
            cin >> pickGender;
            pickGender -= 1;
        }
        newRegister(phone, name, gender[pickGender]);
    }
 


             
  
 
    return 0;
}










void DropTable()
{
    string s, u, p;
    bool flag = localDataForLogin(s, u, p);
    if (flag == false)
        exit(0);
    /*connect to the database*/

    const string server = s;
    const string username = u;
    const string password = p;


    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    /*start work with database name:--- */
    con->setSchema(nameData);
    stmt = con->createStatement();


    /*DROP TABLE*/
    stmt->execute("DROP TABLE IF EXISTS services");
                        /*Printing*/
    cout << "Finished dropping table (if existed)" << endl;
    delete stmt;
    delete con;
    system("pause");
    return;

}

void createTable()
{
    string s, u, p;
    bool flag;
    flag = localDataForLogin(s, u, p);
    if (flag == false)
        exit(0);
    /*connect to the database*/

    const string server = s;
    const string username = u;
    const string password = p; 


    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    /*start work with database name:--- */
    con->setSchema(nameData);
    stmt = con->createStatement();
    //stmt->execute("CREATE TABLE servicesPriceForFemale ( service VARCHAR(50),servicePrice NUMBER);");
    //stmt->execute("CREATE TABLE servicesPriceForMale ( service VARCHAR(50),servicePrice NUMBER);");
     //stmt->execute("CREATE TABLE services ( phone VARCHAR(20),Pedicure BOOLEAN DEFAULT FALSE,Manicure BOOLEAN DEFAULT FALSE,Nail_Building BOOLEAN DEFAULT FALSE,Eyebrow_Shaping BOOLEAN DEFAULT FALSE, Mustache_Wax BOOLEAN DEFAULT FALSE,Leg_Max BOOLEAN DEFAULT FALSE,Hand_Wax BOOLEAN DEFAULT FALSE, Back_Wax BOOLEAN DEFAULT FALSE,Crevices_Wax BOOLEAN DEFAULT FALSE ,time_To_Do VARCHAR(50));");
    //stmt->execute("CREATE TABLE customer (phone VARCHAR(50) PRIMARY KEY,name VARCHAR(50),gender VARCHAR(10), creationDate VARCHAR(50));");
    /*Printing*/
    cout << "Finished creating table" << endl;
    delete stmt;
    delete con;
    system("pause");
    return;
}


            /* insert price of s*/
void InsertData()
{
    string s, u, p;
    bool flag;
    flag = localDataForLogin(s, u, p);
    if (flag == false)
        exit(0);
    /*connect to the database*/
//for demonstration only. never save your password in the code!
    const string server = s;
    const string username = u;
    const string password = p;



    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    /*INSERT DATA TO*/
    //pstmt = con->prepareStatement("INSERT INTO servicesPriceForFemale(service,servicePrice) VALUES(?,?)");
    pstmt = con->prepareStatement("INSERT INTO servicesPriceForMale(service,servicePrice) VALUES(?,?)");
    pstmt->setString(1, "Pedicure");
    pstmt->setString(2, "100");
    pstmt->setString(1, "Manicure");
    pstmt->setString(2, "80");
    pstmt->setString(1, "Nail_Building");
    pstmt->setString(2, "150");
    pstmt->setString(1, "Eyebrow_Shaping");
    pstmt->setString(2, "40");
    pstmt->setString(1, "Mustache_Wax");
    pstmt->setString(2, "100");
    pstmt->setString(1, "Leg_Wax");
    pstmt->setString(2, "100");
    pstmt->setString(1, "Hand_Wax");
    pstmt->setString(2, "100");
    pstmt->setString(1, "Back_Wax");
    pstmt->setString(2, "100");
    pstmt->setString(1, "Cervices_Wax");
    pstmt->setString(2, "100");


    pstmt->execute();
    cout << "One row inserted." << endl;
    delete pstmt;
    system("pause");
}

    
bool localDataForLogin(string& server, string& username, string& password) {
    string nameFile = "D:\\CPP\\connInfo.txt";
    ifstream inFile(nameFile);
    if (inFile.fail())
    {
        cout << "Error trying to connect to local database" << endl;
        return false;

    }
    else {
        while (!inFile.eof())
        {
            inFile >> server >> username >> password;

        }
        inFile.close();
        return true;
    }






}
           


                            /* REGISTER*/
bool newRegister(string phone,string name,string gender)
{
    string s, u, p;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char* dt = ctime(&now);
    bool flag;
    flag = localDataForLogin(s, u, p);
    if (flag == false)
        exit(0);

    /*connect to the database*/
//for demonstration only. never save your password in the code!
    const string server = s;
    const string username = u;
    const string password = p;



    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;

    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    /*INSERT DATA TO*/
    pstmt = con->prepareStatement("INSERT INTO customer(phone,name,gender,creationDate) VALUES(?,?,?,?)");
    pstmt->setString(1, phone);
    pstmt->setString(2, name);
    pstmt->setString(3, gender);
    pstmt->setString(4, dt);
    pstmt->execute();
    cout << "One row inserted." << endl;
    delete pstmt;
    system("pause");
    return true;
}



         /* Checking the correctness of the number and if it already exists */
bool checkPhone(const string phone)
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
    }
    else
    {
        cout << "A phone number should contain 10 digits" << endl;
        return false;
    }
    return true;
}
bool checkIfPhoneNumberExists(const string phone)
{
    string s, u, p;
    bool flag;
    flag = localDataForLogin(s, u, p);
    if (flag == false)
        exit(0);

    /*connect to the database*/
//for demonstration only. never save your password in the code!
    const string server = s;
    const string username = u;
    const string password = p;

    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* result;

    try
    {
        driver = get_driver_instance();
        //for demonstration only. never save password in the code!
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }
    con->setSchema(nameData);
    pstmt = con->prepareStatement("SELECT * FROM customer WHERE phone=?;");
    pstmt->setString(1, phone);
    result = pstmt->executeQuery();
   // while (result->next())
    //{
        cout << result->getString(1).c_str();
   // }
        /*need to return true or false */
    if (pstmt==nullptr)
    {
        delete con;
        delete pstmt;
        system("pause");
        return false;
    }
    
        delete con;
        delete pstmt;
        system("pause");
        return true;
}


      /*check name with only char*/
bool nameWithOnlyChar(const string name)
{
    for (int i = 0; i < int(name.length()); i++)
    {
        if ((name[i] > 65 && name[i] < 91) || (name[i] > 96 && name[i] < 123))
        {
            return true;
        }
        else {
            cout << "The name should contain only letters" << endl;
            return false;
        }
    }
}