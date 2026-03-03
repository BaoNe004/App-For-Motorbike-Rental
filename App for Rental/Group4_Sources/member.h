#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "motorcycle.h"
#include "request.h"

class Member {
private:   
    string username;
    string password;
    string fullname;
    string phonenumber;
    double credit;

    string idType;
    string licenseNumber;
    string expiryDate;
    Motorcycle motorcycle;
    vector<int> rating;
    vector<string> comment;

    bool available;
    string ownerName;

public:
    // request
    Request request;

    // constructor

    Member() {};

    Member(string username, string password, string fullname, string phonenumber, double credit, string idType, string licenseNumber, string expiryDate, Motorcycle motorcycle, vector<int> rating, vector<string> comment, bool available, string ownerName);
    
    // getter

    string getUsername();

    string getPassword();

    string getFullname();

    string getPhonenumber();

    double getCredit();

    string getIdType();

    string getLicenseNumber();

    string getExpiryDate();

    vector<int> getRating();

    vector<string> getComment();

    bool getAvailable();

    string getOwnerName();

    Motorcycle getMotorcycle();

    // setter

    void setUsername(string username);

    void setPassword(string password);

    void setFullname(string fullname);

    void setPhonenumber(string phonenumber);

    void setCredit(double credit);

    void setIdType(string idType);

    void setLicenseNumber(string licenseNumber);

    void setExpiryDate(string expiryDate);

    void setRating(vector<int> rating);

    void setComment(vector<string> comment);

    void setAvailable(bool available);

    void setOwnerName(string ownerName);

    void setMotorcycle(Motorcycle motorcycle);

    // fuctions

    void setMotorcycleRenter(string renterName);

    void setMotorcycleRating(vector<int> ratingV);

    void setMotorcycleComment(vector<string> commentV);

    void toggleMotorcycleAvailable();

    float getAverage();

    Member registerMember(vector<Member> memberList);

    void checkOut(Member &owner);

    void rateRenter(Member &renter);

    void acceptRequest(vector<Member> &members);

    void creditTopUp(int moneySpent);
    
    int makeRequest(Motorcycle model);

    void rentMotorcycle(Motorcycle model);
};

#endif