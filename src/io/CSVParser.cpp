//
// Created by andresantos on 09/03/26.
//

#include "CSVParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

CSVParser::CSVParser() {
    //Constructor
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

string CSVParser::trim(const string& str) const {//cleans the csv files
    size_t first = str.find_first_not_of(" \t\n\r");//finds common whitespace characters in files
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));//extracts the clean string, starts at index first, and ends in the index last-first+1
}

string CSVParser::stripQuotes(const string& str) const {//cleans surrounding quotes from csv fields when they exist
    string cleaned = trim(str);
    if (cleaned.size() >= 2 && cleaned.front() == '"' && cleaned.back() == '"') {
        return cleaned.substr(1, cleaned.size() - 2);
    }
    return cleaned;
}

vector<string> CSVParser::splitCSVLine(const string& line) const {//splits a csv line by commas and trims each field
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

bool CSVParser::parseFile(const string& filename) {//the bool flag described in the project description
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Error: Could not open file: "<<filename<<"\n";
        return false;
    }

    submissions.clear();
    reviewers.clear();
    parameters = Parameters{};
    controlSettings = ControlSettings{};

    string line;
    string currentSection="";

    while (getline(file, line)) {
        string trimmedLine = trim(line);
        if (trimmedLine.empty()) continue;

        //We need to check if the line is a header of the section or a comment
        if (trimmedLine[0] == '#') {
            if (trimmedLine.find("#Submissions")==0) {
                currentSection = "Submissions";
            }
            else if (trimmedLine.find("#Reviewers")==0) {
                currentSection = "Reviewers";
            }
            else if (trimmedLine.find("#Parameters")==0) {
                currentSection = "Parameters";
            }
            else if (trimmedLine.find("#Control")==0) {
                currentSection = "Control";
            }
            continue;//it continues whenever it's none of those 4
        }
        //In case a '#' is present in the line, we remove everything after it
        size_t hashPos = trimmedLine.find("#");
        if (hashPos != string::npos) {
            trimmedLine = trim(trimmedLine.substr(0, hashPos));
            if (trimmedLine.empty()) continue;
        }

        //Gives the data to the correct functions of the parser
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
    return true;
}

void CSVParser::parseSubmissionLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 6) {
        cout<<"Warning: Invalid submission line: "<<line<<"\n";
        return;
    }

    int id = stoi(fields[0]);
    string title = stripQuotes(fields[1]);
    string authors = stripQuotes(fields[2]);
    string email = stripQuotes(fields[3]);
    int primary = stoi(fields[4]);
    int secondary = fields[5].empty() ? 0 : stoi(fields[5]);

    submissions.emplace_back(id, title, authors, email, primary, secondary);
}

void CSVParser::parseReviewerLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 5) {
        cout<<"Warning: Invalid reviewer line: "<<line<<"\n";
        return;
    }

    int id = stoi(fields[0]);
    string name = stripQuotes(fields[1]);
    string email = stripQuotes(fields[2]);
    int primary = stoi(fields[3]);
    int secondary = fields[4].empty() ? 0 : stoi(fields[4]);

    reviewers.emplace_back(id, name, email, primary, secondary);
}

void CSVParser::parseParameterLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 2) {
        cout<<"Warning: Invalid parameter line: "<<line<<"\n";
        return;
    }

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
        cout<<"Warning: Unknown parameter key: "<<key<<"\n";
    }
}

void CSVParser::parseControlLine(const string& line) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() != 2) {
        cout<<"Warning: Invalid control line: "<<line<<"\n";
        return;
    }

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
        cout<<"Warning: Unknown control key: "<<key<<"\n";
    }
}