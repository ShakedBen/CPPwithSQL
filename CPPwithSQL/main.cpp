#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#define SIZEARR 9
#define I_SIZE 10
#define J_SIZE 25
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
void InsertDataToPriceServices();


string nameData = "quickstartdb";


int main()
{

    string phone;
    string name;
    string genderDB;
    int totalPrice = 0;
    string gender[2] = { "male","female"};
    int pickGender = 0;
    char  services_c[I_SIZE][J_SIZE] = {"Pedicure","Menicure","Nail_Building","Eyebrow_Shaping","Mustache_Wax","Leg_Wax","Hand_Wax","Back_Wax","Crevices_Wax"};
    char str[12][50] = { 
        "******************************" , 
        "* To Pedicure click        1 *" , 
        "* To Menicure click        2 *" , 
        "* To Nail building click   3 *",
        "* To Eyebrow shaping click 4 *",
        "* To Mustache wax click    5 *",
       "* To Leg wax click         6 *" ,
       "* To Hand wax click        7 *" ,
       "* To Back wax click        8 *", 
       "* To Crevices wax click    9 *" ,
       "* To Finish click          0 *",
    "******************************" };
    char str2[11][50] = {
"*************************************",
"* To delete Pedicure click        1 *",
"* To delete Menicure click        2 *",
"* To delete Nail building click   3 *",
"* To delete Eyebrow shaping click 4 *",
"* To delete Mustache wax click    5 *",
"* To delete Leg wax click         6 *",
"* To delete Hand wax click        7 *",
"* To delete Back wax click        8 *",
"* To delete Crevices wax click    9 *",
 "************************************" };



 

    /*Choice of services*/
    //DropTable();
    //createTable();
   // InsertDataToPriceServices();
   
    while (checkPhone(phone))
    {
        cout << "Enter phone number" << endl;
        cin >> phone;
    }

    if(!checkIfPhoneNumberExists(phone))
    {
    while (nameWithOnlyChar(name))
    {
        cout << "Enter name :";
        cin >> name;
    }
    while (pickGender > 2 || pickGender < 1)
    {
        cout << "Enter you gender (1)-male (2)-female";
        cin >> pickGender;

    }
    pickGender -= 1;
    newRegister(phone, name, gender[pickGender]);
    }



    if (checkIfPhoneNumberExists(phone))
    {
        bool run = true;
        int a[12] = { 2,0,0,0,0,0,0,0,0,0,3,2 };
        int pick;

        while (run)
        {
            for (int i = 0; i < 12; i++)
            {
                if (a[i] == 0 || a[i] == 2 || a[i] == 3)
                {
                    cout << str[i] << endl;
                }
            }
            for (int i = 0; i < 12; i++)
            {
                if (a[i] == 1 || a[i] == 2)
                {
                    cout << str2[i] << endl;
                }
            }
            cin >> pick;
            if (pick > 0 && pick < 10)
            {
                if (a[pick] == 0)
                    a[pick] = 1;
                else
                    a[pick] = 0;
            }
            else if (pick == 0)
            {
                break;
            }
            else
            {
                cout << "Try pick number between 1-9" << endl;
            }
        }
        int b[SIZEARR];

        for (int i = 0, j = 1; i < SIZEARR; j++, i++)
        {
            b[i] = a[j];

        }
        /*start ad pick*/
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
        pstmt = con->prepareStatement("INSERT INTO services(phone,Pedicure,Manicure,Nail_Building ,Eyebrow_Shaping , Mustache_Wax,Leg_Wax ,Hand_Wax, Back_Wax ,Crevices_Wax  ,time_To_Do ,total_Price) VALUES(?,?,?,?,?,?,?,?,?,?,?)");
        pstmt->setString(1, phone);
        for (int i = 0; i < SIZEARR; i++)
        {
            if (b[i] == 1)
            {
                pstmt->setBoolean(i + 1, true);
            }
        }
        pstmt->execute();

        for (int i = 0; i < SIZEARR; i++)
        {
            if (b[i] == 1)
            {
                /*select gender from customer ,where phone=?  -->phone */
                pstmt = con->prepareStatement("SELECT gender FROM customer where phone=?;");
                //pstmt->setString(1, phone);   //????
                result = pstmt->executeQuery();
                genderDB = result->getString(1).c_str();

                /*if female else male*/
                if (genderDB == gender[0])
                {
                    /*select servicePrice from servicepricemale  where servie=services_c[i]"*/
                    pstmt = con->prepareStatement("SELECT servicePrice FROM servicepricemale where servie=?;");
                    //pstmt->setString(i+1, services_c[i]);   //???? indata onrun
                    result = pstmt->executeQuery();
                    totalPrice += result->getInt(1);
                    
                }
                else
                {
                    /*select servicePrice from servicepricefemale  where servie=services_c[i]"*/
                    pstmt = con->prepareStatement("SELECT servicePrice FROM servicepricefemale where servie=?;");
                    //pstmt->setString(i+1, services_c[i]);   //????
                    result = pstmt->executeQuery();
                    totalPrice += result->getInt(1);
                }




                pstmt->setBoolean(i + 1, true);
            }
        }


        delete result;
        delete pstmt;
        delete con;
        system("pause");













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
    //stmt->execute("CREATE TABLE servicesPriceForFemale ( service VARCHAR(50),servicePrice INTEGER,time_To_Do INTEGER);");
   // stmt->execute("CREATE TABLE servicesPriceForMale ( service VARCHAR(50),servicePrice INTEGER,time_To_Do INTEGER);");
     //stmt->execute("CREATE TABLE services ( phone VARCHAR(20),Pedicure BOOLEAN DEFAULT FALSE,Manicure BOOLEAN DEFAULT FALSE,Nail_Building BOOLEAN DEFAULT FALSE,Eyebrow_Shaping BOOLEAN DEFAULT FALSE, Mustache_Wax BOOLEAN DEFAULT FALSE,Leg_Wax BOOLEAN DEFAULT FALSE,Hand_Wax BOOLEAN DEFAULT FALSE, Back_Wax BOOLEAN DEFAULT FALSE,Crevices_Wax BOOLEAN DEFAULT FALSE ,time_To_Do VARCHAR(50),total_Price INTEGER);");
    //stmt->execute("CREATE TABLE customer (phone VARCHAR(50) PRIMARY KEY,name VARCHAR(50),gender VARCHAR(10), creationDate VARCHAR(50));");
    /*Printing*/
    cout << "Finished creating table" << endl;
    delete stmt;
    delete con;
    system("pause");
}


            /* insert price of Services*/
void InsertDataToPriceServices()
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
    /*start work with database name:--- */
    con->setSchema(nameData);


    /*INSERT DATA TO*/
    //pstmt = con->prepareStatement("INSERT INTO servicesPriceForFemale(service,servicePrice,time_To_do) VALUES(?,?,?)");
    pstmt = con->prepareStatement("INSERT INTO servicespriceformale(service,serviceprice,time_To_Do) VALUES(?,?,?)");
    pstmt->setString(1, "Pedicure");
    pstmt->setInt(2, 100);
    pstmt->setInt(3, 40);
    pstmt->execute();
    pstmt->setString(1, "Manicure");
    pstmt->setInt(2, 80);
    pstmt->setInt(3, 40);
    pstmt->execute();
    pstmt->setString(1, "Nail_Building");
    pstmt->setInt(2, 150);
    pstmt->setInt(3, 70);
    pstmt->execute();
    pstmt->setString(1, "Eyebrow_Shaping");
    pstmt->setInt(2, 40);
    pstmt->setInt(3, 10);
    pstmt->execute();
    pstmt->setString(1, "Mustache_Wax");
    pstmt->setInt(2, 100);
    pstmt->setInt(3, 10);
    pstmt->execute();
    pstmt->setString(1, "Leg_Wax");
    pstmt->setInt(2, 100);
    pstmt->setInt(3, 20);
    pstmt->execute();
    pstmt->setString(1, "Hand_Wax");
    pstmt->setInt(2, 100);
    pstmt->setInt(3, 15);
    pstmt->execute();
    pstmt->setString(1, "Back_Wax");
    pstmt->setInt(2, 100);
    pstmt->setInt(3, 40);
    pstmt->execute();
    pstmt->setString(1, "Cervices_Wax");
    pstmt->setInt(2, 80);
    pstmt->setInt(3, 20);
    pstmt->execute();
    cout << "rows inserted." << endl;
    delete pstmt;
    delete con;
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