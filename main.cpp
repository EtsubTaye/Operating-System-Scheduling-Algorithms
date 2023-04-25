 #include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>

 using namespace std;

// Process struct to store process details
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completion_time;
    int initialBurstTime;
    bool completed;
};
// Comparator struct for priority queue based on process priority

// Comparator struct for sorting processes based on arrival time
struct CompareArrivalTime {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    }
};
// First-Come, First-Served scheduling algorithm
void fcfsScheduling() {
    // Create vector of processes
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        int arrivalTime, burstTime;
        cout << "Enter Arrival time process " << i+1 << ": ";
        cin >> arrivalTime;
        cout<<"Enter Burst time for "<<i+1<<":";
        cin>>burstTime;
        // Initialize process details
        //more on for push
        processes[i] = {i+1, arrivalTime, burstTime, 0, burstTime, 0, 0};
    }

    int currentTime = 0;
    cout << endl << "Process Table: " << endl;
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        currentTime = max(currentTime, processes[i].arrivalTime);
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
        processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
        processes[i].completion_time = currentTime;
        cout << processes[i].id << "\t\t" << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t" << processes[i].completion_time << "\t\t\t"
             << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
    }

    cout << endl << "Gantt Chart: " << endl;
    cout << "+";
    for (int i = 0; i < currentTime; i++) {
        cout << "-";
    }
    cout << "+" << endl;

// Display process IDs and their corresponding time intervals
    cout << "|";
    for (int i = 0; i < n; i++) {
        int processEnd = processes[i].completion_time;
        int processStart = (i == 0) ? 0 : processes[i - 1].completion_time;
        for (int j = processStart; j < processEnd; j++) {
            cout << " ";
        }
        cout << "P" << processes[i].id;
        for (int j = 0; j < processes[i].burstTime - 1; j++) {
            cout << " ";
        }
        cout << "|";
    }
    cout << endl << "+";
    for (int i = 0; i < currentTime; i++) {
        cout << "-";
    }
    cout << "+" << endl;

    // Calculate and display average waiting and turnaround time
    double avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgWaitingTime += processes[i].waitingTime;
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;
    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}
void sjfNPScheduling() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        int burstTime, arrivalTime;
        cout << "Enter arrival time and burst time for process " << i+1 << ": ";
        cin >> arrivalTime >> burstTime;
        processes[i] = {i+1, arrivalTime, burstTime, 0, burstTime, 0, 0};
    }

    sort(processes.begin(), processes.end(), CompareArrivalTime());

    int currentTime = 0;
    double totalWaitTime = 0;
    cout << "Process Table:\n";
    cout << "| PID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time |\n";
    cout << "---------------------------------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        Process p = processes[i];
        totalWaitTime += currentTime - p.arrivalTime;
        currentTime = max(currentTime, p.arrivalTime);
        p.completion_time = currentTime + p.burstTime;
        p.turnaroundTime = p.completion_time - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        currentTime += p.burstTime;
        cout << "| " << setw(3) << p.id << " | " << setw(12) << p.arrivalTime << " | " << setw(9) << p.burstTime << " | "
             << setw(16) << p.completion_time << " | " << setw(12) << p.waitingTime << " | " << setw(15) << p.turnaroundTime << " |\n";
    }
    cout << "---------------------------------------------------------------------------------------\n";
    cout << "Average wait time: " << totalWaitTime/n << endl;

    cout << "Gantt Chart:\n";
    currentTime = 0;
    cout << "| ";
    for (int i = 0; i < n; i++) {
        Process p = processes[i];
        currentTime = max(currentTime, p.arrivalTime);
        while (p.burstTime > 0) {
            cout << setw(3) << p.id << " ";
            p.burstTime--;
            currentTime++;
        }
        cout << "| ";
    }
    cout << endl;

    double avgTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        avgTurnaroundTime += processes[i].turnaroundTime;
    }
    avgTurnaroundTime /= n;
    cout << "Average turnaround time: " << avgTurnaroundTime << endl;
}
void preemptiveSJFScheduling() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        int burstTime, arrivalTime;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> arrivalTime >> burstTime;
        processes[i] = {i + 1, arrivalTime, burstTime, 0, burstTime, 0, 0, false};
    }

     sort(processes.begin(), processes.end(), CompareArrivalTime());

    int currentTime = 0;
    double totalWaitTime = 0;
    int completedProcesses = 0;
    cout << "Process Table:\n";
    cout << "| PID | Arrival Time | Burst Time | Completion Time | Waiting Time | Turnaround Time |\n";
    cout << "---------------------------------------------------------------------------------------\n";
    cout << "Gantt Chart:\n";
    cout << "----------------------------------------------------------------------\n";
    while (completedProcesses < n) {
        int shortestJobIndex = -1;
        int shortestJobBurstTime = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].completed) {
                if (processes[i].burstTime < shortestJobBurstTime) {
                    shortestJobBurstTime = processes[i].burstTime;
                    shortestJobIndex = i;
                }
            }
        }
        if (shortestJobIndex == -1) {
            currentTime++;
            cout << "-";
            continue;
        }
        Process &p = processes[shortestJobIndex];
        p.burstTime--;
        currentTime++;
        cout << "P" << p.id << ".";
        if (p.burstTime == 0) {
            p.completed = true;
            completedProcesses++;
            p.completion_time = currentTime;
            p.turnaroundTime = p.completion_time - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.initialBurstTime;
            totalWaitTime += p.waitingTime;
        }
    }
    cout << endl << "------------------------------------------------------------------\n";
    for (int i = 0; i < n; i++) {
        Process p = processes[i];
        cout << "| " << setw(3) << p.id << " | " << setw(12) << p.arrivalTime << " | " << setw(9) << p.initialBurstTime
             << " | "
             << setw(16) << p.completion_time << " | " << setw(12) << p.waitingTime << " | " << setw(15) << p.turnaroundTime
             << " |\n";
    }
    cout << "---------------------------------------------------------------------------------------\n";
    cout << "Average wait time: " << totalWaitTime / n << endl;
}
void roundRobinScheduling() {
    int n, time_quantum;

    cout << "Enter the number of processes: ";
    cin >> n;

    Process proc[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time for process " << i+1 << ": ";
        cin >> proc[i].arrivalTime;
        cout << "Enter burst time for process " << i+1 << ": ";
        cin >> proc[i].burstTime;
        proc[i].remainingTime = proc[i].burstTime;
    }

    cout << "Enter time quantum: ";
    cin >> time_quantum;

    queue<int> ready_queue;
    int current_time = 0;

    cout << "\nGantt Chart: " << endl;
    cout << "|";

    while (true) {
        bool all_done = true;

        for (int i = 0; i < n; i++) {
            if (proc[i].remainingTime > 0) {
                all_done = false;

                if (proc[i].remainingTime > time_quantum) {
                    current_time += time_quantum;
                    proc[i].remainingTime -= time_quantum;
                    ready_queue.push(i);
                    cout << " P" << i+1 << " |";
                } else {
                    current_time += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    proc[i].completion_time = current_time;
                    proc[i].turnaroundTime = proc[i].completion_time - proc[i].arrivalTime;
                    proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
                    cout << " P" << i+1 << " |";
                }
            }
        }

        if (all_done) {
            break;
        }

        while (!ready_queue.empty()) {
            int i = ready_queue.front();
            ready_queue.pop();

            if (proc[i].remainingTime > 0) {
                if (proc[i].remainingTime > time_quantum) {
                    current_time += time_quantum;
                    proc[i].remainingTime -= time_quantum;
                    ready_queue.push(i);
                    cout << " P" << i+1 << " |";
                } else {
                    current_time += proc[i].remainingTime;
                    proc[i].remainingTime = 0;
                    proc[i].completion_time = current_time;
                    proc[i].turnaroundTime = proc[i].completion_time - proc[i].arrivalTime;
                    proc[i].waitingTime = proc[i].turnaroundTime - proc[i].burstTime;
                    cout << " P" << i+1 << " |";
                }
            }
        }

    }

    cout << endl;

    cout << "\nProcess Table: " << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        cout << "|    P" << i+1 << "   |      " << proc[i].arrivalTime << "      |      " << proc[i].burstTime << "     |        " << proc[i].completion_time << "       |         " << proc[i].turnaroundTime << "        |       " << proc[i].waitingTime << "      |" << endl;
        cout << "------------------------------------------------------------" << endl;
    }
}
void priorityScheduling(){
    int n ;
    cout<<"< Priority Scheduling Algo >"<<endl;
    cout<<"Enter the number of Processes "<<endl;
    cin >> n ;
    Process p[n]; /// the size of the vector
 for (int i = 0 ; i < n ; i++) {
     cout << "Enter the  Id for Process  : " << i + 1 << endl;
     cin >> p[i].id;
     cout << "Enter the Burst time of Process : " << i + 1 << endl;
     cin >> p[i].burstTime;
     cout << "Enter the Priority Tag of Process : " << i + 1 << endl;
     cin >> p[i].priority;
 }
    sort(p, p + n, [](const Process& a, const Process& b) {
        return a.priority < b.priority;
    });
    int current_time = 0;
    cout << "Gant chart: ";
    for (int i = 0; i < n; i++) {
        current_time += p[i].burstTime;
        cout << p[i].id << " ";
    }
    cout << endl;

    double total_waiting_time = 0, total_turnaround_time = 0;
    cout << "Process\tBurst time\tWaiting time\tTurnaround time\n";
    for (int i = 0; i < n; i++) {
        int waiting_time = current_time - p[i].burstTime;
        total_waiting_time += waiting_time;
        total_turnaround_time += waiting_time + p[i].burstTime;
        int turnaround_time = waiting_time + p[i].burstTime;
        cout << p[i].id << "\t" << p[i].burstTime << "\t\t" << waiting_time << "\t\t" << turnaround_time << endl;
    }

    cout << "Average waiting time: " << total_waiting_time / n << endl;
    cout << "Average turnaround time: " << total_turnaround_time / n << endl;

}
void displayProjectInfo() {
     cout << "Welcome to our project!\n\n";
     cout << "Project Members:\n";
     cout << "----------------\n";
     cout << "ID\tFull Name\n";
     cout << "YY6504\tEtsub Yidenkaher\n";
     cout << "EE4321\tKidist Abynehe\n";
     cout << "TT3342\tNoah B\n";
 }
 void Display_Menu(){

        int choice;
        while (true) {
            cout << "Choose a scheduling algorithm:\n";
            cout << "1. First Come First Serve (FCFS)\n";
            cout << "2. Shortest Job First (SJF) - Non-Preemptive\n";
            cout << "3. Shortest Job First (SJF) - Preemptive\n";
            cout << "4. Round Robin (RR)\n";
            cout << "5. Priority Scheduling\n";
            cout << "6. Exit\n";
            cout <<"7. Project Information \n";
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    fcfsScheduling();
                    break;
                case 2:
                    sjfNPScheduling();
                    break;
                case 3:
                    preemptiveSJFScheduling();
                    break;
                case 4:
                    roundRobinScheduling();
                    break;
                case 5:
                    priorityScheduling();
                    break;
                case 6:
                    cout << "Exiting...\n";
                    break;
                case 7:
                     displayProjectInfo();
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
                    break;
            }
        }
    }
int main (){
    Display_Menu();
}