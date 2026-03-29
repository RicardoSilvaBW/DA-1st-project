//
// Created by andresantos on 07/03/26.
//

/**
 * @file BatchRunner.h
 * @brief Header for the BatchRunner class.
 */

#ifndef DA_1ST_PROJECT_BATCHRUNNER_H
#define DA_1ST_PROJECT_BATCHRUNNER_H

#include <string>
#include "../io/CSVParser.h"

/**
 * @class BatchRunner
 * @brief Class that handles execution in batch mode.
 */
class BatchRunner {
    public:
    /**
     * @brief Constructor for BatchRunner.
     */
    BatchRunner();

    /**
     * @brief Executes the tool in batch mode.
     * @param inputFile Input filename.
     * @param outputFile Output filename.
     */
    void run(const std::string& inputFile, const std::string& outputFile);

    private:
    CSVParser parser;

    /**
     * @brief Internal helper to parse data.
     */
    void parseData(const std::string& inputFile);

    /**
     * @brief Internal helper to execute analysis and save results.
     */
    void executeAndSave(const std::string& outputFile);
    };

#endif //DA_1ST_PROJECT_BATCHRUNNER_H