//
// Created by andresantos on 07/03/26.
//

#include "BatchRunner.h"
#include <iostream>
#include <string>

using namespace std;

BatchRunner::BatchRunner() {}

void BatchRunner::run(const string & inputFile, const string & riskFile) {
    cout<<"Running in Batch mode..."<<endl;
    cout<<"Input file: "<<inputFile<<endl;
    cout<<"Risk analysis output: "<<riskFile<<endl;

    parseData(inputFile);
    executeAndSave(riskFile);

    cout<<"Batch execution finished."<<endl;
}

void BatchRunner::parseData(const string& inputFile) {
    //CSV Parser
    cout<<"[Stub]Parsing CSV file..."<<endl;
    //in the future:
    //cout<<"Batch: Parsing "<<inputFile<<"..."<<endl;
}
void BatchRunner::executeAndSave(const string& riskFile) {
    //MaxFlow and saves
    cout<<"[Stub]Executing MaxFlow..."<<endl;
    //in the future:
    //cout<<"Batch: Executing assigment and saving risk results to "<<riskFile<<"..."<<endl;
}
