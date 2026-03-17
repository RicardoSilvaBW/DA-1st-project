//
// Created by ricar on 3/7/2026.
//

#ifndef DA_1ST_PROJECT_CONTROLSETTINGS_H
#define DA_1ST_PROJECT_CONTROLSETTINGS_H

#include <string>

struct ControlSettings {
    int generateAssignments = 0;
    int riskAnalysis = 0;
    std::string outputFilename = "output.csv";
};

#endif //DA_1ST_PROJECT_CONTROLSETTINGS_H