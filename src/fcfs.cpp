#include "process.h"
#include <vector>

// First Come First Serve
void calculateTimesFCFS(std::vector<Process>& processes, std::vector<GanttChartEntry>& gantt_chart) {
    int current_time = 0;
    bool is_first_process = true;
    for (auto& process : processes) {
        if (is_first_process) {
            current_time = process.arrival_time;
            is_first_process = false;
        } else if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        GanttChartEntry entry = {process.pid, current_time, current_time + process.burst_time};
        gantt_chart.push_back(entry);

        process.waiting_time = current_time - process.arrival_time;
        process.turnaround_time = process.waiting_time + process.burst_time;
        process.completion_time = current_time + process.burst_time;
        current_time += process.burst_time;
        process.response_time = process.waiting_time;
    }
}
