//
// Created by andresantos on 07/03/26.
//

/**
 * @file BatchRunner.cpp
 * @brief Implementation of the BatchRunner class for non-interactive execution.
 */

#include "BatchRunner.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "../algorithm/FlowNetwork.h"
#include "../algorithm/RiskAnalyzer.h"

using namespace std;

/**
 * @brief Constructor for BatchRunner.
 */
BatchRunner::BatchRunner() {}

/**
 * @brief Runs the program in batch mode with given input and output files.
 * @param inputFile Path to the input CSV file.
 * @param outputFile Path where results will be saved.
 * @complexity O(N + V*E^2) where N is file size and flow complexity applies.
 */
void BatchRunner::run(const string & inputFile, const string & outputFile) {
    cout << "Running in Batch mode..." << endl;
    cout << "Input file: " << inputFile << endl;
    cout << "Output file: " << outputFile << endl;

    parseData(inputFile);
    executeAndSave(outputFile);

    cout << "Batch execution finished." << endl;
}

/**
 * @brief Parses data from the input file.
 * @param inputFile Path to the input file.
 * @complexity O(N)
 */
void BatchRunner::parseData(const string& inputFile) {
    if (!parser.parseFile(inputFile)) {
        cerr << "Error: Failed to parse input file: " << inputFile << endl;
        exit(1);
    }
}

/**
 * @brief Executes algorithms and saves results to the output file.
 * @param outputFile Path to the output file.
 * @complexity O(V * E^2) for MaxFlow, O(R^K * V * E^2) for Risk Analysis.
 */
void BatchRunner::executeAndSave(const string& outputFile) {
    const auto& cs = parser.getControlSettings();
    const auto& params = parser.getParameters();
    const auto& subs = parser.getSubmissions();
    const auto& revs = parser.getReviewers();

    FlowNetwork network(revs, subs, params, cs);
    network.build();
    int flow = network.run();

    int totalRequired = static_cast<int>(subs.size()) * params.minReviewsPerSubmission;

    ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open output file " << outputFile << " for writing.\n";
        return;
    }

    if (cs.generateAssignments != 0) {
        if (flow < totalRequired) {
            auto assignments = network.getReviewAssignments();
            if (!assignments.empty()) {
                sort(assignments.begin(), assignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
                    if (a.getSubmissionId() != b.getSubmissionId()) return a.getSubmissionId() < b.getSubmissionId();
                    return a.getReviewerId() < b.getReviewerId();
                });

                outFile << "#SubmissionId,ReviewerId,Match\n";
                for (const auto& a : assignments) {
                    outFile << a.getSubmissionId() << ", " << a.getReviewerId() << ", " << a.getSubmissionDomain() << "\n";
                }

                auto dualAssignments = assignments;
                sort(dualAssignments.begin(), dualAssignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
                    if (a.getReviewerId() != b.getReviewerId()) return a.getReviewerId() < b.getReviewerId();
                    return a.getSubmissionId() < b.getSubmissionId();
                });

                outFile << "#ReviewerId,SubmissionId,Match\n";
                for (const auto& a : dualAssignments) {
                    outFile << a.getReviewerId() << ", " << a.getSubmissionId() << ", " << a.getSubmissionDomain() << "\n";
                }
                outFile << "#Total: " << assignments.size() << "\n";
            }

            auto missing = network.getMissingReviews();
            if (!missing.empty()) {
                outFile << "#SubmissionId,Domain,MissingReviews\n";
                for (const auto& m : missing) {
                    outFile << m.getSubmissionId() << ", " << m.getDomain() << ", " << m.getMissingCount() << "\n";
                }
            }
        } else {
            auto assignments = network.getReviewAssignments();
            
            sort(assignments.begin(), assignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
                if (a.getSubmissionId() != b.getSubmissionId()) return a.getSubmissionId() < b.getSubmissionId();
                return a.getReviewerId() < b.getReviewerId();
            });

            outFile << "#SubmissionId,ReviewerId,Match\n";
            for (const auto& a : assignments) {
                outFile << a.getSubmissionId() << ", " << a.getReviewerId() << ", " << a.getSubmissionDomain() << "\n";
            }

            outFile << "#ReviewerId,SubmissionId,Match\n";
            auto dualAssignments = assignments;
            sort(dualAssignments.begin(), dualAssignments.end(), [](const ReviewAssignment& a, const ReviewAssignment& b) {
                if (a.getReviewerId() != b.getReviewerId()) return a.getReviewerId() < b.getReviewerId();
                return a.getSubmissionId() < b.getSubmissionId();
            });

            for (const auto& a : dualAssignments) {
                outFile << a.getReviewerId() << ", " << a.getSubmissionId() << ", " << a.getSubmissionDomain() << "\n";
            }
            outFile << "#Total: " << assignments.size() << "\n";
        }
    }

    if (cs.riskAnalysis > 0) {
        RiskAnalyzer analyzer(subs, revs, params, cs);
        RiskResult result = analyzer.analyze();

        outFile << "#Risk Analysis: " << cs.riskAnalysis << "\n";
        const auto& riskyIds = result.getRiskyReviewerIds();
        for (size_t i = 0; i < riskyIds.size(); ++i) {
            outFile << riskyIds[i] << (i == riskyIds.size() - 1 ? "" : ", ");
        }
        outFile << "\n";
    }

    outFile.close();
}
