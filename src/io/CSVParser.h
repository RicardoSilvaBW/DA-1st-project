//
// Created by andresantos on 09/03/26.
//

#ifndef DA_1ST_PROJECT_CSVPARSER_H
#define DA_1ST_PROJECT_CSVPARSER_H

#include <set>
#include <string>
#include <vector>
//The following includes are here because we need to store the data we parse. I think it makes sense to do it like that, we can change it later on.
#include "../model/Submission.h"
#include "../model/Reviewer.h"
#include "../model/Parameters.h"
#include "../model/ControlSettings.h"

class CSVParser {
    public:
    CSVParser();

    // Bool flag to check if the file parsing was successful, it returns false if it has insconsistent values, the project descrption implies we do this
    bool parseFile(const std::string& filename);

    // Cleans up internal state for a new parse
    void clear();

    // These functions allow the algorithms and menu to access the loaded data
    const std::vector<Submission>& getSubmissions() const;
    const std::vector<Reviewer>& getReviewers() const;
    const Parameters& getParameters() const;
    const ControlSettings& getControlSettings() const;

    private:
    // Stores the data we parse
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;
    Parameters parameters;
    ControlSettings controlSettings;

    // Track IDs to detect duplicates
    std::set<int> submissionIds;
    std::set<int> reviewerIds;

    // Internal error tracking
    bool hasError = false;

    // These functions parses individual lines for each section of the csv
    void parseSubmissionLine(const std::string& line);
    void parseReviewerLine(const std::string& line);
    void parseParameterLine(const std::string& line);
    void parseControlLine(const std::string& line);

    // Function to trim and clean spaces and quotes from the csv
    std::string trim(const std::string& str) const;
    std::vector<std::string> splitCSVLine(const std::string& line) const;
    std::string stripQuotes(const std::string& str) const;
};

#endif //DA_1ST_PROJECT_CSVPARSER_H