//
// Created by ricar on 3/7/2026.
//

#ifndef DA_1ST_PROJECT_SUBMISSION_H
#define DA_1ST_PROJECT_SUBMISSION_H

#include <string>

class Submission {
private:
    int id;
    std::string title;
    std::string authors;
    std::string email;
    int primaryTopic;
    int secondaryTopic;

public:

    //Constructor
    Submission(int id, std::string name, std::string authors, std::string email, int primaryTopic, int secondaryTopic);

    //Gettters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthors() const;
    std::string getEmail() const;
    int getPrimaryTopic() const;
    int getSecondaryTopic() const;
};

#endif //DA_1ST_PROJECT_SUBMISSION_H