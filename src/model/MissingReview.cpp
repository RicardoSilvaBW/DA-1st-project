//
// Created by ricar on 3/7/2026.
//

/**
 * @file MissingReview.cpp
 * @brief Implementation of the MissingReview class.
 */

#include "MissingReview.h"

/**
 * @brief Constructor for MissingReview.
 * @param submissionId ID of the submission with missing reviews.
 * @param domain Topic domain ID of the submission.
 * @param missingCount Number of reviews still needed.
 */
MissingReview::MissingReview(int submissionId, int domain, int missingCount)
                             : submissionId(submissionId), domain(domain), missingCount(missingCount) {}

/**
 * @brief Getter for Submission ID.
 * @return Submission ID.
 */
int MissingReview::getSubmissionId() const {
    return submissionId;
}

/**
 * @brief Getter for Domain.
 * @return Topic domain ID.
 */
int MissingReview::getDomain() const {
    return domain;
}

/**
 * @brief Getter for Missing Count.
 * @return Number of missing reviews.
 */
int MissingReview::getMissingCount() const {
    return missingCount;
}

