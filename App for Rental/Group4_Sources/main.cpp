#include <iostream>
#include <vector>
#include "motorcycle.h"
#include "member.h"
#include "system.h"
#include "admin.h"
#include "request.h"

int main() {

    System system;
    vector<Member> memberList;
    vector<string> requestsMemberName; 
    {
        string line;
        std::ifstream myfile("requests.txt");
        if (myfile.is_open()) {
            while (getline(myfile, line)) {
                requestsMemberName.push_back(line);
            }
            myfile.close();
        }
    }
    if (!system.fetchData()) {
        cout << "Failed to get data from file";
        return -1;
    }
    for (Member m : system.getMemberList()) {
        memberList.push_back(m);
    }
    // for (int i = 0; i < (int)memberList.size(); i++) {
    //     memberList[i].request.requests = requestsMemberName[i];
    // }

    while (true) {
        cout << "EEET2482/COSC2082 GROUP ASSIGNMENT\n"
                "MOTORBIKE RENTAL APPLICATION\n\n"
                "Instructor: Dr. Ling Huo Chong\n"
                "Group: Group No.4\n"
                "s3938331, Yoo Christina\n"
                "s3978719, Huynh Bao Cuong\n"
                "s3978719, Nguyen Duy Bach\n"
                "s3978801, Nguyen Quoc Bao\n";
        cout << "Use the app as 1. Guest    2. Member   3. Admin\n\n";
        cout << "Enter your choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            cout << "\n\n1. Guest" << endl;
            while (1) {
                cout << "Guest Menu: 0. Exit    1. Register    2. View all motorcycles\n";
                cout << "Enter your choice: ";

                string gChoice;
                getline(cin, gChoice);

                if (gChoice == "0") {
                    cout << "\n\n0. Exit" << endl;
                    cout << "Thank you for using our application!" << endl;
                    break;
                } else if (gChoice == "1") {
                    cout << "\n\n1. Register" << endl;
                    Member newMember = Member().registerMember(system.getMemberList());
                    system.pushMemberList(newMember);
                    memberList.push_back(newMember);
                    system.pushMotorcycleList(newMember.getMotorcycle());
                    bool checkNewMember = true;
                    
                    memberMenu:
                    while (1) {
                        cout << "Member Menu: 0. Exit" << endl;
                        cout << "             1. View account information" << endl;
                        cout << "             2. View all motorcycles" << endl;
                        cout << "             3. List or UnList your motorcycle" << endl;
                        cout << "             4. Search for available motorcycle in a city" << endl;
                        cout << "             5. Rent a motorcycle" << endl;
                        cout << "             6. Return rented motorcycle" << endl;
                        cout << "             7. View and accept a request" << endl;
                        cout << "             8. Rate the renter" << endl;
                        cout << "Enter your choice: ";

                        string mChoice;
                        getline(cin, mChoice);

                        if (mChoice == "0") {
                            cout << "\n\n0. Exit" << endl;
                            system.saveAllData(checkNewMember, memberList, newMember);
                            {
                                ofstream myfile;
                                myfile.open("requests.txt");
                                string res = "";

                                for (Member m: memberList) {
                                    myfile << m.request.requests;
                                    myfile << "\n";
                                }

                                myfile.close();
                            }
                            cout << "Thank you for using our application!" << endl;
                            break;
                        } else if (mChoice == "1") {
                            cout << "\n\n1. View account information" << endl;
                            system.showMyInfo(newMember);
                        } else if (mChoice == "2") {
                            cout << "\n\n2. View all motorcycles" << endl;
                            system.showAllMotorcycleDetail(newMember, system.getMotorcycleList());
                        } else if (mChoice == "3") {
                            cout << "\n\n3. List or unList your motorcycle" << endl;
                            newMember = system.listMotorcycleAvailable(newMember, system.getMotorcycleList());
                            cin.ignore(1,'\n');
                        } else if (mChoice == "4") {
                            cout << "\n\n4. Search for all motorcycle in a city" << endl;
                            system.searchAllAvailableMotorcycle(newMember, system.getMotorcycleList());
                        } else if (mChoice == "5") {
                            cout << "\n\n5. Rent a motorcycle" << endl;
                            int index = 0;
                            vector<Motorcycle> motorcycleList = system.getMotorcycleList();
                            vector<Motorcycle> res = {};
                            vector<Member> owners = system.getMemberList();
                            vector<Member> owner = {};
                            int iteration = 0;

                            for (string s: requestsMemberName) {
                                if (s.find(newMember.getUsername()) != -1) {
                                    cout << "You have already made a request or already renting a motorcycle currently!";
                                    goto memberMenu;
                                }
                            }
                            for (Motorcycle m: system.getMotorcycleList()) {
                                    if (!m.getListed() || newMember.getMotorcycle().getDescription() == m.getDescription() || !m.getAvailable() || newMember.getCredit() < m.getRequiredCredit() || newMember.getAverage() < m.getRequirementToRent()) {
                                        iteration++;
                                        continue;
                                    }
                                    cout << "Option "<< iteration << ": " << std::endl;
                                    m.showInfoBasic();
                                    res.push_back(m);
                                    owner.push_back(owners[iteration]);
                                    iteration++;
                                    index++;
                            }
                            if (index == 0) {
                                cout << "There are no motorcycle based on your credit and rating status!" << endl;
                                goto memberMenu;
                            }
                            int choiceIndex = 0;
                            Motorcycle choiceMotorcycle;
                        chooseRentMenu:
                            cout << "Choose a motorcycle to make a request. Enter its number: ";
                            cin >> choiceIndex;
                            if (choiceIndex >= 1 && choiceIndex <= index) {
                                goto chooseRentMenu;
                            }
                            choiceMotorcycle = res[choiceIndex-1];

                            int commentCount = choiceMotorcycle.getComment().size();
                            int ratingCount = choiceMotorcycle.getRating().size();
                            {
                                if (commentCount == 0) {
                                    cout << "No comment yet." << endl;
                                }
                                if (ratingCount == 0) {
                                    cout << "No rating yet." << endl;
                                }
                            }
                            vector<int> ratingChoiceMotorcycle = choiceMotorcycle.getRating();
                            vector<string> commentsChoiceMotorcycle = choiceMotorcycle.getComment();
                            for (int i = 0; i < commentCount; i++) {
                                cout << "Rating: " << ratingChoiceMotorcycle[i] << ", Comment: " << commentsChoiceMotorcycle[i] << endl;
                            }

                            decisionMenu:
                            char answer = ' ';
                            cout << "Would you like to rent this motorcycle? (Y/N): ";
                            cin >> answer;

                            switch (answer) {
                                case 'Y':
                                    for (int i = 0; i < system.getMemberList().size(); i++) {
                                        if (system.getMemberList().at(i).getUsername() == owner[choiceIndex-1].getUsername()) {
                                            memberList.at(i).request.requests += newMember.getUsername() + " ";
                                        };
                                    }
                                    cout << "Rent request is made successfully." << endl;
                                    break;
                                case 'N':
                                    goto chooseRentMenu;
                                default:
                                    goto decisionMenu;
                            }
                        std::cin.ignore(1, '\n');
                        } else if (mChoice == "6") {
                            cout << "\n\n6. Return rented motorcycle" << endl;
                            cout << "You have do not have any motorcycle rented." << endl;
                        } else if (mChoice == "7") {
                            cout << "\n\n7. View and accept a request" << endl;
                            cout << "You do not have any requests yet." << endl;
                        } else if (mChoice == "8") {
                            cout << "\n\n8. Rate the renter" << endl;
                        } else {
                            cout << "\n\nInvalid choice.\n" << endl;
                        }
                    }
                    break;
                } else if (gChoice == "2") {
                    cout << "\n\n2. View all motorcycles" << endl;
                    system.showAllMotorcycleBasic(system.getMotorcycleList());
                } else {
                    cout << "Invalid choice.\n" << endl;
                }
            }
            break;
        }
        else if (choice == "2") {
            cout << "\n\n2. Member" << endl;
            Member loggedInMember = system.loginMember(memberList, system.getMotorcycleList());
            bool checkNewMember = false;
            for (Member m: memberList) {
                if (m.request.requests.find(loggedInMember.getUsername()) != -1 && m.getMotorcycle().getAvailable() == false) {
                    loggedInMember.setAvailable(false);
                    cout << "You are currently renting a motorcycle." << endl;
                }
            }
        memberMenu2:
            while (1) {
                cout << "Member Menu: 0. Exit" << endl;
                cout << "             1. View account information" << endl;
                cout << "             2. View all motorcycles" << endl;
                cout << "             3. List or UnList your motorcycle" << endl;
                cout << "             4. Search for available motorcycle in a city" << endl;
                cout << "             5. Rent a motorcycle" << endl;
                cout << "             6. Return rented motorcycle" << endl;
                if (loggedInMember.getMotorcycle().getRenterName() != "none" && loggedInMember.getMotorcycle().getAvailable() == true) {
                    cout << "                (Rate the renter before accepting a new request. Go to 8.)" << endl;
                }
                cout << "             7. View and accept a request" << endl;
                cout << "             8. Rate the renter" << endl;
                cout << "Enter your choice: ";

                string mChoice;
                getline(cin, mChoice);

                if (mChoice == "0") {
                    cout << "\n\n0. Exit" << endl;
                    system.saveAllData(checkNewMember, memberList, loggedInMember);
                    {
                        ofstream myfile;
                        myfile.open("requests.txt");
                        string res = "";

                        for (Member m: memberList) {
                            myfile << m.request.requests;
                            myfile << "\n";
                        }

                        myfile.close();
                    }
                    cout << "Thank you for using our application!" << endl;
                    break;
                } else if (mChoice == "1") {
                    cout << "\n\n1. View account information" << endl;
                    system.showMyInfo(loggedInMember);
                } else if (mChoice == "2") {
                    cout << "\n\n2. View all motorcycles" << endl;
                    system.showAllMotorcycleDetail(loggedInMember, system.getMotorcycleList());
                } else if (mChoice == "3") {
                    cout << "\n\n3. List or unList your motorcycle" << endl;
                    loggedInMember = system.listMotorcycleAvailable(loggedInMember, system.getMotorcycleList());
                    cin.ignore(1,'\n');
                } else if (mChoice == "4") {
                    cout << "\n\n4. Search for all motorcycle in a city" << endl;
                    system.searchAllAvailableMotorcycle(loggedInMember, system.getMotorcycleList());
                } else if (mChoice == "5") {
                    cout << "\n\n5. Rent a motorcycle" << endl;
                    int index = 0;
                    vector<Motorcycle> motorcycleList = system.getMotorcycleList();
                    vector<Motorcycle> res = {};
                    vector<Member> ownerList = system.getMemberList();
                    vector<Member> owner = {};
                    int iteration = 0;

                    for (string s: requestsMemberName) {
                        if (s.find(loggedInMember.getUsername()) != -1) {
                            cout << "You have already made a request or already renting a motorcycle currently!";
                            goto memberMenu2;
                        }
                    }
                    for (Motorcycle m: system.getMotorcycleList()) {
                            if (!m.getListed() || loggedInMember.getMotorcycle().getDescription() == m.getDescription() || !m.getAvailable() || loggedInMember.getCredit() < m.getRequiredCredit() || loggedInMember.getAverage() < m.getRequirementToRent()) {
                                iteration++;
                                continue;
                            }
                            cout << "Option "<< iteration << ": " << std::endl;
                            m.showInfoBasic();
                            res.push_back(m);
                            owner.push_back(ownerList[iteration]);
                            iteration++;
                            index++;
                    }
                    if (index == 0) {
                        cout << "There are no motorcycle based on your credit and rating status!" << endl;
                        goto memberMenu2;
                    }
                    int choiceIndex = 0;
                    Motorcycle choiceMotorcycle;
                chooseRent:
                    cout << "Choose a motorcycle to make a request. Enter its number: ";
                    cin >> choiceIndex;
                    if (choiceIndex < 1 || choiceIndex > index) {
                        goto chooseRent;
                    }
                    choiceMotorcycle = res[choiceIndex-1];

                    int commentCount = choiceMotorcycle.getComment().size();
                    int ratingCount = choiceMotorcycle.getRating().size();
                    {
                        if (commentCount == 0) {
                            cout << "No comment yet." << endl;
                        }
                        if (ratingCount == 0) {
                            cout << "No rating yet." << endl;
                        }
                    }
                    vector<int> ratingChoiseMotorcycle = choiceMotorcycle.getRating();
                    vector<string> commentsChoiseMotorcycle = choiceMotorcycle.getComment();
                    for (int i = 0; i < commentCount; i++) {
                        cout << "Rating: " << ratingChoiseMotorcycle[i] << ", Comment: " << commentsChoiseMotorcycle[i] << endl;
                    }
                decision:
                    char answer = ' ';
                    cout << "Would you like to rent this motorcycle? ('Y'/'N'): ";
                    cin >> answer;

                    switch (answer) {
                        case 'Y':
                            for (int i = 0; i<(int)system.getMemberList().size(); i++) {
                                if (system.getMemberList().at(i).getUsername() == owner[choiceIndex-1].getUsername()) {
                                    memberList.at(i).request.requests += loggedInMember.getUsername() + " ";
                                }
                            }
                            cout << "Rent request is made successfully!" << endl;
                            break;
                        case 'N':
                            goto chooseRent;
                        default:
                            goto decision;
                    }
                    std::cin.ignore(1, '\n');
                } else if (mChoice == "6") {
                    cout << "\n\n6. Return rented motorcycle" << endl;
                    loggedInMember.acceptRequest(memberList);
                    system.requiredCreditOwner = loggedInMember.getMotorcycle().getRequiredCredit();
                    system.setMemberList(memberList);
                    loggedInMember.setCredit(loggedInMember.getCredit() + system.requiredCreditOwner);

                    for (Member m : memberList) {
                        if (loggedInMember.getUsername() == m.getUsername()) {
                            system.usernameRenter = m.request.requests;
                            break;
                        }
                    }
                } else if (mChoice == "7") {
                    cout << "\n\n7. View and accept a request" << endl;
                    for (Member m : memberList) {
                        if (m.request.requests.find(loggedInMember.getUsername()) != -1 && !m.getMotorcycle().getAvailable()) {
                            system.usernameOwner = m.getUsername();
                        }
                    }
                    if (system.usernameOwner == "") {
                        cout << "You have not let any motorcycle to be rented yet." << endl;
                        goto memberMenu2;
                    }
                    for (Member &owner : memberList) {
                        if (owner.getUsername() == system.usernameOwner) {
                            owner.request.requests = "";
                            owner.toggleMotorcycleAvailable();
                            loggedInMember.setAvailable(true);
                            loggedInMember.setOwnerName("none");
                            cout << owner.getMotorcycle().getAvailable() << "\n";
                            cout << "" << endl;
                    
                            loggedInMember.checkOut(owner);
                            system.setMemberList(memberList);
                            goto memberMenu2;
                        }
                    }
                } else if (mChoice == "8") {
                    cout << "\n\n8. Rate the renter" << endl;
                    if (loggedInMember.getMotorcycle().getRenterName() == "none" && loggedInMember.getMotorcycle().getAvailable() == true)
                    {
                        cout << "There is no renter that need to be rated\n";
                        goto memberMenu2;
                    }

                    for (Member &renter : memberList)
                    {
                        if (renter.getUsername() == loggedInMember.getMotorcycle().getRenterName())
                        {
                            cout << renter.getUsername() << " rented your motorcycle" << endl;
                            loggedInMember.rateRenter(renter);
                            loggedInMember.setMotorcycleRenter("none");
                        }
                    }
                } else {
                    cout << "\n\nInvalid choice.\n" << endl;
                }
            }
            break;
        } else if (choice == "3") {
            cout << "\n\n3. Admin" << endl;
            system.loginAdmin();

            while (1) {
                cout << "Admin Menu: 0. Exit" << endl;
                cout << "            1. View all user and motorcycle information" << endl;
                cout << "Enter your choice: ";

                string aChoice;
                getline(cin, aChoice);

                if (aChoice == "0") {
                    cout << "\n\n0. Exit" << endl;
                    cout << "Thank you for using our application!" << endl;
                    break;
                } else if (aChoice == "1") {
                    cout << "\n\n1. View all user and motorcycle information" << endl;
                    system.showAllInfo(system.getMemberList());
                } else {
                    cout << "\n\nInvalid choice.\n" << endl;
                }
            }
            break;
        } else {
            cout << "\n\nInvalid choice.\n" << endl;
        }
    }
    return 0;
}