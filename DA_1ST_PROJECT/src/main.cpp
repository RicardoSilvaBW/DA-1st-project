//
// Created by ricar on 3/7/2026.
//

#include <iostream>
#include "cli/Menu.h"
#include "cli/BatchRunner.h"
using namespace std;

int main(int argc, char* argv[]) {
    //the else condition exist to determine if the program runs with the cli menu or the batch mode.
    //BatchMode
    if (argc == 4 && string(argv[1]) == "-b") {
        string inputFile = argv[2];
        string riskFile = argv[3];
        BatchRunner batch;
        batch.run(inputFile, riskFile);
    }
	else if (argc >1 && string(argv[1]) == "-b") {
	cout << "Usage: ./program -b <inputFile> <riskFile>\n";}
    //Menu(cli) Test
    else {
        Menu appMenu;
        appMenu.runInteractive();
    }
    return 0;
}