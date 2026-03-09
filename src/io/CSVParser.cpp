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
    size_t first = str.find_first_not_of("\t\n\r");//finds common whitespace characters in files
    if (string::npos == first) return "";
    size_t last = str.find_last_not_of("\t\n\r");
    return str.substr(first, (last - first + 1));//extracts the clean string, starts at index first, and ends in the index last-first+1
}

bool CSVParser::parseFile(const string& filename) {//the bool flag described in the project description
    ifstream file(filename);
    if (!file.is_open()) {
        cout<<"Error: Could not open file: "<<filename<<"\n";
        return false;
    }
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
            parseSubmission(trimmedLine);
        }
        else if (currentSection == "Reviewers") {
            parseReviewer(trimmedLine);
        }
        else if (currentSection == "Parameters") {
            parseParameters(trimmedLine);
        }
        else if (currentSection == "Control") {
            parseControlSettings(trimmedLine);
        }
    }
    file.close();
    return true;
}

void CSVParser::parseSubmissionLine(const string& line) {
    cout<<"[Stub]Found Submission: "<<line<<"\n";
}
void CSVParser::parseReviewerLine(const string& line) {
    cout<<"[Stub]Found Reviewer: "<<line<<"\n";
}
void CSVParser::parseParameterLine(const string& line) {
    cout<<"[Stub]Found Parameters: "<<line<<"\n";
}
void CSVParser::parseControlLine(const string& line) {
    cout<<"[Stub]Found Control: "<<line<<"\n";
}