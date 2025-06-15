# CPU Scheduling Simulator

A  CPU Scheduling Simulator in C++ that supports multiple scheduling algorithms: FCFS, SRTF, Priority, and Round Robin. It features a CLI interface for manual or file-based input, displays detailed process metrics, Gantt charts, and includes an Auto mode to select the best algorithm based on burst time patterns.

---

## Introduction

CPU Scheduling is a key part of how operating systems manage multiple running programs. It decides which process should use the CPU next. Good scheduling helps make the system run smoothly and respond quickly.

This simulator shows how different CPU scheduling algorithms work and lets you compare their performance. It's useful for learning, testing different process setups, or understanding how scheduling affects program execution.

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
