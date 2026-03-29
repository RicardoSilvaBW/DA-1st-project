//
// Created by ricar on 3/7/2026.
//

/**
 * @file Submission.h
 * @brief Header for the Submission class.
 */

#ifndef DA_1ST_PROJECT_SUBMISSION_H
#define DA_1ST_PROJECT_SUBMISSION_H

#include <string>

/**
 * @class Submission
 * @brief Class representing a scientific paper submission.
 */
class Submission {
private:
    int id;                 ///< Submission unique identifier.
    std::string title;      ///< Title of the paper.
    std::string authors;    ///< Authors of the paper.
    std::string email;      ///< Contact email.
    int primaryTopic;       ///< Primary topic ID.
    int secondaryTopic;     ///< Secondary topic ID (optional).

public:
    /**
     * @brief Constructor for Submission.
     */
    Submission(int id, std::string name, std::string authors, std::string email, int primaryTopic, int secondaryTopic);

    /**
     * @brief Getter for ID.
     */
    int getId() const;

    /**
     * @brief Getter for Title.
     */
    std::string getTitle() const;

    /**
     * @brief Getter for Authors.
     */
    std::string getAuthors() const;

    /**
     * @brief Getter for Email.
     */
    std::string getEmail() const;

    /**
     * @brief Getter for Primary Topic.
     */
    int getPrimaryTopic() const;

    /**
     * @brief Getter for Secondary Topic.
     */
    int getSecondaryTopic() const;
};

#endif //DA_1ST_PROJECT_SUBMISSION_H