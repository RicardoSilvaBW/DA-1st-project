//
// Created by ricar on 3/7/2026.
//

/**
 * @file ReviewAssignment.h
 * @brief Header for the ReviewAssignment class.
 */

#ifndef DA_1ST_PROJECT_REVIEWASSIGNMENT_H
#define DA_1ST_PROJECT_REVIEWASSIGNMENT_H


/**
 * @class ReviewAssignment
 * @brief Class representing a single review assignment.
 */
class ReviewAssignment {
private:
    int submissionId;   ///< Submission ID.
    int reviewerId;     ///< Reviewer ID.
    int submissionDomain; ///< Submission domain ID.
    int reviewerDomain; ///< Reviewer domain ID.

public:
    /**
     * @brief Constructor for ReviewAssignment.
     */
    ReviewAssignment(int submissionId, int reviewerId, int submissionDomain, int reviewerDomain);

    /**
     * @brief Getter for Submission ID.
     */
    int getSubmissionId() const;

    /**
     * @brief Getter for Reviewer ID.
     */
    int getReviewerId() const;

    /**
     * @brief Getter for Submission Domain.
     */
    int getSubmissionDomain() const;

    /**
     * @brief Getter for Reviewer Domain.
     */
    int getReviewerDomain() const;
};


#endif //DA_1ST_PROJECT_REVIEWASSIGNMENT_H