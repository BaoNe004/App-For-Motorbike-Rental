#include "member.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// constructor 

Member::Member(string username = "", string password = "", string fullname = "", string phonenumber = "", double credit = 20, string idType = "", string licenseNumber = "", string expiryDate = "", Motorcycle motorcycle = Motorcycle(), vector<int> rating = {}, vector<string> comment = {}, bool available = true, string ownerName = "none") {
    this->username = username,
    this->password = password,
    this->fullname = fullname,
    this->phonenumber = phonenumber,
    this->credit = credit,
    this->idType = idType,
    this->licenseNumber = licenseNumber,
    this->expiryDate = expiryDate,
    this->motorcycle = motorcycle,
    this->rating = rating,
    this->comment = comment,
    this->available = available,
    this->ownerName = ownerName,
    this->request = Request();
    request.name = username;
}

// getter

string Member::getUsername() {
    return username;
}

string Member::getPassword() {
    return password;
}

string Member::getFullname() {
    return fullname;
}

string Member::getPhonenumber() {
    return phonenumber;
}

double Member::getCredit() {
    return credit;
}

string Member::getIdType() {
    return idType;
}

string Member::getLicenseNumber() {
    return licenseNumber;
}

string Member::getExpiryDate() {
    return expiryDate;
}

vector<int> Member::getRating() {
    return rating;
}

vector<string> Member::getComment() {
    return comment;
}

bool Member::getAvailable() {
    return available;
}

string Member::getOwnerName() {
    return ownerName;
}

Motorcycle Member::getMotorcycle() {
    return motorcycle;
}

// setter

void Member::setUsername(string username) {
    this->username = username;
}

void Member::setPassword(string password) {
    this->password = password;
}

void Member::setFullname(string fullname) {
    this->fullname = fullname;
}

void Member::setPhonenumber(string phonenumber) {
    this->phonenumber = phonenumber;
}  

void Member::setCredit(double credit){
    this->credit = credit;
}

void Member::setIdType(string idType) {
    this->idType = idType;
}

void Member::setLicenseNumber(string licenseNumber) {
    this->licenseNumber = licenseNumber;
}

void Member::setExpiryDate(string expiryDate) {
    this->expiryDate = expiryDate;
}

void Member::setRating(vector<int> rating) {
    this->rating = rating;
}

void Member::setComment(vector<string> comment) {
    this->comment = comment;
}

void Member::setAvailable(bool available) {
    this->available = available;
}

void Member::setOwnerName(string ownerName) {
    this->ownerName = ownerName;
}

void Member::setMotorcycle(Motorcycle motorcycle) {
    this->motorcycle = motorcycle;
}

// functions

void Member::setMotorcycleRenter(string renterName) {
    this->motorcycle.setRenterName(renterName);
}

void Member::setMotorcycleRating(vector<int> ratingV) {
    this->motorcycle.setRating(ratingV);
}

void Member::setMotorcycleComment(vector<string> commentV) {
    this->motorcycle.setComment(commentV);
}

void Member::toggleMotorcycleAvailable() {
    this->motorcycle.toggleAvailable();
}

float Member::getAverage() {
    if(rating.size() == 0) {
        return 0;
    }
    int total = 0;
    for(int r : rating) {
        total += r;
    }
    return total/this->rating.size();
}

Member Member::registerMember(vector<Member> memberList) {
    // enter username
    string inputUsername;
    while(true) {
        cout << "Enter your username: ";
        getline(cin, inputUsername);
        int breakPoint = 0;
        for(Member member : memberList) {
            if(inputUsername == member.getUsername()) {
                cout << "This username already exists.\n";
                cout << "Enter a different username.\n\n";
                breakPoint = 1;
                break;
            }
        }
        if (breakPoint == 0) {
            break;
        }
    }

    // enter password
    cout << "Enter your password: ";
    string inputPassword;
    getline(cin, inputPassword);

    // enter fullname
    cout << "Enter your full name: ";
    string inputFullname;
    getline(cin, inputFullname);

    // enter phonenumber
    string inputPhonenumber;
    cout << "Enter your phone number: ";
    getline(cin, inputPhonenumber);

    // enter license info
    string inputIdType, inputLicenseNumber, inputExpiryDate;
    cout << "Enter your ID Type: ";
    getline(cin, inputIdType);
    cout << "Enter your License Number: ";
    getline(cin, inputLicenseNumber);
    cout << "Enter your License Expiry Date: ";
    getline(cin, inputExpiryDate);

    string inputModel, inputColor, inputTransmission, inputEngineSize, inputYearMade, inputCity, inputDescription;
    cout << "Enter your motorcycle's model: ";
    getline(cin, inputModel);
    cout << "Enter your motorcycle's color: ";
    getline(cin, inputColor);
    cout << "Enter your motorcycle's engine size (int): ";
    getline(cin, inputEngineSize);
    int intEngineSize = stoi(inputEngineSize);
    cout << "Enter your motorcycles's transmission: ";
    getline(cin, inputTransmission);
    cout << "Enter your motorcycle's year made: ";
    getline(cin, inputYearMade);
    int intYearMade = stoi(inputYearMade);
    while(true) {
        // limit the location for our application for simplicity
        cout << "Enter your motorcycle's city location (Ha Noi/Sai Gon): ";
        getline(cin, inputCity);
        int breakPoint = 0;
        if(inputCity != "Ha Noi" && inputCity != "Sai Gon") {
            cout << "You can only choose between Ha Noi and Sai Gon.\n";
            breakPoint = 1;
        }
        if(breakPoint == 0) {
            break;
        }
    }
    cout << "Enter your motorcycle's description': ";
    getline(cin, inputDescription);
    Motorcycle newMotorcycle(inputModel, inputColor, intEngineSize, inputTransmission, intYearMade, inputDescription, inputCity, "none", {}, {}, true, false);
    Member newMember(inputUsername, inputPassword, inputFullname, inputPhonenumber, 20, inputIdType, inputLicenseNumber, inputExpiryDate, newMotorcycle);
    cout << "You are registered successfully. Welcome to our application!\n\n";
    return newMember;
}

void Member::checkOut(Member &owner) {
        string stringRate, stringComment;
        vector<int> ratingV = owner.getMotorcycle().getRating();
        vector<string> commentV = owner.getMotorcycle().getComment();
        int rate;
        while (true)
        {
            while (true) {
                cout << "Please rate the owner (int from 0 to 10): ";
                getline(cin, stringRate);
                if (stoi(stringRate) > 10 || stoi(stringRate) <0) {
                    cout << "Please enter a rating from 0 to 10!\n";
                } else {
                    break;
                }
            }
            ratingV.push_back(stoi(stringRate));
            owner.setRating(ratingV);

            cout << "Please comment on the motorcycle: ";
            getline(cin, stringComment);
            commentV.push_back(stringComment);
            owner.setMotorcycleComment(commentV);
            break;
        }
}

void Member::rateRenter(Member &renter) {
        string stringRating, stringComment;
        vector<int> ratingV = renter.getRating();
        vector<string>commentV = renter.getComment();
        int rate;
        while (true)
        {
            while (true) {
                cout << "Please rate the renter (int from 0 to 10): ";
                getline(cin, stringRating);
                if (stoi(stringRating) > 10 || stoi(stringRating) <0) {
                    cout << "Please enter a rating from 0 to 10!\n";
                } else {
                    break;
                }
            }
            ratingV.push_back(stoi(stringRating));
            renter.setRating(ratingV);

            cout << "Please comment on the occupier: ";
            getline(cin, stringComment);
            commentV.push_back(stringComment);
            renter.setComment(commentV);
            break;
        }
}

void Member::acceptRequest(vector<Member> &members) {
    if (!this->motorcycle.getAvailable()) {
        cout << "Motorcycle is being used already." << endl;
        return;
    }

    string stringOwnerName = this->username;
	string result("");
    string information("");
	for(Member m : members){
		if(this->phonenumber == m.phonenumber){
			result = m.request.requests;
		}

	}
    for(Member m : members){
		if(result.find(m.getPhonenumber() )!= -1){
			information = information + "Credit: " + to_string(m.getCredit()) + "\nAverage rating: " + to_string(m.getAverage()) + "\nUsername: " + m.getUsername() + "\nPhone number: " + m.getPhonenumber();
		}

	}
    if(result == ""){
        cout<< "There is no request made to your motorcycle yet." << endl;
        return;
    }

	cout << "Requests made to your motorcycle as followings:" << endl;
    cout << information;

	cout << "Enter the username of the renter that you want to rent your motorcycle to: ";
	string choiceRenter;
	cin >> choiceRenter;

	if(result.find(choiceRenter) != -1){
		for(Member &owner : members){
				if(this->username == owner.username){               
					owner.request.requests = choiceRenter;
				}
			}
            for(Member &renter : members) {
                if(choiceRenter == renter.username) {
                    renter.setAvailable(false);
                    renter.setOwnerName(this->username);
                    this->motorcycle.setRenterName(renter.getUsername());
                }
            }
		this->motorcycle.toggleAvailable();
    
        cout << "Accepted the chosen request successfully." << endl;
	}
}


void Member::creditTopUp(int moneySpent) {
    credit += moneySpent;
    //modify text
}

// int Member::makeRequest(Motorcycle model) {
//     // Access the owner attribute, then access owner's request, then set owner's request request to renter phone number
//     model.getOwner().getRequest().setRequest(this->phonenumber);
//     model.getOwner().getRequest().setName(model.getOwner().getPhonenumber());
// }

void Member::rentMotorcycle(Motorcycle model) {

        // If member credit is not enough, ask them to either quit and return later or top up
        // top up will usee the creditTopUp function in member class

        if(credit < model.getRequiredCredit()) {
            std::cout << "You don't have enough credit in order to rent this motorcycle!\n";
            std::cout << "1. Top up\n2. Quit\nPlease enter your choice: ";
            int choice;
            std::cin >> choice;
            switch(choice){
                case 1:
                    int moneySpent;
                    std::cout << "Please enter the amount you want to top up: ";
                    std::cin.ignore(1,'\n');
                    std::cin >> moneySpent;
                    std::cout << "Your credit was " << credit << ", your new credit balance is ";
                    creditTopUp(moneySpent);
                    std::cout << credit << std::endl;
                    break;
                case 2:
                    std::cout << "Please prepare the amount of credit next time!";
                    break;
            }
        }
        else if(credit < model.getRequiredCredit()) {
            std::cout << "You have enough credit to make a request for this Motorcycle!\n";
            // makeRequest(model);
            std::cout << "Successfully created request, please wait for owner's answer\n";
        }
}