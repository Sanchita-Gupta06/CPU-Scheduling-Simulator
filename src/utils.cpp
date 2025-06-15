#include "process.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

// Sort processes by arrival time → priority → PID
void sorted(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        if (a.arrival_time == b.arrival_time && a.priority == b.priority)
            return a.pid < b.pid;
        else if (a.arrival_time == b.arrival_time)
            return a.priority < b.priority;
        return a.arrival_time < b.arrival_time;
    });
}

// Print the process table with metrics like WT, TT, RT, etc.
void displayProcesses(const std::vector<Process>& processes) {
    int total_wt = 0, total_tt = 0;

    std::cout << "\n--- Process Table ---\n";
    std::cout << std::left
              << std::setw(6) << "PID"
              << std::setw(10) << "Arrival"
              << std::setw(8) << "Burst"
              << std::setw(10) << "Priority"
              << std::setw(10) << "Waiting"
              << std::setw(12) << "Turnaround"
              << std::setw(10) << "Response"
              << std::setw(10) << "Completion" << "\n";

    for (const auto& p : processes) {
        std::cout << std::left
                  << std::setw(6) << p.pid
                  << std::setw(10) << p.arrival_time
                  << std::setw(8) << p.burst_time
                  << std::setw(10) << p.priority
                  << std::setw(10) << p.waiting_time
                  << std::setw(12) << p.turnaround_time
                  << std::setw(10) << p.response_time
                  << std::setw(10) << p.completion_time << "\n";

        total_wt += p.waiting_time;
        total_tt += p.turnaround_time;
    }

    // Print averages
    std::cout << "\nAverage Waiting Time: " << std::fixed << std::setprecision(2)
              << static_cast<float>(total_wt) / processes.size() << "\n";

    std::cout << "Average Turnaround Time: " << std::fixed << std::setprecision(2)
              << static_cast<float>(total_tt) / processes.size() << "\n";
}

// Display Gantt Chart on console
void displayGanttChart(const std::vector<GanttChartEntry>& gantt_chart) {
    std::cout << "\n--- Gantt Chart ---\n ";

    for (const auto& entry : gantt_chart) std::cout << "------";
    std::cout << "\n|";
    for (const auto& entry : gantt_chart) std::cout << "  P" << entry.pid << "  |";
    std::cout << "\n ";
    for (const auto& entry : gantt_chart) std::cout << "------";
    std::cout << "\n0";

    for (const auto& entry : gantt_chart)
        std::cout << std::setw(6) << entry.end_time;
    std::cout << "\n";
}

// Read process data from a text file
std::vector<Process> getProcessInputFromFile(const std::string& filename) {
    std::vector<Process> processes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return {};
    }

    int pid = 1;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int arrival, burst, priority;

        // Read values from a line
        if (ss >> arrival >> burst >> priority) {
            Process p;
            p.pid = pid++;
            p.arrival_time = arrival;
            p.burst_time = burst;
            p.remaining_time = burst;
            p.priority = priority;
            processes.push_back(p);
        }
    }

    file.close();
    return processes;
}

// Take process data from user via console
std::vector<Process> getProcessInput() {
    std::vector<Process> processes;
    int n;

    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        Process p;
        p.pid = i + 1;
        std::cout << "Enter arrival time, burst time, and priority for process " << p.pid << ": ";
        std::cin >> p.arrival_time >> p.burst_time >> p.priority;
        p.remaining_time = p.burst_time;
        processes.push_back(p);
    }

    return processes;
}

// Save scheduling results to a file
void exportOutput(const std::string& algorithm_name, const std::vector<Process>& processes, const std::vector<GanttChartEntry>& gantt_chart, const std::string& filename) {
    std::ofstream out(filename, std::ios::app); // Append to file
    if (!out.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing.\n";
        return;
    }

    // Write header and process table
    out << "\n========== " << algorithm_name << " ==========\n\n";
    out << std::left
        << std::setw(6) << "PID"
        << std::setw(10) << "Arrival"
        << std::setw(8) << "Burst"
        << std::setw(10) << "Priority"
        << std::setw(10) << "Waiting"
        << std::setw(12) << "Turnaround"
        << std::setw(10) << "Response"
        << std::setw(10) << "Completion" << "\n";

    int total_wt = 0, total_tt = 0;
    for (const auto& p : processes) {
        out << std::left
            << std::setw(6) << p.pid
            << std::setw(10) << p.arrival_time
            << std::setw(8) << p.burst_time
            << std::setw(10) << p.priority
            << std::setw(10) << p.waiting_time
            << std::setw(12) << p.turnaround_time
            << std::setw(10) << p.response_time
            << std::setw(10) << p.completion_time << "\n";

        total_wt += p.waiting_time;
        total_tt += p.turnaround_time;
    }

    float avg_wt = static_cast<float>(total_wt) / processes.size();
    float avg_tt = static_cast<float>(total_tt) / processes.size();

    out << "\nAverage Waiting Time: " << std::fixed << std::setprecision(2) << avg_wt << "\n";
    out << "Average Turnaround Time: " << std::fixed << std::setprecision(2) << avg_tt << "\n";

    // Write Gantt Chart
    out << "\nGantt Chart:\n ";
    for (const auto& entry : gantt_chart) out << "------";
    out << "\n|";
    for (const auto& entry : gantt_chart) out << "  P" << entry.pid << "  |";
    out << "\n ";
    for (const auto& entry : gantt_chart) out << "------";
    out << "\n0";
    for (const auto& entry : gantt_chart) out << std::setw(6) << entry.end_time;
    out << "\n";

    out.close();
    std::cout << "\nOutput also saved to: " << filename << "\n";
}
