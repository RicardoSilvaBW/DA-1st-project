//
// Created by andresantos on 07/03/26.
//

/**
 * @file Menu.h
 * @brief Header for the Menu class.
 */

#ifndef DA_1ST_PROJECT_MENU_H
#define DA_1ST_PROJECT_MENU_H

#include <string>
#include "../io/CSVParser.h"

/**
 * @class Menu
 * @brief Class that provides the interactive command-line interface.
 * 
 * Task 1.1: Develop the Assignment Tool with a simple command-line menu.
 */
class Menu {
    public:
    /**
     * @brief Constructor for Menu.
     */
    Menu();

    /**
     * @brief Main loop for the interactive menu.
     */
    void runInteractive();

    private:
    CSVParser parser;
    bool dataLoaded = false;

    /**
     * @brief Option to read and parse the input data.
     */
    void readAndParseData();

    /**
     * @brief Option to execute risk analysis.
     */
    void executeRiskAnalysis();

    /**
     * @brief Option to execute Max-Flow review assignment.
     */
    void executeMaxFlowAssignment();

    /**
     * @brief Displays loaded submissions.
     */
    void displaySubmissions() const;

    /**
     * @brief Displays loaded reviewers.
     */
    void displayReviewers() const;

    /**
     * @brief Displays current parameters and control settings.
     */
    void displayParameters() const;

    /**
     * @brief Prints the menu options to the console.
     */
    void displayMenuOptions() const;

    /**
     * @brief Checks if data has been loaded.
     * @return true if data is loaded, false otherwise.
     */
    bool requireData() const;
};

#endif //DA_1ST_PROJECT_MENU_H