#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

struct Process
{
    int Process_Id;
    int Arrival_Time;
    int Burst_Time;
    int Waiting_Time;
    int Turn_Around_Time;
    int Remaining_Time;
    int Completion_Time;
};

void FCFS(vector<Process> processes)
{
    // sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
    { return a.Arrival_Time < b.Arrival_Time; });

    // calculate waiting time, turnaround time, and completion time for each process
    int total_wait_time = 0, total_turnaround_time = 0, current_time = 0;
    for (int i = 0; i < processes.size(); i++)
    {
        if (current_time < processes[i].Arrival_Time)
        {
            current_time = processes[i].Arrival_Time;
        }
        processes[i].Completion_Time = current_time + processes[i].Burst_Time;
        processes[i].Turn_Around_Time = processes[i].Completion_Time - processes[i].Arrival_Time;
        processes[i].Waiting_Time = processes[i].Turn_Around_Time - processes[i].Burst_Time;
        if (processes[i].Waiting_Time < 0)
        {
            processes[i].Waiting_Time = 0;
        }
        current_time = processes[i].Completion_Time;
        total_wait_time += processes[i].Waiting_Time;
        total_turnaround_time += processes[i].Turn_Around_Time;
    }

    // calculate average waiting time and turnaround time
    double avg_wait_time = (double)total_wait_time / processes.size();
    double avg_turnaround_time = (double)total_turnaround_time / processes.size();

    // display process table
    cout << "+-----+--------------+------------+------------------+---------------------+---------------------+" << endl;
    cout << "| PID | Arrival Time | Burst Time | Waiting Time (ms) | Turnaround Time (ms) | Completion Time (ms) |" << endl;
    cout << "+-----+--------------+------------+------------------+---------------------+---------------------+" << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        printf("| %-3d |      %-7d |     %-6d |        %-9d |          %-11d |          %-11d |\n",
               processes[i].Process_Id, processes[i].Arrival_Time, processes[i].Burst_Time,
               processes[i].Waiting_Time, processes[i].Turn_Around_Time, processes[i].Completion_Time);
    }
    cout << "+-----+--------------+------------+------------------+---------------------+---------------------+" << endl;

    // display Gantt chart
    cout << "Gantt Chart:" << endl;
    cout << "+";
    for (int i = 0; i < processes[0].Arrival_Time; i++)
    {
        cout << "---+";
    }
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "---+";
        for (int j = 0; j < processes[i].Burst_Time; j++)
        {
            cout << " " << processes[i].Process_Id << " |";
        }
    }
    cout << endl;

    // display average waiting time and turnaround time
    cout << "Average waiting time: " << avg_wait_time << " ms" << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << " ms" << endl;
}
void SJF_NP(vector<Process> processes)
{
    // sort processes by arrival time and then by burst time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
    {
        if (a.Arrival_Time == b.Arrival_Time) {
            return a.Burst_Time < b.Burst_Time;
        }
        return a.Arrival_Time < b.Arrival_Time; });

    // calculate waiting time, turnaround time, and completion time for each process
    int total_wait_time = 0, total_turnaround_time = 0, current_time = 0;
    for (int i = 0; i < processes.size(); i++)
    {
        if (current_time < processes[i].Arrival_Time)
        {
            current_time = processes[i].Arrival_Time;
        }
        processes[i].Completion_Time = current_time + processes[i].Burst_Time;
        processes[i].Turn_Around_Time = processes[i].Completion_Time - processes[i].Arrival_Time;
        processes[i].Waiting_Time = processes[i].Turn_Around_Time - processes[i].Burst_Time;
        if (processes[i].Waiting_Time < 0)
        {
            processes[i].Waiting_Time = 0;
        }
        current_time = processes[i].Completion_Time;
        total_wait_time += processes[i].Waiting_Time;
        total_turnaround_time += processes[i].Turn_Around_Time;
    }

    // calculate average waiting time and turnaround time
    double avg_wait_time = (double)total_wait_time / processes.size();
    double avg_turnaround_time = (double)total_turnaround_time / processes.size();

    // display process table
    cout << "+-----+--------------+------------+------------------+---------------------+---------------------+" << endl;
    cout << "| PID | Arrival Time | Burst Time | Waiting Time (ms) | Turnaround Time (ms) | Completion Time (ms) |" << endl;
    cout << "+-----+--------------+------------+------------------+---------------------+---------------------+" << endl;
    for (int i = 0; i < processes.size(); i++)
    {
        printf("| %-3d |      %-7d |     %-6d |        %-9d |          %-11d |          %-11d |\n",
               processes[i].Process_Id, processes[i].Arrival_Time, processes[i].Burst_Time,
               processes[i].Waiting_Time, processes[i].Turn_Around_Time, processes[i].Completion_Time);
    }
    cout << "+-----+--------------+------------+------------------+---------------------+---------------------+" << endl;

    // display Gantt chart
    cout << "Gantt Chart:" << endl;
    cout << "+";
    for (int i = 0; i < processes[0].Arrival_Time; i++)
    {
        cout << "---+";
    }
    for (int i = 0; i < processes.size(); i++)
    {
        cout << "---+";
        for (int j = 0; j < processes[i].Burst_Time; j++)
        {
            cout << " " << processes[i].Process_Id << " |";
        }
    }
    cout << endl;

    // display average waiting time and turnaround time
    cout << "Average waiting time: " << avg_wait_time << " ms" << endl;
    cout << "Average turnaround time: " << avg_turnaround_time << " ms" << endl;
}
void SJF_P(vector<Process>& processes)  {
        // sort processes by arrival time and then by burst time
        sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
            if (a.Arrival_Time == b.Arrival_Time) {
                return a.Burst_Time < b.Burst_Time;
            }
            return a.Arrival_Time < b.Arrival_Time;
        });

        // calculate waiting time, turnaround time, and completion time for each process
        int total_wait_time = 0, total_turnaround_time = 0, current_time = 0, min_burst_time;
        vector<int> remaining_burst_time(processes.size(), 0);
        for (int i = 0; i < processes.size(); i++) {
            remaining_burst_time[i] = processes[i].Burst_Time;
        }

        vector<int> completion_time(processes.size(), 0), start_time(processes.size(), 0);
        int completed = 0;
        while (completed != processes.size()) {
            min_burst_time = INT_MAX;
            int min_index = -1;
            for (int i = 0; i < processes.size(); i++) {
                if (remaining_burst_time[i] > 0 && remaining_burst_time[i] < min_burst_time &&
                    processes[i].Arrival_Time <= current_time) {
                    min_burst_time = remaining_burst_time[i];
                    min_index = i;
                }
            }
            if (min_index == -1) {
                current_time++;
                continue;
            }
            remaining_burst_time[min_index]--;

            if (remaining_burst_time[min_index] == 0) {
                completed++;
                completion_time[min_index] = current_time + 1;
                processes[min_index].Turn_Around_Time = completion_time[min_index] - processes[min_index].Arrival_Time;
                processes[min_index].Waiting_Time =
                        processes[min_index].Turn_Around_Time - processes[min_index].Burst_Time;
                if (processes[min_index].Waiting_Time < 0) {
                    processes[min_index].Waiting_Time = 0;
                }
                total_wait_time += processes[min_index].Waiting_Time;
                total_turnaround_time += processes[min_index].Turn_Around_Time;
            }
            current_time++;
            start_time[min_index] = current_time - remaining_burst_time[min_index];
        }

        // calculate average waiting time and turnaround time
        double avg_wait_time = (double) total_wait_time / processes.size();
        double avg_turnaround_time = (double) total_turnaround_time / processes.size();

        // display process table
        cout << "+-----+--------------+------------+------------------+---------------------+---------------------+"
             << endl;
        cout << "| PID | Arrival Time | Burst Time | Waiting Time (ms) | Turnaround Time (ms) | Completion Time (ms) |"
             << endl;
        cout << "+-----+--------------+------------+------------------+---------------------+---------------------+"
             << endl;
        for (int i = 0; i < processes.size(); i++) {
            printf("| %-3d |      %-7d |     %-6d |        %-9d |          %-11d |          %-11d |\n",
                   processes[i].Process_Id, processes[i].Arrival_Time, processes[i].Burst_Time,
                   processes[i].Waiting_Time, processes[i].Turn_Around_Time, completion_time[i]);
        }
        cout << "+-----+--------------+------------+------------------+---------------------+---------------------+"<< endl;


        // display Gantt chart
        cout << "Gantt Chart:" << endl;
        cout << "+";
        for (int i = 0; i < processes[0].Arrival_Time; i++) {
            cout << "---+";
        }
        for (int i = 0; i < processes.size(); i++) {
            cout << "---+";
            for (int j = 0; j < processes[i].Burst_Time; j++) {
                cout << " " << processes[i].Process_Id << " |";
            }
        }
        cout << endl;

        // display average waiting time and turnaround time
        cout << "Average waiting time: " << avg_wait_time << " ms" << endl;
        cout << "Average turnaround time: " << avg_turnaround_time << " ms" << endl;
    }


void displayMenu()
{
    int choice;
    vector<Process> processes;
    while (true)
    {
        cout << "|-- O.S.A.M -- |" << endl;
        cout << "--------------------1" << endl;
        cout << "SELECT YOUR ALGO" << endl;
        cout << "1. FCFS" << endl;
        cout << "2. SJF_NP" << endl;
        cout << "3. SJF_P" << endl;
        cout << "4. Round Robin" << endl;
        cout << "5. Priority" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                // read the number of processes from user
                int num_processes;
                cout << "First Come First Serve";
                cout << "Enter the number of processes: ";
                cin >> num_processes;

                // read process details from user and store them in the processes vector
                for (int i = 0; i < num_processes; i++)
                {
                    Process p;
                    p.Process_Id = i + 1;

                    cout << "Enter the arrival time of process " << p.Process_Id << ": ";
                    cin >> p.Arrival_Time;

                    cout << "Enter the burst time of process " << p.Process_Id << ": ";
                    cin >> p.Burst_Time;

                    p.Remaining_Time = p.Burst_Time;

                    processes.push_back(p);
                }

                FCFS(processes); //call the FCFS function here
                break;
            case 2:
                cout << "Shortest Job First :NON_Preemptive";
                cout << "Enter the number of processes: ";
                cin >> num_processes;

                // read process details from user and store them in the processes vector
                for (int i = 0; i < num_processes; i++)
                {
                    Process p;
                    p.Process_Id = i + 1;

                    cout << "Enter the arrival time of process " << p.Process_Id << ": ";
                    cin >> p.Arrival_Time;

                    cout << "Enter the burst time of process " << p.Process_Id << ": ";
                    cin >> p.Burst_Time;

                    p.Remaining_Time = p.Burst_Time;

                    processes.push_back(p);
                }

                SJF_NP(processes);
                break;

            case 3:
                cout << "Shortest Job First : Preemptive" << endl;
                cout << "Enter the number of processes : ";
                cin >> num_processes;
                for (int i = 0 ; i < num_processes ;i++){
                    Process p;
                    p.Process_Id = i + 1;

                    cout << "Enter the arrival time of process " << p.Process_Id << ": ";
                    cin >> p.Arrival_Time;

                    cout << "Enter the burst time of process " << p.Process_Id << ": ";
                    cin >> p.Burst_Time;

                    p.Remaining_Time = p.Burst_Time;

                    processes.push_back(p);
                }
                // Call the SJF_P() function here
                SJF_P(processes);

            default:
                cout << "Invalid choice" << endl;
                break;
            case 4:
                // Call function for Round Robin algorithm
                break;
            case 5:
                // Call function for Priority algorithm
                break;
            case 6:
                // Exit program
                exit(0);

               // cout << "Invalid choice. Please try again." << endl;
              //  break;
        }
    }
}

void welcome()
{
    cout << "Welcome to the OS Scheduling Algorithms Model |-- O.S.A.M -- | !\n";
    int choice;
    do
    {
        cout << "Please select an option:\n";
        cout << "1. Continue\n";
        cout << "2. Exit\n";
        cin >> choice;
        switch (choice)
        {
            case 1:
                displayMenu();
                break;
            case 2:
                cout << "Exiting O.S.A.M ...." << endl;
                exit(0);
            default:
                cout << "Invalid choice . Please try again ." << endl;
        }

    } while (choice != 1);
}

int main()
{
    welcome();
    return 0;
}