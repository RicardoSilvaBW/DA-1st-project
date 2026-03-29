//
// Created by andresantos on 09/03/26.
//

/**
 * @file CSVParser.cpp
 * @brief Implementation of the CSVParser class.
 */

#include "CSVParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * @brief Constructor for CSVParser.
 */
CSVParser::CSVParser() {
    
}

const vector<Submission>& CSVParser::getSubmissions() const {
    return submissions;
}
const vector<Reviewer>& CSVParser::getReviewers() const {
    return reviewers;
}
const Parameters& CSVParser::getParameters() const {
    return parameters;
}
const ControlSettings& CSVParser::getControlSettings() const {
    return controlSettings;
}

string CSVParser::trim(const string& str) const { 
    size_t first = str.find_first_not_of(" \t\n\r"); 
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1)); 
}

string CSVParser::stripQuotes(const string& str) const { 
    string cleaned = trim(str);
    if (cleaned.size() >= 2 && cleaned.front() == '"' && cleaned.back() == '"') {
        return cleaned.substr(1, cleaned.size() - 2);
    }
    return cleaned;
}

vector<string> CSVParser::splitCSVLine(const string& line) const { 
    vector<string> fields;
    string field;
    stringstream ss(line);

    while (getline(ss, field, ',')) {
        fields.push_back(trim(field));
    }

    if (!line.empty() && line.back() == ',') {
        fields.push_back("");
    }

    return fields;
}

/**
 * @brief Clears the internal data structures.
 */
void CSVParser::clear() {
    submissions.clear();
    reviewers.clear();
    submissionIds.clear();
    reviewerIds.clear();
    parameters = Parameters{};
    controlSettings = ControlSettings{};
    hasError = false;
}

/**
 * @brief Parses the input CSV file.
 * @param filename Path to the CSV file.
 * @return true if successful, false otherwise.
 * @complexity O(N) where N is number of characters in file.
 */
bool CSVParser::parseFile(const string& filename) { 
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << "\n";
        return false;
    }

    clear();

    string line;
    string currentSection = "";

    while (getline(file, line)) {
        string trimmedLine = trim(line);
        if (trimmedLine.empty()) continue;

        
        if (trimmedLine[0] == '#') {
            if (trimmedLine.find("#Submissions") == 0) {
                currentSection = "Submissions";
            }
            else if (trimmedLine.find("#Reviewers") == 0) {
                currentSection = "Reviewers";
            }
            else if (trimmedLine.find("#Parameters") == 0) {
                currentSection = "Parameters";
            }
            else if (trimmedLine.find("#Control") == 0) {
                currentSection = "Control";
            }
            continue; 
        }
        
        size_t hashPos = trimmedLine.find("#");
        if (hashPos != string::npos) {
            trimmedLine = trim(trimmedLine.substr(0, hashPos));
            if (trimmedLine.empty()) continue;
        }

        
        if (currentSection == "Submissions") {
            parseSubmissionLine(trimmedLine);
        }
        else if (currentSection == "Reviewers") {
            parseReviewerLine(trimmedLine);
        }
        else if (currentSection == "Parameters") {
            parseParameterLine(trimmedLine);
        }
        else if (currentSection == "Control") {
            parseControlLine(trimmedLine);
        }
    }
    file.close();

    if (hasError) {
        cerr << "Parsing failed due to inconsistent data.\n";
        return false;
    }
    return true;
}

void CSVParser::parseSubmissionLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 6) {
        cerr << "Warning: Invalid submission line (wrong field count): " << line << "\n";
        hasError = true;
        return;
    }

    try {
        int id = stoi(fields[0]);
        if (submissionIds.find(id) != submissionIds.end()) {
            cerr << "Error: Duplicate submission ID found: " << id << "\n";
            hasError = true;
            return;
        }

        string title = stripQuotes(fields[1]);
        string authors = stripQuotes(fields[2]);
        string email = stripQuotes(fields[3]);

        if (fields[4].empty()) {
            cerr << "Error: Submission ID " << id << " is missing mandatory primary topic.\n";
            hasError = true;
            return;
        }
        int primary = stoi(fields[4]);
        if (primary < 1) {
            cerr << "Warning: Submission ID " << id << " has topic ID < 1: " << primary << "\n";
        }
        int secondary = fields[5].empty() ? 0 : stoi(fields[5]);
        if (secondary < 0) {
            cerr << "Warning: Submission ID " << id << " has secondary topic ID < 0: " << secondary << "\n";
        }

        submissions.emplace_back(id, title, authors, email, primary, secondary);
        submissionIds.insert(id);
    } catch (const exception& e) {
        cerr << "Error: Numeric conversion failed in submission line: " << line << " (" << e.what() << ")\n";
        hasError = true;
    }
}

void CSVParser::parseReviewerLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 5) {
        cerr << "Warning: Invalid reviewer line (wrong field count): " << line << "\n";
        hasError = true;
        return;
    }

    try {
        int id = stoi(fields[0]);
        if (reviewerIds.find(id) != reviewerIds.end()) {
            cerr << "Error: Duplicate reviewer ID found: " << id << "\n";
            hasError = true;
            return;
        }

        string name = stripQuotes(fields[1]);
        string email = stripQuotes(fields[2]);

        if (fields[3].empty()) {
            cerr << "Error: Reviewer ID " << id << " is missing mandatory primary expertise.\n";
            hasError = true;
            return;
        }
        int primary = stoi(fields[3]);
        if (primary < 1) {
            cerr << "Warning: Reviewer ID " << id << " has expertise ID < 1: " << primary << "\n";
        }
        int secondary = fields[4].empty() ? 0 : stoi(fields[4]);
        if (secondary < 0) {
            cerr << "Warning: Reviewer ID " << id << " has secondary expertise ID < 0: " << secondary << "\n";
        }

        reviewers.emplace_back(id, name, email, primary, secondary);
        reviewerIds.insert(id);
    } catch (const exception& e) {
        cerr << "Error: Numeric conversion failed in reviewer line: " << line << " (" << e.what() << ")\n";
        hasError = true;
    }
}

void CSVParser::parseParameterLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 2) {
        cerr << "Warning: Invalid parameter line: " << line << "\n";
        hasError = true;
        return;
    }

    try {
        string key = stripQuotes(fields[0]);
        int value = stoi(fields[1]);

        if (key == "MinReviewsPerSubmission") {
            parameters.minReviewsPerSubmission = value;
        }
        else if (key == "MaxReviewsPerReviewer") {
            parameters.maxReviewsPerReviewer = value;
        }
        else if (key == "PrimaryReviewerExpertise") {
            parameters.primaryReviewerExpertise = value;
        }
        else if (key == "SecondaryReviewerExpertise") {
            parameters.secondaryReviewerExpertise = value;
        }
        else if (key == "PrimarySubmissionDomain") {
            parameters.primarySubmissionDomain = value;
        }
        else if (key == "SecondarySubmissionDomain") {
            parameters.secondarySubmissionDomain = value;
        }
        else {
            cerr << "Warning: Unknown parameter key: " << key << "\n";
        }
    } catch (const exception& e) {
        cerr << "Error: Numeric conversion failed in parameter: " << line << " (" << e.what() << ")\n";
        hasError = true;
    }
}

void CSVParser::parseControlLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 2) {
        cerr << "Warning: Invalid control line: " << line << "\n";
        hasError = true;
        return;
    }

    try {
        string key = stripQuotes(fields[0]);
        string value = stripQuotes(fields[1]);

        if (key == "GenerateAssignments") {
            controlSettings.generateAssignments = stoi(value);
        }
        else if (key == "RiskAnalysis") {
            controlSettings.riskAnalysis = stoi(value);
        }
        else if (key == "OutputFileName") {
            controlSettings.outputFilename = value;
        }
        else {
            cerr << "Warning: Unknown control key: " << key << "\n";
        }
    } catch (const exception& e) {
        cerr << "Error: Numeric conversion failed in control line: " << line << " (" << e.what() << ")\n";
        hasError = true;
    }
}