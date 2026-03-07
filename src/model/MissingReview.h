//
// Created by ricar on 3/7/2026.
//

#ifndef DA_1ST_PROJECT_MISSINGREVIEW_H
#define DA_1ST_PROJECT_MISSINGREVIEW_H

class MissingReview {
private:
    int submissionId;
    int domain;
    int missingCount;

public:

    MissingReview(int submissionId, int domain, int missingCount);

    int getSubmissionId() const;
    int getDomain() const;
    int getMissingCount() const;
};


#endif //DA_1ST_PROJECT_MISSINGREVIEW_H