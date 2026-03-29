//
// Created by ricar on 3/7/2026.
//

/**
 * @file MissingReview.h
 * @brief Header for the MissingReview class.
 */

#ifndef DA_1ST_PROJECT_MISSINGREVIEW_H
#define DA_1ST_PROJECT_MISSINGREVIEW_H

/**
 * @class MissingReview
 * @brief Class representing a submission that is missing reviews.
 */
class MissingReview {
private:
    int submissionId; ///< Submission ID.
    int domain;       ///< Domain ID.
    int missingCount; ///< Number of reviews missing.

public:
    /**
     * @brief Constructor for MissingReview.
     */
    MissingReview(int submissionId, int domain, int missingCount);

    /**
     * @brief Getter for Submission ID.
     */
    int getSubmissionId() const;

    /**
     * @brief Getter for Domain.
     */
    int getDomain() const;

    /**
     * @brief Getter for Missing Count.
     */
    int getMissingCount() const;
};


#endif //DA_1ST_PROJECT_MISSINGREVIEW_H