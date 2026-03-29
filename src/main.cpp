//
// Created by ricar on 3/7/2026.
//

/**
 * @file main.cpp
 * @brief Entry point for the Conference Review Management Tool.
 */

#include <iostream>
#include "cli/Menu.h"
#include "cli/BatchRunner.h"
using namespace std;

/**
 * @brief Main function.
 * @param argc Argument count.
 * @param argv Argument values.
 * @return 0 on success.
 */
int main(int argc, char* argv[]) {
    
    
    if (argc == 4 && string(argv[1]) == "-b") {
        string inputFile = argv[2];
        string outputFile = argv[3];
        BatchRunner batch;
        batch.run(inputFile, outputFile);
    }
	else if (argc > 1 && string(argv[1]) == "-b") {
	    cout << "Usage: ./program -b <inputFile> <outputFile>\n";
    }
    
    else {
        Menu appMenu;
        appMenu.runInteractive();
    }
    return 0;
}