//
// Created by ricar on 3/7/2026.
//

#include "MissingReview.h"

MissingReview::MissingReview(int submissionId, int domain, int missingCount)
                             : submissionId(submissionId), domain(domain), missingCount(missingCount) {}

int MissingReview::getSubmissionId() const {
    return submissionId;
}

int MissingReview::getDomain() const {
    return domain;
}

int MissingReview::getMissingCount() const {
    return missingCount;
}

