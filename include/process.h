//process.h
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

// Structure to hold process details
struct Process {
    int pid;               // Process ID
    int arrival_time;      // Time at which process arrives
    int burst_time;        // Total time required by the process
    int remaining_time;    // Time left for execution (used in preemptive scheduling)
    int waiting_time;      // Total time process waits in the queue
    int turnaround_time;   // Total time from arrival to completion
    int completion_time;   // Time at which process finishes execution
    int priority;          // Priority of the process (lower value = higher priority)
    int response_time;     // Time from arrival to first execution
    int start_time;        // First time the process starts execution
};

// Structure to store Gantt chart entries
struct GanttChartEntry {
    int pid;               // Process ID
    int start_time;        // Start time of execution
    int end_time;          // End time of execution
};

// Function to read process data from file
std::vector<Process> getProcessInputFromFile(const std::string& filename);

// Function to get process data from user input
std::vector<Process> getProcessInput();

#endif
