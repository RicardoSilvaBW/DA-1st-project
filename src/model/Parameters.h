//
// Created by ricar on 3/7/2026.
//

/**
 * @file Parameters.h
 * @brief Struct to hold conference parameters.
 */

#ifndef DA_1ST_PROJECT_PARAMETERS_H
#define DA_1ST_PROJECT_PARAMETERS_H

/**
 * @brief Struct containing global conference parameters.
 */
struct Parameters {
    int minReviewsPerSubmission = 0;    ///< Minimum reviews each submission must receive.
    int maxReviewsPerReviewer = 0;      ///< Maximum reviews each reviewer can perform.
    int primaryReviewerExpertise = 0;   ///< Weight or flag for primary expertise.
    int secondaryReviewerExpertise = 0; ///< Weight or flag for secondary expertise.
    int primarySubmissionDomain = 0;    ///< Weight or flag for primary submission domain.
    int secondarySubmissionDomain = 0;  ///< Weight or flag for secondary submission domain.
};

#endif //DA_1ST_PROJECT_PARAMETERS_H