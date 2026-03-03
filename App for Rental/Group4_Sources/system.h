#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstring>
using namespace std;

#include "Member.h"
#include "Motorcycle.h"
#include "Admin.h"

#define FILENAME "data.txt"

class System {
private:
    vector<Member> memberList;
    vector<Motorcycle> motorcycleList;

public:
    string usernameOwner = "";
    string usernameRenter = "";
    int requiredCreditOwner = 0;

    System() {};

    System(vector<Member> memberList, vector<Motorcycle> motorcycleList);
    
    bool fetchData();

    Member loginMember(vector<Member> memberList, vector<Motorcycle> motorcycleList);

    void loginAdmin();

    void showAllMotorcycleBasic(vector<Motorcycle> motorcycleList);

    void showAllMotorcycleDetail(Member member, vector<Motorcycle> motorcycleList);

    void showAllInfo(vector<Member> memberList); // by admin

    Member listMotorcycleAvailable(Member member, vector<Motorcycle> motorcycleList);

    void searchAllAvailableMotorcycle(Member member, vector<Motorcycle> motorcycleList);

    void showMyInfo(Member member);

    void showMember();

    bool saveData(Member member);

    bool saveAllData(bool checkNewMember, vector<Member> memberList, Member member); // runs when the program in terminated

    vector<Member> getMemberList();

    vector<Motorcycle> getMotorcycleList();

    void pushMemberList(Member member);

    void setMemberList(vector<Member> memberList);

    void pushMotorcycleList(Motorcycle motorcycle);
};

#endif