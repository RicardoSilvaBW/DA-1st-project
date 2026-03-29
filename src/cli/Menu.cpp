//
// Created by andresantos on 07/03/26.
//

/**
 * @file Menu.cpp
 * @brief Implementation of the Menu class.
 */

#include "Menu.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_set>
#include "../algorithm/RiskAnalyzer.h"
#include "../algorithm/FlowNetwork.h"
#include "../model/ReviewAssignment.h"
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * @brief Constructor for Menu.
 */
Menu::Menu() {
    
}


/**
 * @brief Helper method to ensure data is loaded before proceeding with operations.
 * @return true if data is loaded, false otherwise.
 */
bool Menu::requireData() const {
    if (!dataLoaded) {
        cout << "No data loaded. Please use option 1 to read an input file first.\n";
        return false;
    }
    return true;
}

/**
 * @brief Prints the menu options to the console.
 */
void Menu::displayMenuOptions() const {
    cout<<"\n=========================================\n"; 
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

/**
 * @brief Main loop for the interactive menu.
 */
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
            option = stoi(inputStr); 
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

/**
 * @brief Prompts the user for a filename and parses the data.
 */
void Menu::readAndParseData() {
    

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

    
    const auto& subs = parser.getSubmissions();
    unordered_set<int> seenIds;
    for (const auto& s : subs){
        if (!seenIds.insert(s.getId()).second){
                cerr << "Error: duplicate submission ID " << s.getId() << ".\n";
                valid = false;
        }
    }

    
    const auto& revs = parser.getReviewers();
    unordered_set<int> seenRevs;
    for (const auto& r : revs){
        if (!seenRevs.insert(r.getId()).second){
                cerr << "Error: duplicate review ID " << r.getId() << ".\n";
                valid = false;
        }
    }

    
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

/**
 * @brief Displays loaded submissions in a formatted table.
 */
void Menu::displaySubmissions() const {
    
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

/**
 * @brief Displays loaded reviewers in a formatted table.
 */
void Menu::displayReviewers() const {
    
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

/**
 * @brief Displays current parameters and control settings.
 */
void Menu::displayParameters() const {
    
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

/**
 * @brief Executes the Max-Flow algorithm to assign reviews and saves to file.
 */
void Menu::executeMaxFlowAssignment() {
    if (!requireData()){
        return;
    }

    const auto& cs = parser.getControlSettings();
    const auto& params = parser.getParameters();
    const auto& subs = parser.getSubmissions();
    const auto& revs = parser.getReviewers();

    string modeDesc;
    switch (cs.generateAssignments){
        case 1: modeDesc = "primary domains only"; break;
        case 2: modeDesc = "primary & secondary submission domains"; break;
        case 3: modeDesc = "all primary & secondary domains"; break;
        default: modeDesc = "primary domains only"; break;
    }

    cout << "Mode: " << modeDesc << "\n";
    cout << "Output file: " << cs.outputFilename << "\n";

    FlowNetwork network(revs, subs, params, cs);
    network.build();
    int flow = network.run();

    int totalRequired = static_cast<int>(subs.size()) * params.minReviewsPerSubmission;
    
    ofstream outFile(cs.outputFilename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open output file " << cs.outputFilename << " for writing.\n";
        return;
    }

    if (flow < totalRequired) {
        cout << "UNSUCCESSFUL assignment: Total flow " << flow << " < Required " << totalRequired << "\n";
        auto assignments = network.getReviewAssignments();
        if (!assignments.empty()) {
            sort(assignments.begin(), assignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
                if (a.getSubmissionId() != b.getSubmissionId()) return a.getSubmissionId() < b.getSubmissionId();
                return a.getReviewerId() < b.getReviewerId();
            });

            outFile << "#SubmissionId,ReviewerId,Match\n";
            for (const auto& a : assignments) {
                outFile << a.getSubmissionId() << ", " << a.getReviewerId() << ", " << a.getSubmissionDomain() << "\n";
            }

            auto dualAssignments = assignments;
            sort(dualAssignments.begin(), dualAssignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
                if (a.getReviewerId() != b.getReviewerId()) return a.getReviewerId() < b.getReviewerId();
                return a.getSubmissionId() < b.getSubmissionId();
            });

            outFile << "#ReviewerId,SubmissionId,Match\n";
            for (const auto& a : dualAssignments) {
                outFile << a.getReviewerId() << ", " << a.getSubmissionId() << ", " << a.getSubmissionDomain() << "\n";
            }
            outFile << "#Total: " << assignments.size() << "\n";
        }

        auto missing = network.getMissingReviews();
        if (!missing.empty()) {
            outFile << "#SubmissionId,Domain,MissingReviews\n";
            for (const auto& m : missing) {
                outFile << m.getSubmissionId() << ", " << m.getDomain() << ", " << m.getMissingCount() << "\n";
            }
        }
    } else {
        cout << "SUCCESSFUL assignment! Total flow: " << flow << "\n";
        auto assignments = network.getReviewAssignments();
        
        
        sort(assignments.begin(), assignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
            if (a.getSubmissionId() != b.getSubmissionId()) return a.getSubmissionId() < b.getSubmissionId();
            return a.getReviewerId() < b.getReviewerId();
        });

        
        outFile << "#SubmissionId,ReviewerId,Match\n";
        for (const auto& a : assignments) {
            outFile << a.getSubmissionId() << ", " << a.getReviewerId() << ", " << a.getSubmissionDomain() << "\n";
        }
        
        
        outFile << "#ReviewerId,SubmissionId,Match\n";
        
        auto dualAssignments = assignments;
        sort(dualAssignments.begin(), dualAssignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
            if (a.getReviewerId() != b.getReviewerId()) return a.getReviewerId() < b.getReviewerId();
            return a.getSubmissionId() < b.getSubmissionId();
        });

        for (const auto& a : dualAssignments) {
            outFile << a.getReviewerId() << ", " << a.getSubmissionId() << ", " << a.getSubmissionDomain() << "\n";
        }
        outFile << "#Total: " << assignments.size() << "\n";
    }
    outFile.close();
    cout << "Results saved to " << cs.outputFilename << "\n";
}

/**
 * @brief Executes risk analysis based on control settings.
 */
void Menu::executeRiskAnalysis() {
    if (!requireData()){
        return;
    }

    const auto& cs = parser.getControlSettings();
    if (cs.riskAnalysis <= 0){
        cout << "Risk analysis is disabled.\n";
        return;
    }

    RiskAnalyzer analyzer(parser.getSubmissions(), parser.getReviewers(), parser.getParameters(), cs);
    cout << "Executing Risk Analysis (K=" << cs.riskAnalysis << ")... This may take a moment.\n";
    
    RiskResult result = analyzer.analyze();

    cout << "\n--- Risk Analysis Results ---\n";
    cout << "Number of risky reviewers: " << result.getRiskLevel() << "\n";
    
    if (result.getRiskLevel() > 0) {
        cout << "Risky Reviewer IDs: ";
        for (size_t i = 0; i < result.getRiskyReviewerIds().size(); ++i) {
            cout << result.getRiskyReviewerIds()[i] << (i == result.getRiskyReviewerIds().size() - 1 ? "" : ", ");
        }
        cout << "\n";
    } else {
        cout << "No risky reviewers found for K=" << cs.riskAnalysis << ".\n";
    }

    
    ofstream outFile(cs.outputFilename, ios::app); 
    if (outFile.is_open()) {
        outFile << "#Risk Analysis: " << cs.riskAnalysis << "\n";
        const auto& riskyIds = result.getRiskyReviewerIds();
        for (size_t i = 0; i < riskyIds.size(); ++i) {
            outFile << riskyIds[i] << (i == riskyIds.size() - 1 ? "" : ", ");
        }
        outFile << "\n";
        outFile.close();
        cout << "Risk Analysis results appended to " << cs.outputFilename << "\n";
    }
}
