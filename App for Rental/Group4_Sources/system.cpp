#include <iostream>
#include <vector>
using namespace std;

#include "system.h"

System::System(vector<Member> memberList = {}, vector<Motorcycle> motorcycleList = {})
{
    this->memberList = memberList;
    this->motorcycleList = motorcycleList;
}

bool System::fetchData() {
    fstream checkFile;
    checkFile.open(FILENAME, std::ios::in);

    string checkSen;

    getline(checkFile, checkSen);

    if (checkSen == "")
    {
        memberList = {};
        motorcycleList = {};
        return true;
    }

    fstream dataFile;
    dataFile.open(FILENAME, std::ios::in);

    if (!dataFile.is_open())
    {
        cout << "Fail to open the file\n";
        return false;
    }

    while (!dataFile.eof())
    {
        // member attributes
        string username, password, fullname, phonenumber, stringUserCredit, idType, licenseNumber, expiryDate, stringUserRating, stringUserComments, stringMemberAvailable, ownerName;
        double credit;
        vector<int> memberRating;
        vector<string> memberComment;
        bool memberAvailable;

        // motorcycle attributes
        string model, color, stringEngineSize, transmission, stringYearMade, description, city, renterName, stringMotorcycleRating, stringMotorcycleComments, stringMotorcycleAvailable, stringListed, stringRequirementToRent, stringRequiredCredit, periodStart, periodEnd;
        int engineSize, yearMade;
        double requiredCredit;
        float requirementToRent;
        vector<string> motorcycleComments;
        vector<int> motorcycleRating;
        bool motorcycleAvailable, listed;

        // read user's information
        getline(dataFile, username, ',');
        if (username == "")
        {
            break;
        }
        getline(dataFile, password, ',');
        getline(dataFile, fullname, ',');
        getline(dataFile, phonenumber, ',');
        getline(dataFile, stringUserCredit, ',');
        credit = stod(stringUserCredit);
        getline(dataFile, idType, ',');
        getline(dataFile, licenseNumber, ',');
        getline(dataFile, expiryDate, ',');
        getline(dataFile, stringUserRating, ',');
        if (stringUserRating != "") {
            istringstream iss(stringUserRating);
            string rating;
            while (getline(iss, rating, '_')) {
                memberRating.push_back(stoi(rating));
            }
        }
        getline(dataFile, stringUserComments, ',');
        if (stringUserComments != "") {
            istringstream iss(stringUserComments);
            string comment;
            while (getline(iss, comment, '_')) {
                memberComment.push_back(comment);
            }
        }
        getline(dataFile, stringMemberAvailable, ',');
        memberAvailable = stoi(stringMemberAvailable);
        getline(dataFile, ownerName, '\n');

        // read motorcycle's information
        getline(dataFile, model, ',');
        getline(dataFile, color, ',');
        getline(dataFile, stringEngineSize, ',');

        getline(dataFile, transmission, ',');
        getline(dataFile, stringYearMade, ',');

        getline(dataFile, description, ',');
        getline(dataFile, city, ',');
        getline(dataFile, renterName, ',');
        getline(dataFile, stringMotorcycleRating, ',');
        if (stringMotorcycleRating != "") {
            std::istringstream iss(stringMotorcycleRating);
            string rate;
            while (getline(iss, rate, '_'))
            {
                motorcycleRating.push_back(stoi(rate));
            }
        }
        getline(dataFile, stringMotorcycleComments, ',');
        if (stringMotorcycleComments != "") {
            std::istringstream iss(stringMotorcycleComments);
            string comment;
            while (getline(iss, comment, '_'))
            {
                motorcycleComments.push_back(comment);
            }
        }
        getline(dataFile, stringMotorcycleAvailable, ',');
        motorcycleAvailable = stoi(stringMotorcycleAvailable);
        getline(dataFile, stringListed, ',');
        listed = stoi(stringListed);
        if (listed == 0)
        {
            string nextLine;
            getline(dataFile, nextLine, '\n');
            Member member(username, password, fullname, phonenumber, credit, idType, licenseNumber, expiryDate, Motorcycle(model, color, engineSize, transmission, yearMade, description, city, renterName, motorcycleRating, motorcycleComments, motorcycleAvailable, listed), memberRating, memberComment, memberAvailable, ownerName);
            memberList.push_back(member);
            motorcycleList.push_back(member.getMotorcycle());
        }
        else
        {
            getline(dataFile, stringRequirementToRent, ',');
            requirementToRent = stoi(stringRequirementToRent);
            getline(dataFile, stringRequiredCredit, ',');
            requiredCredit = stod(stringRequiredCredit);
            getline(dataFile, periodStart, ',');
            getline(dataFile, periodEnd, '\n');

            Member member(username, password, fullname, phonenumber, credit, idType, licenseNumber, expiryDate, Motorcycle(model, color, engineSize, transmission, yearMade, description, city, renterName, motorcycleRating, motorcycleComments, motorcycleAvailable, listed, requirementToRent, requiredCredit, periodStart, periodEnd), memberRating, memberComment, memberAvailable, ownerName);
            member.setOwnerName(ownerName);
            memberList.push_back(member);
            motorcycleList.push_back(member.getMotorcycle());
        }
    }

    dataFile.close();
    return true;
}

Member System::loginMember(vector<Member> memberList, vector<Motorcycle> motorcycleList) {
    string inputUsername;

    Motorcycle motorcycle;
    Member m;

    while (true)
    {
        cout << "Enter your username: ";

        do
        {
            getline(cin, inputUsername);
        } while (inputUsername == "");

        for (Member member : memberList)
        {
            if (inputUsername == member.getUsername())
            {
                motorcycle.setModel(member.getMotorcycle().getModel());
                motorcycle.setColor(member.getMotorcycle().getColor());
                motorcycle.setEngineSize(member.getMotorcycle().getengineSize());
                motorcycle.setTransmission(member.getMotorcycle().getTransmission());
                motorcycle.setYearMade(member.getMotorcycle().getYearMade());
                motorcycle.setDescription(member.getMotorcycle().getDescription());
                motorcycle.setCity(member.getMotorcycle().getCity());
                motorcycle.setRenterName(member.getMotorcycle().getRenterName());
                motorcycle.setRating(member.getMotorcycle().getRating());
                motorcycle.setComment(member.getMotorcycle().getComment());
                motorcycle.setAvailable(member.getMotorcycle().getAvailable());
                motorcycle.setListed(member.getMotorcycle().getListed());
                if (member.getMotorcycle().getListed() == 1)
                {
                    string mPeriodStart = member.getMotorcycle().getperiodStart();
                    string mPeriodEnd = member.getMotorcycle().getperiodEnd();
                    double mRequiredCredit = member.getMotorcycle().getRequiredCredit();
                    float mRequirementToRent = member.getMotorcycle().getRequirementToRent();

                    motorcycle.setperiodStart(mPeriodStart);
                    motorcycle.setperiodEnd(mPeriodEnd);
                    motorcycle.setRequiredCredit(mRequiredCredit);
                    motorcycle.setRequirementToRent(mRequirementToRent);
                }

                m.setUsername(member.getUsername());
                m.setPassword(member.getPassword());
                m.setFullname(member.getFullname());
                m.setPhonenumber(member.getPhonenumber());
                m.setCredit(member.getCredit());
                m.setIdType(member.getIdType());
                m.setLicenseNumber(member.getLicenseNumber());
                m.setExpiryDate(member.getExpiryDate());
                m.setMotorcycle(motorcycle);
                m.setRating(member.getRating());
                m.setComment(member.getComment());
                m.setAvailable(member.getAvailable());
                m.setOwnerName(member.getOwnerName()); 

                string inputPassword;
                while (true) {
                    cout << "Enter your password: ";
                    getline(cin, inputPassword);
                    if (inputPassword == m.getPassword()) {
                        cout << "You are logged in!\n";
                        return m;
                        break;
                    } else {
                        cout << "Wrong password." << endl;
                    }
                }
                break;
            }
        }
        cout << "Username does not exist." << endl;
    }
}

void System::loginAdmin() {
    Admin admin;
    string username;
    while (true) {
        cout << "Enter username: ";
        getline(cin, username);

        if (username == admin.getUsername()) {
            string password;
            while (true) {
                cout << "Enter password: ";
                getline(cin, password);

                if (password == admin.getPassword()) {
                    cout << "You are logged in!" << endl;
                    break;
                }
                else {
                    cout << "Wrong password." << endl;
                }
            }
            break;
        }
        cout << "Incorrect username." << endl;
    }
}

void System::showAllMotorcycleBasic(vector<Motorcycle> motorcycleList) {
    cout << "All motorcycle Information:" << endl;

    int index = 1;

    for (Motorcycle motorcycle : motorcycleList)
    {
        cout << "Motorcycle " << index << "." << endl;
        cout << "    Model: " << motorcycle.getModel() << endl;
        cout << "    Color: " << motorcycle.getColor() << endl;
        cout << "    Engine size: " << motorcycle.getengineSize() << endl;
        cout << "    Year:" << motorcycle.getYearMade() << endl;
        cout << "    Description: " << motorcycle.getDescription() << endl;
        index++;
    }
}

void System::showAllMotorcycleDetail(Member member, vector<Motorcycle> motorcycleList) {
    cout << "All motorcycle Information:" << endl;

    int index = 1;

    for (Motorcycle motorcycle : motorcycleList)
    {
        cout << "Motorcycle " << index << "." << endl;
        cout << "    Model: " << motorcycle.getModel() << endl;
        cout << "    Color: " << motorcycle.getColor() << endl;
        cout << "    Engine size: " << motorcycle.getengineSize() << endl;
        cout << "    Year:" << motorcycle.getYearMade() << endl;
        cout << "    Description: " << motorcycle.getDescription() << endl;
        cout << "    Ratings: ";
        if (motorcycle.getRating().size() == 0) {
            cout << "No ratings yet.";
        } else {
            for(int i = 0; i < motorcycle.getRating().size(); i++){
                cout << motorcycle.getRating()[i] << ", ";
            }
        }
        cout << endl;
        cout << "    Comments: ";
        if (motorcycle.getComment().size() == 0) {
            cout << "No comments yet.";
        } else {
            for(int i = 0; i < motorcycle.getComment().size(); i++) {
                cout << motorcycle.getComment()[i] << ", ";
            }
        }
        cout << endl;
        cout << "    Requirement: " << motorcycle.getRequirementToRent() << endl;
        cout << "    City: " << motorcycle.getCity() << endl;
        cout << "    Credit cost: " << motorcycle.getRequiredCredit() << endl;
        cout << "    Availability: ";
        if (motorcycle.getAvailable() == true) {
            if (motorcycle.getRenterName() != "") {
                cout << "Available. It is already rented now." << endl;
            } else {
                cout << "Available. It is not rented by anyone." << endl;
            }
        } else {
            cout << "Unavailable. It is already rented now." << endl;
        }
        index++;
    }
}

void System::showAllInfo(vector<Member> memberList) {
    cout << "All Members & Motorcycles Information: " << endl;

    int index = 1;

    for (Member member : memberList)
    {
        cout << "User " << index << "." << endl;
        cout << "    Username: " << member.getUsername() << endl;
        cout << "    Password: " << member.getPassword() << endl;
        cout << "    Phone number: " << member.getPhonenumber() << endl;
        cout << "    Total credit: " << member.getCredit() << endl;
        cout << "    Rating: ";
        if (member.getRating().size() == 0) {
            cout << "No ratings yet.";
        } else {
            for(int i = 0; i < member.getRating().size(); i++){
                cout << member.getRating()[i] << ", ";
            }
        }
        cout << endl;
        cout << "    Comments: ";
        if (member.getComment().size() == 0) {
            cout << "No comments yet.";
        } else {
            for(int i = 0; i < member.getComment().size(); i++) {
                cout << member.getComment()[i] << ", ";
            }
        }
        cout << endl;

        cout << "    Motorcycle information:" << endl;

        cout << "        City: " << member.getMotorcycle().getCity() << endl;
        cout << "        Descrption: " << member.getMotorcycle().getDescription() << endl;
        cout << "        Ratings: ";
        if (member.getMotorcycle().getRating().size() == 0) {
            cout << "No ratings yet.";
        } else {
            for(int i = 0; i < member.getMotorcycle().getRating().size(); i++){
                cout << member.getMotorcycle().getRating()[i] << ", ";
            }
        }
        cout << endl;
        cout << "        Comments: ";
        if (member.getMotorcycle().getComment().size() == 0) {
            cout << "No comments yet.";
        } else {
            for(int i = 0; i < member.getMotorcycle().getComment().size(); i++) {
                cout << member.getMotorcycle().getComment()[i] << ", ";
            }
        }
        cout << endl;
        cout << "        Availability: ";
        if (member.getMotorcycle().getAvailable() == true) {
            if (member.getMotorcycle().getRenterName() != "") {
                cout << "Available. It is already rented now." << endl;
            } else {
                cout << "Available. It is not rented by anyone." << endl;
            }
        } else {
            cout << "Unavailable. It is already rented now." << endl;
        }
        index++;
    }
}

Member System::listMotorcycleAvailable(Member member, vector<Motorcycle> motorcycleList) {
    if (member.getMotorcycle().getAvailable() == 0)
    {
        cout << "The motorcycle is in rent.\n"
             << "You cannot rent the motorcycle until the previous renting is over.\n";
        return member;
    }

    cout << "Rent / Return a Motorcycle" << endl;

    string periodStart;
    string periodEnd;
    float requirementToRent;
    double requiredCredit;

    for (Motorcycle motorcycle : motorcycleList)
    {
        string memModel = member.getMotorcycle().getModel();
        string memColor = member.getMotorcycle().getColor();
        int memEngineSize = member.getMotorcycle().getengineSize();
        string memTransmission = member.getMotorcycle().getTransmission();
        int memYearMade = member.getMotorcycle().getYearMade();
        string memDescription = member.getMotorcycle().getDescription();
        string memCity = member.getMotorcycle().getCity();
        string memRenterName = member.getMotorcycle().getRenterName();
        vector<int> memRating = member.getMotorcycle().getRating();
        vector<string> memComment = member.getMotorcycle().getComment();
        bool memAvailable = member.getMotorcycle().getAvailable();

        if (member.getMotorcycle().getListed() == false) {
            string list;
            cout << "Do you want to list your motorcycle on rent? (Y/N): ";
            getline(cin, list);

            if (list == "Y") {
                cout << "Enter a start period in yyyymmdd: ";
                getline(cin, periodStart);
                cout << "Enter a end point in yyyymmdd: ";
                getline(cin, periodEnd);
                cout << "Enter a required credit during for renting: ";
                cin >> requiredCredit;
                cout << "Enter a required rating of the owner: ";
                cin >> requirementToRent;
                member.setMotorcycle(Motorcycle(memModel, memColor, memEngineSize, memTransmission, memYearMade, memDescription, memCity, memRenterName, memRating, memComment, memAvailable, 1, requirementToRent, requiredCredit, periodStart, periodEnd));
                cout << "Your motorcycle is listed now." << endl;
                break;
            } else if (list == "N") {
                cout << "Return to menu" << endl;
                break;
            } else {
                cout << "Invalid choice" << endl;
            }
        } else {
            string unlist;
            cout << "Do you want to unlist your motorcycle from rent? (Y/N): ";
            getline(cin, unlist);

            if (unlist == "Y") {
                requirementToRent = 0;
                requiredCredit = 0;
                periodStart = "";
                periodEnd = "";

                member.setMotorcycle(Motorcycle(memModel, memColor, memEngineSize, memTransmission, memYearMade, memDescription, memCity, memRenterName, memRating, memComment, memAvailable, 0));

                cout << "Your motorcycle is unlisted from rent now." << endl;

                break;
            } else if (unlist == "N") {
                cout << "Return to menu." << endl;
                break;
            } else {
                cout << "Invalid choice" << endl;
            }
        }
    }
    return member;
}

void System::searchAllAvailableMotorcycle(Member member, vector<Motorcycle> motorcycleList) {
    cout << "Search All Available motorcycles.";
    cout << "(Your credit: " << member.getCredit() << ", average rating: " << member.getAverage() << endl;

    string start;

    cout << "Enter the start time period that you want (yyyymmdd): ";
    getline(cin, start);

    string end;

    cout << "Enter the end point that you want(YYYYMMDD): ";
    getline(cin, end);

    cout << "Enter the city location that you want (Ha Noi / Sai Gon): ";

    string cityName;
    getline(cin, cityName);

    if (cityName == "Ha Noi") {
        int motorcycleIndex = 1;
        cout << "Available motorcycle list in " << cityName << ":" << endl;
        for (Motorcycle motorcycle : motorcycleList)
        {
            if ((motorcycle.getCity() == "Ha Noi") && (motorcycle.getAvailable() == true) && (motorcycle.getListed() == true) && (motorcycle.getRequirementToRent() <= member.getAverage()) && (motorcycle.getRequiredCredit() <= member.getCredit()) && (stoi(start) <= stoi(motorcycle.getperiodStart())) && (stoi(motorcycle.getperiodEnd()) <= stoi(end))) {
                cout << "    Motorcycle " << motorcycleIndex << "." << endl;
                cout << "        Model: " << motorcycle.getModel() << endl;
                cout << "        Color: " << motorcycle.getColor() << endl;
                cout << "        Engine size: " << motorcycle.getengineSize() << endl;
                cout << "        Year:" << motorcycle.getYearMade() << endl;
                cout << "        Description: " << motorcycle.getDescription() << endl;
                cout << "        Ratings: ";
                if (motorcycle.getRating().size() == 0) {
                    cout << "No ratings yet.";
                } else {
                    for(int i = 0; i < motorcycle.getRating().size(); i++){
                        cout << motorcycle.getRating()[i] << ", ";
                    }
                }
                cout << endl;
                cout << "        Comments: ";
                if (motorcycle.getComment().size() == 0) {
                    cout << "No comments yet.";
                } else {
                    for(int i = 0; i < motorcycle.getComment().size(); i++) {
                        cout << motorcycle.getComment()[i] << ", ";
                    }
                }
                cout << endl;
                cout << "        Requirement: " << motorcycle.getRequirementToRent() << endl;
                cout << "        City: " << motorcycle.getCity() << endl;
                cout << "        Credit cost: " << motorcycle.getRequiredCredit() << endl;
                cout << "        Availability: ";
                if (motorcycle.getAvailable() == true) {
                    if (motorcycle.getRenterName() != "") {
                        cout << "Available. It is already rented now." << endl;
                    } else {
                        cout << "Available. It is not rented by anyone." << endl;
                    }
                } else {
                    cout << "Unavailable. It is already rented now." << endl;
                }
                motorcycleIndex++;
            }
        }
        if (motorcycleIndex == 1) {
            cout << "There is no available motorcycle in " << cityName << " at the moment." << endl;
        }
    } else if (cityName == "Sai Gon") {
        int motorcycleIndex = 1;
        cout << "Available motorcycle list in " << cityName << ":" << endl;
        for (Motorcycle motorcycle : motorcycleList)
        {
            if ((motorcycle.getCity() == "Sai Gon") && (motorcycle.getAvailable() == true) && (motorcycle.getListed() == true) && (motorcycle.getRequirementToRent() <= member.getAverage()) && (motorcycle.getRequiredCredit() <= member.getCredit()) && (stoi(start) <= stoi(motorcycle.getperiodStart())) && (stoi(motorcycle.getperiodEnd()) <= stoi(end))) {
                cout << "    Motorcycle " << motorcycleIndex << "." << endl;
                cout << "        Model: " << motorcycle.getModel() << endl;
                cout << "        Color: " << motorcycle.getColor() << endl;
                cout << "        Engine size: " << motorcycle.getengineSize() << endl;
                cout << "        Year:" << motorcycle.getYearMade() << endl;
                cout << "        Description: " << motorcycle.getDescription() << endl;
                cout << "        Ratings: ";
                if (motorcycle.getRating().size() == 0) {
                    cout << "No ratings yet.";
                } else {
                    for(int i = 0; i < motorcycle.getRating().size(); i++){
                        cout << motorcycle.getRating()[i] << ", ";
                    }
                }
                cout << endl;
                cout << "        Comments: ";
                if (motorcycle.getComment().size() == 0) {
                    cout << "No comments yet.";
                } else {
                    for(int i = 0; i < motorcycle.getComment().size(); i++) {
                        cout << motorcycle.getComment()[i] << ", ";
                    }
                }
                cout << endl;
                cout << "        Requirement: " << motorcycle.getRequirementToRent() << endl;
                cout << "        City: " << motorcycle.getCity() << endl;
                cout << "        Credit cost: " << motorcycle.getRequiredCredit() << endl;
                cout << "        Availability: ";
                if (motorcycle.getAvailable() == true) {
                    if (motorcycle.getRenterName() != "") {
                        cout << "Available. It is already rented now." << endl;
                    } else {
                        cout << "Available. It is not rented by anyone." << endl;
                    }
                } else {
                    cout << "Unavailable. It is already rented now." << endl;
                }
                motorcycleIndex++;
            }
        }
        if (motorcycleIndex == 1) {
            cout << "There is no available motorcycle in " << cityName << " at the moment." << endl;
        }
    } else {
        cout << "Invalid Choice" << endl;
    }
}

void System::showMyInfo(Member member) {
    cout << "Your account information:" << endl; 

    cout << "   Username: " << member.getUsername() << endl;
    cout << "    Password: " << member.getPassword() << endl;
    cout << "    Fullname: " << member.getFullname() << endl;
    cout << "    Phone number: " << member.getPhonenumber() << endl;
    cout << "    credit: " << member.getCredit() << endl;
    cout << "    ID Type: " << member.getIdType() << endl;
    cout << "    License number: " << member.getLicenseNumber() << endl;
    cout << "    License expiry date: " << member.getExpiryDate() << endl;
    if (member.getAvailable() == false) {
        cout << "You are currently renting " << member.getOwnerName() << "'s motorcycle";
    };
    cout << "    Rating: ";
    if (member.getRating().size() == 0) {
        cout << "no ratings yet." << endl;
    } else {
        for (int i = 0; i < member.getRating().size(); i++) {
            cout << member.getRating()[i] << " ";
        }
        cout << endl;
    }
    cout << "    Comment: ";
    if (member.getComment().size() == 0) {
        cout << "no comments yet." << endl;
    } else {
        for (int i = 0; i < member.getComment().size(); i++) {
            cout << member.getComment()[i] << " ";
        }
        cout << endl;
    }

    cout << "    Motorcycle information:" << endl;
    cout << "        Model: " << member.getMotorcycle().getModel() << endl;
    cout << "        Color: " << member.getMotorcycle().getColor() << endl;
    cout << "        Engine size: " << member.getMotorcycle().getengineSize() << endl;
    cout << "        Year:" << member.getMotorcycle().getYearMade() << endl;
    cout << "        Description: " << member.getMotorcycle().getDescription() << endl;
    cout << "        Ratings: ";
    if (member.getMotorcycle().getRating().size() == 0) {
        cout << "No ratings yet.";
    } else {
        for(int i = 0; i < member.getMotorcycle().getRating().size(); i++){
            cout << member.getMotorcycle().getRating()[i] << ", ";
        }
    }
    cout << endl;
    cout << "        Comments: ";
    if (member.getMotorcycle().getComment().size() == 0) {
        cout << "No comments yet.";
    } else {
        for(int i = 0; i < member.getMotorcycle().getComment().size(); i++) {
            cout << member.getMotorcycle().getComment()[i] << ", ";
        }
    }
    cout << endl;
    cout << "        Requirement: " << member.getMotorcycle().getRequirementToRent() << endl;
    cout << "        City: " << member.getMotorcycle().getCity() << endl;
    cout << "        Credit cost: " << member.getMotorcycle().getRequiredCredit() << endl;
    cout << "        Availability: ";
    if (member.getMotorcycle().getAvailable() == true) {
            if (member.getMotorcycle().getRenterName() != "") {
            cout << "Available. It is already rented now." << endl;
        } else {
            cout << "Available. It is not rented by anyone." << endl;
        }
    } else {
        cout << "Unavailable. It is already rented now." << endl;
    }
}

void System::showMember() {
    
}

bool System::saveData(Member member) {
    fstream dataFile;
    dataFile.open(FILENAME, std::ios::app);

    if (!dataFile.is_open())
    {
        cout << "Failed to open the file\n";
        return false;
    }

    dataFile << member.getUsername() << "," << member.getPassword() << "," << member.getFullname() << "," << member.getPhonenumber() << "," << member.getCredit() << "," << member.getIdType() << "," << member.getLicenseNumber() << "," << member.getExpiryDate() << ",";

    if (member.getRating().size() == 0) {
        dataFile << ",";
    } else {
        int index = 1;
        for (int rate : member.getRating()) {
            if (index == member.getRating().size()) {
                dataFile << rate << ",";
                break;
            }
            dataFile << rate << "_";
            index++;
        }
    } 
    if (member.getComment().size() == 0) {
        dataFile << "," << member.getOwnerName() << "," << member.getAvailable() << "\n";
    } else {
        int index = 1;
        for (string comment : member.getComment()) {
            if (index == member.getComment().size()) {
                dataFile << comment << ",";
                break;
            }
            dataFile << comment << "_";
            index++;
        }
        dataFile << member.getAvailable() << "," << member.getOwnerName() << "\n";
    }
    

    dataFile << member.getMotorcycle().getModel() << "," << member.getMotorcycle().getColor() << "," << member.getMotorcycle().getengineSize() << "," << member.getMotorcycle().getTransmission() << "," << member.getMotorcycle().getYearMade() << "," << member.getMotorcycle().getDescription() << "," << member.getMotorcycle().getCity() << "," << member.getMotorcycle().getRenterName() << ",";
    if (member.getMotorcycle().getRating().size() == 0) {
        dataFile << ",";
    } else {
        int index = 1;
        for (int rate : member.getMotorcycle().getRating()) {
            if (index == member.getMotorcycle().getRating().size()) {
                dataFile << rate << ",";
                break;
            }
            dataFile << rate << "_";
            index++;
        }
    }
    if (member.getMotorcycle().getComment().size() == 0) {
        dataFile << ",";
    } else {
        int index = 1;
        for (string comment : member.getMotorcycle().getComment()) {
            if (index == member.getMotorcycle().getComment().size())
            {
                dataFile << comment << ",";
                break;
            }
            dataFile << comment << "_";
            index++;
        }
    }
    dataFile << member.getMotorcycle().getAvailable() << "," << member.getMotorcycle().getListed() << ",";

    if (member.getMotorcycle().getListed() == false) {
        dataFile << "\n";
    } else {
        dataFile << member.getMotorcycle().getRequirementToRent() << member.getMotorcycle().getRequiredCredit() << member.getMotorcycle().getperiodStart() << "," << member.getMotorcycle().getperiodEnd() << "\n";
    }

    dataFile.close();

    return true;
}

bool System::saveAllData(bool checkNewMember, vector<Member> memberList, Member member) {
    if (checkNewMember == true) {
        saveData(member);
    } else {
        fstream dataFile;
        dataFile.open(FILENAME, ios::out);

        if (!dataFile.is_open()) {
            cout << "Failed to open the file\n";
            return false;
        }

        for (Member existMember : memberList) {
            if (member.getUsername() == existMember.getUsername()) {
                existMember = member;
                if (member.getMotorcycle().getListed() == 1) {
                    string memModel = member.getMotorcycle().getModel();
                    string memColor = member.getMotorcycle().getColor();
                    int memEngineSize = member.getMotorcycle().getengineSize();
                    string memTransmission = member.getMotorcycle().getTransmission();
                    int memYearMade = member.getMotorcycle().getYearMade();
                    string memDescription = member.getMotorcycle().getDescription();
                    string memCity = member.getMotorcycle().getCity();
                    string memRenterName = member.getMotorcycle().getRenterName();
                    vector<int> memRating = member.getMotorcycle().getRating();
                    vector<string> memComment = member.getMotorcycle().getComment();
                    bool memAvailable = member.getMotorcycle().getAvailable();
                    bool memListed = member.getMotorcycle().getListed();
                    float memRequirementToRent = member.getMotorcycle().getRequirementToRent();
                    double memRequiredCredit = member.getMotorcycle().getRequiredCredit();
                    string memperiodStart = member.getMotorcycle().getperiodStart();
                    string memperiodEnd = member.getMotorcycle().getperiodEnd();

                    existMember.setCredit(member.getCredit());
                    existMember.setMotorcycle(Motorcycle(memModel, memColor, memEngineSize, memTransmission, memYearMade, memDescription, memCity, memRenterName, memRating, memComment, memAvailable, 1, memRequirementToRent, memRequiredCredit, memperiodStart, memperiodEnd));
                } else {
                    string memModel = member.getMotorcycle().getModel();
                    string memColor = member.getMotorcycle().getColor();
                    int memEngineSize = member.getMotorcycle().getengineSize();
                    string memTransmission = member.getMotorcycle().getTransmission();
                    int memYearMade = member.getMotorcycle().getYearMade();
                    string memDescription = member.getMotorcycle().getDescription();
                    string memCity = member.getMotorcycle().getCity();
                    string memRenterName = member.getMotorcycle().getRenterName();
                    vector<int> memRating = member.getMotorcycle().getRating();
                    vector<string> memComment = member.getMotorcycle().getComment();
                    bool memAvailable = member.getMotorcycle().getAvailable();
                    bool memListed = member.getMotorcycle().getListed();

                    existMember.setCredit(member.getCredit());
                    existMember.setMotorcycle(Motorcycle(memModel, memColor, memEngineSize, memTransmission, memYearMade, memDescription, memCity, memRenterName, memRating, memComment, memAvailable, 0));
                }
            }
            if (existMember.getUsername() == usernameRenter) {
                existMember.setCredit(existMember.getCredit() - requiredCreditOwner);
            }
            saveData(existMember);
        }
    }
    return true;
}

vector<Member> System::getMemberList() {
    return memberList;
}

vector<Motorcycle> System::getMotorcycleList() {
    return motorcycleList;
}

void System::pushMemberList(Member member) {
    memberList.push_back(member);
}

void System::setMemberList(vector<Member> memberList) {
    this->memberList = memberList;
}

void System::pushMotorcycleList(Motorcycle motorcycle) {
    motorcycleList.push_back(motorcycle);
}