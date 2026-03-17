//
// Created by ricar on 3/7/2026.
//

#include "Submission.h"

Submission::Submission(int id, std::string title, std::string authors,
                        std::string email, int primaryTopic, int secondaryTopic)
                            : id(id), title(title), authors(authors), email(email),
                                primaryTopic(primaryTopic), secondaryTopic(secondaryTopic) {}

int Submission::getId() const {
    return id;
}

std::string Submission::getTitle() const {
    return title;
}

std::string Submission::getAuthors() const {
    return authors;
}

std::string Submission::getEmail() const {
    return email;
}

int Submission::getPrimaryTopic() const {
    return primaryTopic;
}

int Submission::getSecondaryTopic() const {
    return secondaryTopic;
}