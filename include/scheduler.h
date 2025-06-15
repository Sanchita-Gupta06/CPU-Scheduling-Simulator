#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <vector>
#include <string>

// Runs the selected scheduling algorithm and displays results
void scheduler(const std::string& algorithm, std::vector<Process>& processes, int timeQuantum);

// Automatically selects and runs the best-fit algorithm based on burst time distribution
void auto_schedule(std::vector<Process>& processes, std::vector<GanttChartEntry>& combinedChart, int timeQuantum);

#endif 
