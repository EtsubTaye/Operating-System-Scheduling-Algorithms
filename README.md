

# OS Scheduling Algorithms

This is a C++ program that implements four different operating system scheduling algorithms: First Come First Serve (FCFS), Shortest Job First (SJF), Non-preemptive SJF, Round Robin (RR), and Priority.

## Getting Started

To use this program, simply compile and run the 'main.cpp' file using a C++ compiler. The program will prompt the user to enter the number of processes to be scheduled, as well as the scheduling algorithm they would like to use.

## Algorithms

### First Come First Serve (FCFS)

This algorithm schedules processes in the order in which they arrive. The first process to arrive will be scheduled first, followed by the second process, and so on.

### Shortest Job First (SJF)

This algorithm schedules processes based on their CPU burst time, with the shortest job being scheduled first. If multiple jobs have the same burst time, the algorithm will choose the job that arrived first.

### Non-preemptive SJF

This is a variant of the SJF algorithm where once a process has been scheduled, it cannot be preempted by another process with a shorter CPU burst time.

### Round Robin (RR)

This algorithm schedules processes by assigning them a fixed time slice, or quantum, during which they can execute. Once the quantum expires, the process is preempted and moved to the back of the scheduling queue.

### Priority

This algorithm schedules processes based on their priority level, with higher priority processes being scheduled first. If multiple jobs have the same priority, the algorithm will choose the job that arrived first.

## Output

After the user selects a scheduling algorithm, the program will generate a random process table with the specified number of processes and display the results of the scheduling algorithm in the form of a Gantt chart.

## License

This project is licensed under the MIT License - see the LICENSE file for details.
