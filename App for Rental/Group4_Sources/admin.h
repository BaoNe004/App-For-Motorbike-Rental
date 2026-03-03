#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::cout;
using std::cin;
using std::string;
#include <vector>
#include <regex>
#ifndef ADMIN
#define ADMIN


class Admin {
private:
    string username = "group4";
    string password = "group4pw";

public:
    Admin() {};

    Admin(string username, string password);

    string getUsername();

    string getPassword();
};
#endif