//
// Created by ricar on 3/7/2026.
//

/**
 * @file ReviewAssignment.cpp
 * @brief Implementation of the ReviewAssignment class.
 */

#include "ReviewAssignment.h"

/**
 * @brief Constructor for ReviewAssignment.
 * @param submissionId ID of the submission.
 * @param reviewerId ID of the assigned reviewer.
 * @param submissionDomain Matching domain from the submission.
 * @param reviewerDomain Matching expertise domain from the reviewer.
 */
ReviewAssignment::ReviewAssignment(int submissionId, int reviewerId, int submissionDomain, int reviewerDomain)
                                    : submissionId(submissionId), reviewerId(reviewerId), submissionDomain(submissionDomain), reviewerDomain(reviewerDomain) {}

/**
 * @brief Getter for Submission ID.
 * @return Submission ID.
 */
int ReviewAssignment::getSubmissionId() const {
    return submissionId;
}

/**
 * @brief Getter for Reviewer ID.
 * @return Reviewer ID.
 */
int ReviewAssignment::getReviewerId() const {
    return reviewerId;
}

/**
 * @brief Getter for Submission Domain.
 * @return The domain ID from the submission that matched.
 */
int ReviewAssignment::getSubmissionDomain() const {
    return submissionDomain;
}

/**
 * @brief Getter for Reviewer Domain.
 * @return The expertise domain ID from the reviewer that matched.
 */
int ReviewAssignment::getReviewerDomain() const {
    return reviewerDomain;
}