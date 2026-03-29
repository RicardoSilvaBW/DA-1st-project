//
// Created by ricar on 3/7/2026.
//

/**
 * @file Reviewer.h
 * @brief Header for the Reviewer class.
 */

#ifndef DA_1ST_PROJECT_REVIEWER_H
#define DA_1ST_PROJECT_REVIEWER_H

#include <string>

/**
 * @class Reviewer
 * @brief Class representing a scientific reviewer.
 */
class Reviewer {
private:
    int id;                 ///< Reviewer unique identifier.
    std::string name;       ///< Name of the reviewer.
    std::string email;      ///< Contact email.
    int primaryExpertise;   ///< Primary expertise topic ID.
    int secondaryExpertise; ///< Secondary expertise topic ID (optional).

public:
    /**
     * @brief Constructor for Reviewer.
     */
    Reviewer(int id, std::string name, std::string email, int primaryExpertise, int secondaryExpertise);

    /**
     * @brief Getter for ID.
     */
    int getId() const;

    /**
     * @brief Getter for Name.
     */
    std::string getName() const;

    /**
     * @brief Getter for Email.
     */
    std::string getEmail() const;

    /**
     * @brief Getter for Primary Expertise.
     */
    int getPrimaryExpertise() const;

    /**
     * @brief Getter for Secondary Expertise.
     */
    int getSecondaryExpertise() const;
};


#endif //DA_1ST_PROJECT_REVIEWER_H