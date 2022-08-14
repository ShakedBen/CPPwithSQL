#include "Register.h"
Register::Register(string phone, string name, string gender)
{
    this->phone = phone;
    this->name = name;
    this->gender = gender;
    localDataForLoginAndConnectDatabaseAndinsertNewCustomer();
}
bool Register::localDataForLoginAndConnectDatabaseAndinsertNewCustomer()
{
    string s, u, p;
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char* dt = ctime(&now);
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
            inFile >> s >> u >> p;

        }
        inFile.close();
        return true;
    }

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
    return 0;
}
