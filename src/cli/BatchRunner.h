//
// Created by andresantos on 07/03/26.
//

#ifndef DA_1ST_PROJECT_BATCHRUNNER_H
#define DA_1ST_PROJECT_BATCHRUNNER_H

#include <string>

class BatchRunner {
    public:
    BatchRunner();
    void run(const std::string& inputFile, const std::string& riskFile);//i named it riskfile becaause of the project guidelines

    private:
    //This eventually will be where we link the IO and Algorithm Logic i think

    void parseData(const std::string& inputFile);
    void executeAndSave(const std::string& riskFile);//This automates some steps the Menu does not (Runs the MaxFlow and writes the results automaticallly to a file)
    };

#endif //DA_1ST_PROJECT_BATCHRUNNER_H