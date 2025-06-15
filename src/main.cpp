#include "process.h"
#include <iostream>
#include <vector>
#include <string>
#include "utils.h"
#include "scheduler.h" 
#include <fstream>

int main() {
    std::vector<Process> baseProcesses;
    std::string algorithm;
    int timeQuantum = 0;

    // Display simulator title
    std::cout << "=====================\n";
    std::cout << " CPU Scheduling Simulator\n";
    std::cout << "=====================\n\n";

    // Let user choose scheduling algorithm
    std::cout << "--- Select Scheduling Algorithm ---\n\n";
    std::cout << "1. FCFS\n";
    std::cout << "2. SRTF\n";
    std::cout << "3. Priority\n";
    std::cout << "4. Round Robin\n";
    std::cout << "5. Auto (Best Fit)\n";
    std::cout << "6. Run All Algorithms & Compare\n";
    std::cout << "\nEnter your choice: ";

    int algoChoice;
    std::cin >> algoChoice;

    // Check if "Run All" option is selected
    bool runAll = (algoChoice == 6);

    // Set the selected algorithm name
    if (!runAll) {
        switch (algoChoice) {
            case 1: algorithm = "FCFS"; break;
            case 2: algorithm = "SRTF"; break;
            case 3: algorithm = "Priority"; break;
            case 4: algorithm = "RR"; break;
            case 5: algorithm = "auto"; break;
            default:
                std::cerr << "Invalid choice.\n";
                return 1;
        }
    }

    // Let user choose input method
    std::cout << "\n--- Select Input Method ---\n\n";
    std::cout << "1. Manual Entry\n";
    std::cout << "2. Load from File\n";
    std::cout << "\nEnter your choice: ";

    int inputChoice;
    std::cin >> inputChoice;
    std::cout << "\n";

    // Handle process input
    if (inputChoice == 1) {
        baseProcesses = getProcessInput(); // Manual entry
    } else if (inputChoice == 2) {
        std::string filename;
        std::cout << "Enter input filename (e.g., input.txt): ";
        std::cin >> filename;
        baseProcesses = getProcessInputFromFile(filename); // Load from file
        if (baseProcesses.empty()) {
            std::cerr << "Failed to read input from file.\n";
            return 1;
        }
    } else {
        std::cerr << "Invalid input method.\n";
        return 1;
    }

    // If RR or auto or runAll, ask for time quantum
    if (runAll || algorithm == "RR" || algorithm == "auto") {
        std::cout << "\nEnter time quantum: ";
        std::cin >> timeQuantum;
    }

    // Clear previous output
    std::ofstream clear("output.txt", std::ios::trunc);
    clear.close();

    // Run selected algorithm(s)
    if (runAll) {
        std::vector<std::string> algorithms = {"FCFS", "SRTF", "Priority", "RR"};
        for (const auto& algo : algorithms) {
            std::vector<Process> copy = baseProcesses;  // Copy original processes
            std::cout << "\n========== " << algo << " ==========\n";
            scheduler(algo, copy, timeQuantum); // Run scheduler for each algorithm
        }
    } else {
        std::cout << "\n--- Running " << algorithm << " Scheduling ---\n";
        scheduler(algorithm, baseProcesses, timeQuantum); // Run selected scheduler
    }

    return 0;
}
