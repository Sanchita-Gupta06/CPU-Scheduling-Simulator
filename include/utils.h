#ifndef UTILS_H
#define UTILS_H

#include "process.h"
#include <vector>
#include <string>

// Gets process data manually from user input
std::vector<Process> getProcessInput();

// Loads process data from a file
std::vector<Process> getProcessInputFromFile(const std::string& filename);

// Sorts processes by arrival time, then priority, then PID
void sorted(std::vector<Process>& processes);

// Displays the process table with calculated times
void displayProcesses(const std::vector<Process>& processes);

// Displays the Gantt chart in terminal
void displayGanttChart(const std::vector<GanttChartEntry>& gantt_chart);

// Exports results and Gantt chart to a text file
void exportOutput(const std::string& algorithm_name, const std::vector<Process>& processes, const std::vector<GanttChartEntry>& gantt_chart, const std::string& filename);

#endif 
