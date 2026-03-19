//
// Created by andresantos on 07/03/26.
//

#ifndef DA_1ST_PROJECT_MENU_H
#define DA_1ST_PROJECT_MENU_H

#include <string>
#include "../io/CSVParser.h"

class Menu {
    public:
    Menu();
    void runInteractive();

    private:
    CSVParser parser;
    bool dataLoaded = false;

    void readAndParseData();
    void executeRiskAnalysis();
    void executeMaxFlowAssignment();
    void displaySubmissions() const;
    void displayReviewers() const;
    void displayParameters() const;
    void displayMenuOptions() const;

    bool requireData() const;
};

#endif //DA_1ST_PROJECT_MENU_H