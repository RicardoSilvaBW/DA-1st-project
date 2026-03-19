//
// Created by andresantos on 07/03/26.
//

#include "Menu.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_set>

using namespace std;

Menu::Menu() {
    // Since we don't have all the pieces yet, we can initialize other stuff like the parser
}

// helpers
bool Menu::requireData() const {
    if (!dataLoaded) {
        cout << "No data loaded. Please use option 1 to read an input file first.\n";
        return false;
    }
    return true;
}

void Menu::displayMenuOptions() const {
    cout<<"\n=========================================\n"; //
    cout<<" Scientific Conference Organization Tool \n";
    cout<<"=========================================\n";
    cout<<"1. Read and Parse Input Data\n";
    cout<<"2. Display Submissions\n";
    cout<<"3. Display Reviewers\n";
    cout<<"4. Display Current Parameters\n";
    cout<<"5. Execute MaximumFlow Assignment\n";
    cout<<"6. Execute Risk Analysis\n";
    cout<<"0. Exit\n";
    cout<<"=========================================\n";
}

void Menu::runInteractive() {
    int option = -1;
    string inputStr;
    bool hasSelectedOption = false;

    displayMenuOptions();

    while (true) {
        if (hasSelectedOption) {
            cout << "\n";
        }

        cout << "Select an option (0-6, m for menu): ";
        getline(cin, inputStr);

        if (inputStr == "m" || inputStr == "M") {
            cout << "\n";
            displayMenuOptions();
            continue;
        }

        try {
            option = stoi(inputStr); // parses the user's input as an integer; invalid non-numeric input is handled by the catch block
        } catch (...) {
            cout << "Invalid input. Please enter a number between 0 and 6, or m to show the menu.\n";
            continue;
        }

        hasSelectedOption = true;

        switch (option) {
            case 1:
                readAndParseData();
                break;
            case 2:
                displaySubmissions();
                break;
            case 3:
                displayReviewers();
                break;
            case 4:
                displayParameters();
                break;
            case 5:
                executeMaxFlowAssignment();
                break;
            case 6:
                executeRiskAnalysis();
                break;
            case 0:
                cout << "Exiting program...\n";
                return;
            default:
                cout << "Invalid option. Please choose a number between 0 and 6.\n";
                break;
        }
    }
}

void Menu::readAndParseData() {
    // cout<<"[Stub] Reading and Parsing CSV...\n";

    if (dataLoaded){
        cout << "Data is already loaded. Replace it with a new file? (y/n): ";
        string answer;
        getline(cin, answer);
        if (answer != "y" && answer != "Y"){
            cout << "Load cancelled.\n";
            return;
        }
    }

    cout << "Enter input file path (.csv): ";
    string filename;
    getline(cin, filename);

    if (filename.empty()){
        cout << "No filename entered.\n";
        return;
    }

    // extension isn't .csv
    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".csv"){
        cout << "File is not .csv\n";
    }

    cout << "Parsing \"" << filename << "\"...\n";

    if (!parser.parseFile(filename)){
        cout << "Failed to parse file.\n";
        dataLoaded = false;
        return;
    }

    bool valid = true;

    // sees if there's a duplicate submission ID
    const auto& subs = parser.getSubmissions();
    unordered_set<int> seenIds;
    for (const auto& s : subs){
        if (!seenIds.insert(s.getId()).second){
                cerr << "Error: duplicate submission ID " << s.getId() << ".\n";
                valid = false;
        }
    }

    // same but for reviewer IDs
    const auto& revs = parser.getReviewers();
    unordered_set<int> seenRevs;
    for (const auto& r : revs){
        if (!seenRevs.insert(r.getId()).second){
                cerr << "Error: duplicate review ID " << r.getId() << ".\n";
                valid = false;
        }
    }

    // checks the required parameter
    const auto& params = parser.getParameters();
    if (params.minReviewsPerSubmission <= 0){
        cerr << "Error: MinReviewsPerSubmission must be a positive integer.\n";
        valid = false;
    }
    if (params.maxReviewsPerReviewer <= 0){
        cerr << "Error: MaxReviewsPerReviewer must be a positive integer.\n";
        valid = false;
    }

    if (!valid){
        cout << "File rejected due to consistency errors.\n";
        dataLoaded = false;
        return;
    }

    dataLoaded = true;
    cout    << "Successfully loaded: "
            << subs.size() << " submission(s), "
            << revs.size() << " reviewer(s).\n";
}

void Menu::displaySubmissions() const {
    // cout<<"[Stub] Displaying Submissions...\n";
    if (!requireData()){
        return;
    }

    const auto& subs = parser.getSubmissions();
    if (subs.empty()){
        cout << "No submissions found.\n";
        return;
    }

    cout << "\n--- Submissions (" << subs.size() << ")---\n";
    cout    << left
            << setw(6)  << "ID"
            << setw(40) << "Title"
            << setw(22) << "Authors"
            << setw(28) << "E-mail"
            << setw(8)  << "Primary"
            << "Secondary\n";
    cout << string(110, '-') << "\n";

    for (const auto& s : subs){

        string title = s.getTitle();
        if (title.size() > 37){
            title = title.substr(0, 37) + "...";
        }

        string authors = s.getAuthors();
        if (authors.size() > 19){
            authors = authors.substr(0, 19) + "...";
        }

        cout    << left
                << setw(6)  << s.getId()
                << setw(40) << title
                << setw(22) << authors
                << setw(28) << s.getEmail()
                << setw(8)  << s.getPrimaryTopic()
                << (s.getSecondaryTopic() != 0 ? to_string(s.getSecondaryTopic()) : "-")
                << "\n";
    }
}

void Menu::displayReviewers() const {
    // cout<<"[Stub] Displaying Reviewers...\n";
    if (!requireData()){
        return;
    }

    const auto& revs = parser.getReviewers();
    if (revs.empty()){
        cout << "No reviewers found.\n";
        return;
    }

    cout << "\n--- Reviewers (" << revs.size() << ") ---\n";
    cout    << left
            << setw(6)  << "ID"
            << setw(28) << "Name"
            << setw(28) << "E-mail"
            << setw(10) << "Primary"
            << "Secondary\n";
    cout << string(78, '-') << "\n";

    for (const auto& r : revs){
        cout << left
             << setw(6)  << r.getId()
             << setw(28) << r.getName()
             << setw(28) << r.getEmail()
             << setw(10) << r.getPrimaryExpertise()
             << (r.getSecondaryExpertise() != 0 ? to_string(r.getSecondaryExpertise()) : "-")
             << "\n";
    }
}

void Menu::displayParameters() const {
    // cout<<"[Stub] Displaying Parameters...\n";
    if (!requireData()){
        return;
    }

    const auto& p = parser.getParameters();
    const auto & cs = parser.getControlSettings();

    cout << "\n--- Parameters ---\n";
    cout << "  MinReviewsPerSubmission   : " << p.minReviewsPerSubmission    << "\n";
    cout << "  MaxReviewsPerReviewer     : " << p.maxReviewsPerReviewer      << "\n";
    cout << "  PrimaryReviewerExpertise  : " << p.primaryReviewerExpertise   << "\n";
    cout << "  SecondaryReviewerExpertise: " << p.secondaryReviewerExpertise << "\n";
    cout << "  PrimarySubmissionDomain   : " << p.primarySubmissionDomain    << "\n";
    cout << "  SecondarySubmissionDomain : " << p.secondarySubmissionDomain  << "\n";

    cout << "\n--- Control Settings ---\n";
    cout << "  GenerateAssignments: " << cs.generateAssignments << "\n";
    cout << "  RiskAnalysis       : " << cs.riskAnalysis        << "\n";
    cout << "  OutputFileName     : " << cs.outputFilename      << "\n";
}

void Menu::executeMaxFlowAssignment() {
    // Expected to formulate the Review Assignment Problem as a Max-Flow problem
    // cout<<"[Stub] Executing MaxFlow Assignment...\n";
    if (!requireData()){
        return;
    }

    const auto& cs = parser.getControlSettings();

    if (cs.generateAssignments == 0){
        cout << "Assignment generaion is disabled (GenerateAssignments = 0 in input file).\n";
        cout << "The assignment will be computed but not reported.\n";
    }

    string modeDesc;
    switch (cs.generateAssignments){
        case 1:
            modeDesc = "primary submission domains + primary reviewer expertise only";
            break;
        case 2:
            modeDesc = "primary & secondary submission domains + primary reviewer expertise";
            break;
        case 3:
            modeDesc = "all primary & secondary domains for both submissions and reviewers";
            break;
        default:
            modeDesc = "primary submission domains + primary reviewr expertise only";
            break;
    }

    cout << "Mode: " << modeDesc << "\n";
    cout << "Output file: " << cs.outputFilename << "\n";

    // TODO: still need to build a flow network and run Edmonds-Karp (T 2.1)
    cout << "[TODO] Maximum Flow assignment not yet implemented.\n";
}

void Menu::executeRiskAnalysis() {
    // Tests if the absence of one or more reviewers jeopardizes the review process
    // cout<<"[Stub] Executing Risk Analysis...\n";
    if (!requireData()){
        return;
    }

    const auto& cs = parser.getControlSettings();

    if (cs.riskAnalysis == 0){
        cout << "Risk analysis is disabled (RiskAnalysis = 0 in input file).\n";
        return;
    }

    else if (cs.riskAnalysis == 1){
        cout << "Risk Analysis K=1: will check if removing any single reviewer\n";
        cout << " makes it impossible to meet the minimum reviews per submission.\n";
    }

    else{
        cout << "Risk Analysis K=" << cs.riskAnalysis << ": will check if removing any group of "
             << cs.riskAnalysis << " reviewers\n";
        cout << " makes it impossible to meet the minimum reviews per submission.\n";
    }

    // TODO: implement risk analysis (T2.2 / T2.3)
    cout << "[TODO] Risk Analysis not yet implemented.\n";
}
