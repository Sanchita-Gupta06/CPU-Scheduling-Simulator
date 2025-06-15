#include "process.h"
#include <vector>
#include <queue>
#include <climits>

// Round Robin Algorithm
void calculateTimesRR(std::vector<Process>& processes, std::vector<GanttChartEntry>& gantt_chart, int time_quantum) {
    int n = processes.size(), current_time = 0, completed = 0;
    std::vector<int> remaining_time(n), arrival_time(n), lastExec(n, 0);
    std::queue<int> q;

    for (int i = 0; i < n; ++i) {
        remaining_time[i] = processes[i].burst_time;
        arrival_time[i] = processes[i].arrival_time;
    }

    while (completed != n) {
        for (int i = 0; i < n; ++i)
            if (arrival_time[i] <= current_time && remaining_time[i] > 0) {
                q.push(i);
                arrival_time[i] = INT_MAX;
            }

        if (!q.empty()) {
            int idx = q.front(); q.pop();
            if (remaining_time[idx] > time_quantum) {
                gantt_chart.push_back({processes[idx].pid, current_time, current_time + time_quantum});
                current_time += time_quantum;
                remaining_time[idx] -= time_quantum;

                for (int i = 0; i < n; ++i)
                    if (arrival_time[i] <= current_time && remaining_time[i] > 0 && i != idx) {
                        q.push(i);
                        arrival_time[i] = INT_MAX;
                    }

                q.push(idx);
            } else {
                gantt_chart.push_back({processes[idx].pid, current_time, current_time + remaining_time[idx]});
                current_time += remaining_time[idx];
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                remaining_time[idx] = 0;
                ++completed;
            }
        } else {
            ++current_time;
        }
    }
}
