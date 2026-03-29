//
// Created by ricar on 3/7/2026.
//

/**
 * @file Reviewer.cpp
 * @brief Implementation of the Reviewer class.
 */

#include "Reviewer.h"

/**
 * @brief Constructor for Reviewer.
 * @param id Reviewer unique ID.
 * @param name Name of the reviewer.
 * @param email Contact email.
 * @param primaryExpertise Primary expertise domain ID.
 * @param secondaryExpertise Secondary expertise domain ID (optional, 0 if none).
 */
Reviewer::Reviewer(int id, std::string name, std::string email, int primaryExpertise, int secondaryExpertise)
                    : id(id), name(name), email(email), primaryExpertise(primaryExpertise), secondaryExpertise(secondaryExpertise) {}

/**
 * @brief Getter for ID.
 * @return Reviewer ID.
 */
int Reviewer::getId() const {
    return id;
}

/**
 * @brief Getter for Name.
 * @return Reviewer name.
 */
std::string Reviewer::getName() const {
    return name;
}

/**
 * @brief Getter for Email.
 * @return Contact email.
 */
std::string Reviewer::getEmail() const {
    return email;
}

/**
 * @brief Getter for Primary Expertise.
 * @return Primary expertise domain ID.
 */
int Reviewer::getPrimaryExpertise() const {
    return primaryExpertise;
}

/**
 * @brief Getter for Secondary Expertise.
 * @return Secondary expertise domain ID.
 */
int Reviewer::getSecondaryExpertise() const {
    return secondaryExpertise;
}