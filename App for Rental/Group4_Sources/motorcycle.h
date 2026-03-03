
#ifndef MOTOCYCLE_H
#define MOTOCYCLE_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <vector>
#include <regex>


class Motorcycle
{
private:
    string model;
    string color;
    int engineSize; // > 0
    string transmission;
    int yearMade; // > 0
    string description;
    string city;
    
    string renterName;

    std::vector<int> rating; // 0 - 5
    std::vector<std::string> comment;
    bool available = true;
    bool listed = false;

    float requirementToRent; // 0 - 5
    double requiredCredit;

    string periodStart; // need regex (optional)
    string periodEnd;

    // string rentStart;
    // string rentEnd;

public:
    // constructor
    Motorcycle(  // not listed
        string model,
        string color,
        int engineSize,
        string transmission,
        int yearMade,
        string description,
        string city,
        string renterName,
        vector<int> rating,
        vector<string> comment,
        bool available,
        bool listed
    );

    Motorcycle( // listed
        string model,
        string color,
        int engineSize,
        string transmission,
        int yearMade,
        string description,
        string city,
        string renterName,
        vector<int> rating,
        vector<string> comment,
        bool available,
        bool listed,
        float requirementToRent,
        double requiredCredit,
        string periodStart,
        string periodEnd
    );

    Motorcycle() {};

    string getModel();

    string getColor();

    int getengineSize();

    string getTransmission();

    int getYearMade();

    string getDescription();

    string getCity();

    string getRenterName();  

    vector<int> getRating();

    float getAverage();

    vector<string> getComment();

    bool getAvailable();

    bool getListed();

    float getRequirementToRent();

    double getRequiredCredit();

    string getperiodStart();

    string getperiodEnd();

    // string getRentStart();
    // string getRentEnd();
    
    // set rating for motocycle
    void setModel(string model);

    void setColor(string color);

    void setEngineSize(int engineSize);

    void setTransmission(string transmission);

    void setYearMade(int yearMade);

    void setDescription(string description);

    void setCity(string city);

    void setRenterName(string renterName) ;

    void setRating(vector<int> rating);

    void setComment(vector<string> comment);

    void setAvailable(bool available);

    void setListed(bool listed);

    void setRequirementToRent(int num); // implemented - delete after check

    void setRequiredCredit(double num); // implemented - delete after check

    void setperiodStart(string periodStart);

    void setperiodEnd(string periodEnd);

    // void setRentStart(string rentStart);

    // void setRentEnd(string rentEnd);

    bool checkEngineSize(int engineSizeRead);

    // check if year is valid
    bool checkYear(int yearRead);

    // this can be use to check both rating and requirementToRent
    // because both are between 0 - 5
    bool checkRating(float input);

    // check if date is valid
    // https://www.regular-expressions.info/dates.html#:~:text=To%20match%20a%20date%20in,%5D)%5B%2D%20%2F.%5D
    bool checkDateType(string date);

    void showInfoBasic();

    void showInfoDetailed();

    void setPeriodRent();

    int addComment(std::string temp); // not really sure about this (record in vector or file)

    int showComment(); // temp is the model which user want to see comments/add


    void toggleAvailable();

    void toggleListed();
};

#endif




