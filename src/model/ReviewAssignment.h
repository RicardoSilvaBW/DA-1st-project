//
// Created by ricar on 3/7/2026.
//

#ifndef DA_1ST_PROJECT_REVIEWASSIGNMENT_H
#define DA_1ST_PROJECT_REVIEWASSIGNMENT_H


class ReviewAssignment {
private:
    int submissionId;
    int reviewerId;
    int submissionDomain;
    int reviewerDomain;

public:

    ReviewAssignment(int submissionId, int reviewerId, int submissionDomain, int reviewerDomain);

    int getSubmissionId() const;
    int getReviewerId() const;
    int getSubmissionDomain() const;
    int getReviewerDomain() const;
};


#endif //DA_1ST_PROJECT_REVIEWASSIGNMENT_H