#include "process.h"
#include <vector>
#include <limits>
#include <algorithm>

// Priority Scheduling - (non-preemptive Priority Scheduling)
void calculateTimesPriority(std::vector<Process>& processes, std::vector<GanttChartEntry>& gantt_chart) {
    int n = processes.size(), current_time = 0;
    std::vector<bool> completed(n, false);
    int completed_count = 0;

    for (auto& p : processes) {
        p.waiting_time = 0;
        p.turnaround_time = 0;
        p.response_time = -1;
        p.completion_time = 0;
        p.remaining_time = p.burst_time;
    }

    while (completed_count < n) {
        int highest_priority = std::numeric_limits<int>::max(), idx = -1;

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival_time <= current_time &&
                processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            // First time executing this process
            if (processes[idx].response_time == -1)
                processes[idx].response_time = current_time - processes[idx].arrival_time;

            int start_time = current_time;
            current_time += processes[idx].burst_time;
            int end_time = current_time;

            processes[idx].completion_time = end_time;
            processes[idx].turnaround_time = end_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;

            completed[idx] = true;
            ++completed_count;

            gantt_chart.push_back({processes[idx].pid, start_time, end_time});
        } else {
            ++current_time;  // CPU is idle
        }
    }
}
