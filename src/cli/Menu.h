//
// Created by andresantos on 07/03/26.
//

#ifndef DA_1ST_PROJECT_MENU_H
#define DA_1ST_PROJECT_MENU_H

#include <string>

class Menu {
    public:
    Menu();
    void runInteractive();

    private:
    void readAndParseData();
    void executeRiskAnalysis();
    void executeMaxFlowAssignment();
    void displaySubmissions() const;
    void displayReviewers() const;
    void displayParameters() const;
    void displayMenuOptions() const;
};

#endif //DA_1ST_PROJECT_MENU_H