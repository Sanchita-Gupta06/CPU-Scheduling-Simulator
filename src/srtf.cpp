#include "process.h"
#include <vector>
#include <climits>

// Shortest Remaining Time First
void calculateTimesSRTF(std::vector<Process>& processes, std::vector<GanttChartEntry>& gantt_chart) {
    int n = processes.size();
    int current_time = 0, completed = 0, prev = -1;

    for (auto& p : processes) {
        p.remaining_time = p.burst_time;
        p.response_time = -1;
    }

    while (completed != n) {
        int shortest = -1, min_remaining_time = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            ++current_time;
            continue;
        }

        if (processes[shortest].response_time == -1)
            processes[shortest].response_time = current_time - processes[shortest].arrival_time;

        processes[shortest].remaining_time--;
        ++current_time;

        if (processes[shortest].remaining_time == 0) {
            ++completed;
            processes[shortest].completion_time = current_time;
            processes[shortest].waiting_time = processes[shortest].completion_time - 
                                               processes[shortest].arrival_time - 
                                               processes[shortest].burst_time;
            processes[shortest].waiting_time = std::max(0, processes[shortest].waiting_time);
            processes[shortest].turnaround_time = processes[shortest].burst_time + processes[shortest].waiting_time;
            gantt_chart.push_back({processes[shortest].pid, current_time - processes[shortest].burst_time, current_time});
        }
    }
}
