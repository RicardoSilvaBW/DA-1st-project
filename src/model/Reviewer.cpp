//
// Created by ricar on 3/7/2026.
//

#include "Reviewer.h"

Reviewer::Reviewer(int id, std::string name, std::string email, int primaryExpertise, int secondaryExpertise)
                    : id(id), name(name), email(email), primaryExpertise(primaryExpertise), secondaryExpertise(secondaryExpertise) {}

int Reviewer::getId() const {
    return id;
}

std::string Reviewer::getName() const {
    return name;
}

std::string Reviewer::getEmail() const {
    return email;
}

int Reviewer::getPrimaryExpertise() const {
    return primaryExpertise;
}

int Reviewer::getSecondaryExpertise() const {
    return secondaryExpertise;
}