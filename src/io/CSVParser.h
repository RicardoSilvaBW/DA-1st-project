//
// Created by andresantos on 09/03/26.
//

/**
 * @file CSVParser.h
 * @brief Header for the CSVParser class.
 */

#ifndef DA_1ST_PROJECT_CSVPARSER_H
#define DA_1ST_PROJECT_CSVPARSER_H

#include <set>
#include <string>
#include <vector>

#include "../model/Submission.h"
#include "../model/Reviewer.h"
#include "../model/Parameters.h"
#include "../model/ControlSettings.h"

/**
 * @brief CSV parser for conference data files.
 * 
 * Task 1.2: Read and Parse the Input Data.
 */
class CSVParser {
    public:
    CSVParser();

    /**
     * @brief Parses a CSV file and loads data into internal structures.
     * @param filename Path to the CSV file.
     * @return true if parsing was successful and data is consistent, false otherwise.
     * @complexity O(N) where N is the number of characters in the file.
     */
    bool parseFile(const std::string& filename);

    /**
     * @brief Cleans up internal state for a new parse.
     */
    void clear();

    /**
     * @return Loaded submissions.
     */
    const std::vector<Submission>& getSubmissions() const;

    /**
     * @return Loaded reviewers.
     */
    const std::vector<Reviewer>& getReviewers() const;

    /**
     * @return Current parameters.
     */
    const Parameters& getParameters() const;

    /**
     * @return Current control settings.
     */
    const ControlSettings& getControlSettings() const;

    private:
    std::vector<Submission> submissions;
    std::vector<Reviewer> reviewers;
    Parameters parameters;
    ControlSettings controlSettings;

    std::set<int> submissionIds;
    std::set<int> reviewerIds;

    bool hasError = false;

    /**
     * @brief Internal helper to parse a submission line.
     * @complexity O(L) where L is line length.
     */
    void parseSubmissionLine(const std::string& line);

    /**
     * @brief Internal helper to parse a reviewer line.
     * @complexity O(L)
     */
    void parseReviewerLine(const std::string& line);

    /**
     * @brief Internal helper to parse a parameter line.
     * @complexity O(L)
     */
    void parseParameterLine(const std::string& line);

    /**
     * @brief Internal helper to parse a control line.
     * @complexity O(L)
     */
    void parseControlLine(const std::string& line);

    /**
     * @brief Utility to trim whitespace from a string.
     */
    std::string trim(const std::string& str) const;

    /**
     * @brief Utility to split a CSV line by commas.
     */
    std::vector<std::string> splitCSVLine(const std::string& line) const;

    /**
     * @brief Utility to strip quotes from a CSV field.
     */
    std::string stripQuotes(const std::string& str) const;
};

#endif //DA_1ST_PROJECT_CSVPARSER_H