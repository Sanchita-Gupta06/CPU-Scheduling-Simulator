#include "process.h"
#include "utils.h"
#include <vector>
#include <string>
#include <iostream> 
#include <cmath> 
#include <fstream>

// Forward declarations for scheduling algorithms
void calculateTimesFCFS(std::vector<Process>&, std::vector<GanttChartEntry>&);
void calculateTimesSRTF(std::vector<Process>&, std::vector<GanttChartEntry>&);
void calculateTimesPriority(std::vector<Process>&, std::vector<GanttChartEntry>&);
void calculateTimesRR(std::vector<Process>&, std::vector<GanttChartEntry>&, int);

// Utility functions
void sorted(std::vector<Process>&);
void displayProcesses(const std::vector<Process>&);
void displayGanttChart(const std::vector<GanttChartEntry>&);

// Auto scheduling logic to select best algorithm based on burst time pattern
void auto_schedule(std::vector<Process>& processes, std::vector<GanttChartEntry>& gantt_chart, int tq) {
    double sum = 0, N = processes.size(), mean, stddev = 0;

    // Calculate average burst time
    for (auto& p : processes) sum += p.burst_time;
    mean = sum / N;

    // Calculate standard deviation of burst times
    for (auto& p : processes)
        stddev += (p.burst_time - mean) * (p.burst_time - mean);
    stddev = sqrt(stddev / N);

    // Choose algorithm based on burst time pattern
    if (stddev < mean / 2.0)
        calculateTimesFCFS(processes, gantt_chart); // Low variation: use FCFS
    else if (N > 7)
        calculateTimesRR(processes, gantt_chart, tq); // More processes: use RR
    else
        calculateTimesSRTF(processes, gantt_chart); // Default: use SRTF
}

// Main scheduler function that dispatches based on selected algorithm
void scheduler(const std::string& algo, std::vector<Process>& processes, int tq = 1) {
    sorted(processes); // Sort by arrival time
    std::vector<GanttChartEntry> gantt_chart;
    std::string full_algo_name;

    // Choose and run appropriate algorithm
    if (algo == "FCFS") {
        calculateTimesFCFS(processes, gantt_chart);
        full_algo_name = "First Come First Serve (FCFS)";
    } else if (algo == "SRTF") {
        calculateTimesSRTF(processes, gantt_chart);
        full_algo_name = "Shortest Remaining Time First (SRTF)";
    } else if (algo == "Priority") {
        calculateTimesPriority(processes, gantt_chart);
        full_algo_name = "Priority Scheduling";
    } else if (algo == "RR") {
        calculateTimesRR(processes, gantt_chart, tq);
        full_algo_name = "Round Robin (RR)";
    } else if (algo == "auto") {
        auto_schedule(processes, gantt_chart, tq);
        full_algo_name = "Adaptive Scheduling (Auto)";
    } else {
        std::cout << "Invalid scheduling algorithm.\n";
        return;
    }

    // Display and save results
    displayProcesses(processes);
    displayGanttChart(gantt_chart);
    exportOutput(full_algo_name, processes, gantt_chart, "output.txt");
}
