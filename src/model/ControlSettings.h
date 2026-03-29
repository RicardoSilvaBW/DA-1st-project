//
// Created by ricar on 3/7/2026.
//

/**
 * @file ControlSettings.h
 * @brief Struct for controlling the tool's behavior.
 */

#ifndef DA_1ST_PROJECT_CONTROLSETTINGS_H
#define DA_1ST_PROJECT_CONTROLSETTINGS_H

#include <string>

/**
 * @brief Struct containing flags and parameters that control the tool's execution.
 */
struct ControlSettings {
    int generateAssignments = 0;             ///< Strategy for matching (1, 2, or 3).
    int riskAnalysis = 0;                    ///< K value for risk analysis (K=0 means disabled).
    std::string outputFilename = "output.csv"; ///< Name of the file to save results.
};

#endif //DA_1ST_PROJECT_CONTROLSETTINGS_H