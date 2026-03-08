//
// Created by ricar on 3/7/2026.
//

#ifndef DA_1ST_PROJECT_REVIEWER_H
#define DA_1ST_PROJECT_REVIEWER_H

#include <string>

class Reviewer {
private:
    int id;
    std::string name;
    std::string email;
    int primaryExpertise;
    int secondaryExpertise;

public:

    //Constructor
    Reviewer(int id, std::string name, std::string email, int primaryExpertise, int secondaryExpertise);

    //Getters
    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    int getPrimaryExpertise() const;
    int getSecondaryExpertise() const;

};


#endif //DA_1ST_PROJECT_REVIEWER_H