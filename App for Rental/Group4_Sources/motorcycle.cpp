

#include <string>
using namespace std;
#include <vector>
#include <regex>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "motorcycle.h"


Motorcycle::Motorcycle( // not listed
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
) : 
    model(model), 
    color(color), 
    engineSize(engineSize), 
    transmission(transmission),
    yearMade(yearMade),
    description(description),
    city(city),
    renterName(renterName),
    rating(rating),
    comment(comment),
    available(available),
    listed(listed) {}

Motorcycle::Motorcycle( // listed
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
) : 
    model(model), 
    color(color), 
    engineSize(engineSize), 
    transmission(transmission),
    yearMade(yearMade),
    description(description),
    city(city),
    renterName(renterName),
    rating(rating),
    comment(comment),
    available(available),
    listed(listed),
    requirementToRent(requirementToRent),
    requiredCredit(requiredCredit),
    periodStart(periodStart),
    periodEnd(periodEnd) {}

string Motorcycle::getModel()
{
    return model;
}

string Motorcycle::getColor()
{
    return color;
}

int Motorcycle::getengineSize()
{
    return engineSize;
}

string Motorcycle::getTransmission()
{
    return transmission;
}

int Motorcycle::getYearMade()
{
    return yearMade;
}

string Motorcycle::getDescription(){
    return description;
}

string Motorcycle::getCity()
{
    return city;
}

string Motorcycle::getRenterName() 
{
    return renterName;
}

vector<int> Motorcycle::getRating() 
{
    return rating;
}

float Motorcycle::getAverage() {
    if (rating.size() == 0) {
        return 0;
    }
    int total;
    for (int r: rating) {
        total += r;
    }
    return total/this->rating.size();
}

vector<string> Motorcycle::getComment()
{
    return comment;
}

bool Motorcycle::getAvailable() 
{
    return available;
}

bool Motorcycle::getListed()
{
    return listed;
}

float Motorcycle::getRequirementToRent()
{
    return requirementToRent;
}

double Motorcycle::getRequiredCredit() {
    return requiredCredit;
}

string Motorcycle::getperiodStart()
{
    return periodStart;
}

string Motorcycle::getperiodEnd()
{
    return periodEnd;
}

// string Motorcycle::getRentStart()
// {
//     return rentStart;
// }

// string Motorcycle::getRentEnd()
// {
//     return rentEnd;
// }

void Motorcycle::setModel(string model)
{
    this->model = model;
}

void Motorcycle::setColor(string color)
{
    this->color = color;
}

void Motorcycle::setEngineSize(int engineSize)
{
    this->engineSize = engineSize;
}

void Motorcycle::setTransmission(string transmission)
{
    this->transmission = transmission;
}

void Motorcycle::setYearMade(int yearMade)
{
    this->yearMade = yearMade;
}

void Motorcycle::setDescription(string description) {
    this->description = description;
}

void Motorcycle::setCity(string city)
{
    this->city = city;
}

void Motorcycle::setRenterName(string renterName) 
{
    this->renterName = renterName;
}

void Motorcycle::setRating(vector<int> rating)
{
    this->rating = rating;
}

void Motorcycle::setComment(vector<string> comment)
{
    this->comment = comment;
}

void Motorcycle::setAvailable(bool available) {
    this->available = available;
}

void Motorcycle::setListed(bool listed) {
    this->listed = listed;
}

void Motorcycle::setperiodStart(string periodStart)
{
    this->periodStart = periodStart;
}

void Motorcycle::setperiodEnd(string periodEnd)
{
    this->periodEnd = periodEnd;
}

// void Motorcycle::setRentStart(string start)
// {
//     this->rentStart = start;
// }

// void Motorcycle::setRentEnd(string end)
// {
//     this->rentEnd = end;
// }

void Motorcycle::setRequirementToRent(int num)
{
    this->requirementToRent = num;
}

void Motorcycle::setRequiredCredit(double credit)
{
    this->requiredCredit = credit;
}

bool Motorcycle::checkEngineSize(int engineSizeRead)
{
    if (engineSizeRead > 0)
    {
        return true;
    }
    else
        return false;
}

bool Motorcycle::checkYear(int yearRead)
{
    if (yearRead < 1885)
    {
        return false;
    }
    else
        return true;
}

bool Motorcycle::checkRating(float input)
{
    if (input > 5 || input < 0)
    {
        return false;
    }
    else
        return true;
}

bool Motorcycle::checkDateType(string date)
{
    if (regex_match(date, regex("^(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](18|19||20)[0-9][0-9]$")))
    {
        return true;
    }
    else
    {
        return false;
    }
}


void Motorcycle::showInfoBasic()
{
    cout << "Model: " << this->model << endl;
    cout << "Color: " << this->color << endl;
    cout << "Engine size: " << this->engineSize << endl;
    cout << "Year:" << this->yearMade << endl;
    cout << "Description: " << this->description << endl;
}

void Motorcycle::showInfoDetailed()
{
    cout << "Model: " << this->model << endl;
    cout << "Color: " << this->color << endl;
    cout << "Engine size: " << this->engineSize << endl;
    cout << "Year:" << this->yearMade << endl;
    cout << "Description: " << this->description << endl;
    cout << "Rating: " ;
    for(int i = 0; i < rating.size(); i++){
        std::cout << rating[i] << " ";
    }
    std::cout << std::endl;
    cout << "Requirement: " << this->requirementToRent << endl;
    cout << "City: " << this->city << endl;
    cout << "Credit cost: " << this->requiredCredit << endl;
}

void Motorcycle::setPeriodRent()
{
    std::string temp; // this will be use as a temporary string to store date input
    while (1)
    { // Keep asking until user enter valid start date
        std::cout << "please enter the date rent: ";
        std::cin >> temp;
        if (checkDateType(temp) == true)
        {
            this->periodStart = temp;
            std::cin.ignore(1, '\n');
            temp.clear();
            break;
        }
        else if (checkDateType(temp) == false)
        {
            std::cout << "Invalid date!\n";
            temp.clear();
        }
    }

    while (1)
    { // Keep asking until user enter valid end date
        std::cout << "please enter the return date: ";
        std::cin >> temp;
        if (checkDateType(temp) == true)
        {
            this->periodEnd = temp;
            std::cin.ignore(1, '\n');
        }
        else if (checkDateType(temp) == false)
        {
            std::cout << "Invalid date!\n";
        }
    }
}

// in progress

int Motorcycle::showComment()
{
    std::fstream commentfile;
    commentfile.open("MotorComments.txt", std::ios::in);

    // if cant open file, return error
    if (!commentfile)
    {
        std::cerr << "Fail to create/open file \n";
        return -1;
    }
    else
    {
        std::cout << "Opened file successful \n";
    }

    // getline then create sub string start at pos 0 with 4 letter
    // if that sub string == model
    std::string searchModel;
    std::string temp;
    int modelNameLenght = 0;
    int pos = model.length() + 1; // position which the comments start, + 1 because skipping the ','

    while (std::getline(commentfile, searchModel, '\n'))
    {
        // check if the sub string (first string in the comment line)
        if (searchModel.substr(0, model.length()) == model)
        {
            int commentLenght = 0;
            // If match model
            // For loop through the searchModel string (which contain the whole line)
            // If current position is not ',' then count the comment lenght
            // If current position is ',' meaning the comment stop, then assign the comments to temp
            // Then push that temp to the comments vector
            // Then clear the string temp incase there's more comments
            for (int i = pos; i < searchModel.length(); i++)
            {
                if (searchModel[i] == ',')
                {
                    temp.assign(searchModel, pos, commentLenght);
                    comment.push_back(temp);
                    temp.clear();
                    pos += commentLenght + 1;
                    commentLenght = 0;
                }
                else
                    commentLenght++;
            }
        }
    }

    // function show all comments
    std::cout << "These are the comments for " << model << " : \n";
    for (int i = 0; i < comment.size(); i++)
    {
        std::cout << comment[i] << std::endl;
    }
    return 0;
}
int Motorcycle::addComment(string commentToAdd)
{
    std::fstream commentfile("MotorComments.txt", std::ios::in | std::ios::out);

    // if cant open file, return error
    if (!commentfile)
    {
        std::cerr << "Fail to create/open file \n";
        return -1;
    }
    else
    {
        std::cout << "Opened file successful \n";
    }
    std::string temp;
    std::vector<std::string> lines;

    while (std::getline(commentfile, temp))
    {

        if (temp.substr(0, model.length()) == model)
        {
            temp += commentToAdd + ",";
        }

        lines.push_back(temp);
    }
    commentfile.close();

    commentfile.open("MotorComments.txt", std::ios::out);
    for (const auto &line : lines)
    {
        commentfile << line << "\n";
    }
    commentfile.close();
    cout << "Your comment have been recorded";

    return 0;
}





void Motorcycle::toggleAvailable() {
    if (available == true) {
        available = false;
    } else {
        available = true;
    }
}

void Motorcycle::toggleListed() {
    if (listed == true) {
        listed = false;
    } else {
        listed = true;
    }
}