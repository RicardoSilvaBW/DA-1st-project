//
// Created by ricar on 3/7/2026.
//

/**
 * @file Submission.cpp
 * @brief Implementation of the Submission class.
 */

#include "Submission.h"

/**
 * @brief Constructor for Submission.
 * @param id Submission unique ID.
 * @param title Title of the submission.
 * @param authors Authors of the submission.
 * @param email Contact email.
 * @param primaryTopic Primary topic ID.
 * @param secondaryTopic Secondary topic ID (optional, 0 if none).
 */
Submission::Submission(int id, std::string title, std::string authors,
                        std::string email, int primaryTopic, int secondaryTopic)
                            : id(id), title(title), authors(authors), email(email),
                                primaryTopic(primaryTopic), secondaryTopic(secondaryTopic) {}

/**
 * @brief Getter for ID.
 * @return Submission ID.
 */
int Submission::getId() const {
    return id;
}

/**
 * @brief Getter for Title.
 * @return Submission title.
 */
std::string Submission::getTitle() const {
    return title;
}

/**
 * @brief Getter for Authors.
 * @return Submission authors.
 */
std::string Submission::getAuthors() const {
    return authors;
}

/**
 * @brief Getter for Email.
 * @return Contact email.
 */
std::string Submission::getEmail() const {
    return email;
}

/**
 * @brief Getter for Primary Topic.
 * @return Primary topic ID.
 */
int Submission::getPrimaryTopic() const {
    return primaryTopic;
}

/**
 * @brief Getter for Secondary Topic.
 * @return Secondary topic ID.
 */
int Submission::getSecondaryTopic() const {
    return secondaryTopic;
}