//
// Created by andresantos on 07/03/26.
//

#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

Menu::Menu() {
    // Since we don't have all the pieces yet, we can initialize other stuff like the parser
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
    cout<<"[Stub] Reading and Parsing CSV...\n";
}

void Menu::displaySubmissions() const {
    cout<<"[Stub] Displaying Submissions...\n";
}

void Menu::displayReviewers() const {
    cout<<"[Stub] Displaying Reviewers...\n";
}

void Menu::displayParameters() const {
    cout<<"[Stub] Displaying Parameters...\n";
}

void Menu::executeMaxFlowAssignment() {
    // Expected to formulate the Review Assignment Problem as a Max-Flow problem
    cout<<"[Stub] Executing MaxFlow Assignment...\n";
}

void Menu::executeRiskAnalysis() {
    // Tests if the absence of one or more reviewers jeopardizes the review process
    cout<<"[Stub] Executing Risk Analysis...\n";
}