#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using std::cout;
using std::cin;
using std::string;
#include <vector>
#include <regex>

#include "admin.h"

Admin::Admin (string username = "", string password = "") : username(this->username), password(this->password) {};

string Admin::getUsername() {
    return this->username;
}

string Admin::getPassword() {
    return this->password;
}