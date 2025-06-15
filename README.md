# CPU Scheduling Simulator

A complete CPU Scheduling Simulator written in C++ that implements multiple CPU scheduling algorithms. The simulator can run FCFS, SRTF, Priority Scheduling, and Round Robin, and allows users to compare scheduling strategies on various performance metrics. It also includes an automatic scheduling mode that selects the most suitable algorithm based on process burst times and supports CLI-based interactive input.

---

## Introduction

CPU Scheduling is a core operating system concept that decides which of the ready processes gets the CPU. Efficient scheduling improves system throughput, CPU utilization, and responsiveness.

This simulator helps visualize and compare the behavior and efficiency of different algorithms under a variety of input conditions. It is ideal for OS education, benchmarking, or systems experimentation.

---

## Features

- First-Come, First-Serve (FCFS): Simple scheduling based on arrival time.  
- Shortest Remaining Time First (SRTF): Preemptive algorithm that always chooses the process with the least time left.  
- Priority Scheduling: Non-preemptive; executes the process with the highest priority (lowest number).  
- Round Robin (RR): Each process gets a fixed time quantum cyclically.  
- Auto Scheduler: Uses standard deviation of burst times to select the most efficient algorithm.  
- Compare All Mode: Executes and compares all algorithms on the same input.  
- File and Manual Input Support: Choose between interactive or file-based inputs.  
- Gantt Chart Display: Visual representation of process execution order.  
- Performance Metrics: Includes waiting time, turnaround time, response time, and completion time.  
- Output Logging: Final results saved to `output.txt` for every run.

---

## Getting Started

### Prerequisites

- A C++ compiler like `g++`
- Works on Windows, Linux, or macOS

### 1. Clone the Repository

```bash
git clone https://github.com/Sanchita-Gupta06/CPU-Scheduling-Simulator.git
cd CPU-Scheduling-Simulator
```

### 2. Compile the Program

```bash
g++ main.cpp fcfs.cpp srtf.cpp priority.cpp rr.cpp auto_scheduler.cpp utils.cpp -o scheduler
or g++ -std=c++17 -Iinclude src/*.cpp -o scheduler
```

### 3. Run the Program

```bash
./scheduler
```

---

## Usage

### Step-by-Step Execution

1. **Start the Simulator**

   ```bash
   ./scheduler
   ```

2. **Select Scheduling Algorithm**

   ```
   --- Select Scheduling Algorithm ---

   1. FCFS
   2. SRTF
   3. Priority
   4. Round Robin
   5. Auto (Best Fit)
   6. Run All Algorithms & Compare
   ```

3. **Select Input Method**

   ```
   --- Select Input Method ---

   1. Manual Entry
   2. Load from File
   ```

4. **If File Input is Selected**

   ```
   Enter input filename (e.g., input.txt): input.txt
   ```

   File Format (one process per line):

   ```
   ArrivalTime BurstTime Priority
   ```

   Example:

   ```
   0 5 2
   1 3 1
   2 8 3
   ```

5. **If Using Round Robin (RR)**

   ```
   Enter time quantum: 5
   ```

---

## Example Output

For `Compare All` option with file input:

```
=====================
 CPU Scheduling Simulator
=====================

--- Select Scheduling Algorithm ---
6

--- Select Input Method ---
2

Enter input filename: input.txt
Enter time quantum: 5
```

### Output Snippet

```
========== FCFS ==========
--- Process Table ---
PID   Arrival   Burst   Priority  Waiting   Turnaround  Response  Completion
1     0         20      3         0         20          0         20
2     1         2       1         19        21          19        22
3     2         3       2         20        23          20        25

Average Waiting Time: 13.00
Average Turnaround Time: 21.33

--- Gantt Chart ---
 ------------------
|  P1  |  P2  |  P3  |
 ------------------
0      20     22     25

Output also saved to: output.txt
```

(Similar outputs for SRTF, Priority, and RR)

---

## Further Improvements

- Add preemptive version of Priority Scheduling  
- GUI interface using Qt or web technologies  
- Export Gantt chart as image or PDF  

---