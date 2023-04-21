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
void SJF_P(vector<Process> processes){
    // sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
    { return a.Arrival_Time < b.Arrival_Time; });

    // initialize variables
    int current_time = 0;
    int completed_processes = 0;
    vector<Process> ready_queue;
    Process current_process;

    // loop until all processes are completed
    while (completed_processes < processes.size())
    {
        // add newly arrived processes to the ready queue
        for (int i = 0; i < processes.size(); i++)
        {
            if (processes[i].Arrival_Time <= current_time && processes[i].Remaining_Time > 0)
            {
                bool found = false;
                for (int j = 0; j < ready_queue.size(); j++)
                {
                    if (ready_queue[j].Process_Id == processes[i].Process_Id)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    ready_queue.push_back(processes[i]);
                }
            }
        }

        // select the process with the shortest remaining time from the ready queue
        if (ready_queue.size() > 0)
        {
            sort(ready_queue.begin(), ready_queue.end(), [](const Process &a, const Process &b)
            { return a.Remaining_Time < b.Remaining_Time; });

            // check if the current process should be preempted
            if (current_process.Process_Id != ready_queue[0].Process_Id)
            {
                current_process.Remaining_Time = current_process.Completion_Time - current_time;
                ready_queue.push_back(current_process);}
            current_process = ready_queue[0];
            ready_queue.erase(ready_queue.begin());

            // update waiting time for all processes in the ready queue
            for (int i = 0; i < ready_queue.size(); i++)
            {
                ready_queue[i].Waiting_Time += current_time - ready_queue[i].Completion_Time;
            }
        }

        // execute the current process for 1 time unit
        current_process.Remaining_Time--;
        current_time++;

        // check if the current process is completed
        if (current_process.Remaining_Time == 0)
        {
            current_process.Completion_Time = current_time;
            current_process.Turn_Around_Time = current_process.Completion_Time - current_process.Arrival_Time;
            current_process.Waiting_Time = current_process.Turn_Around_Time - current_process.Burst_Time;
            if (current_process.Waiting_Time < 0)
            {
                current_process.Waiting_Time = 0;
            }
            completed_processes++;
        }
    }

    // calculate average waiting time and turnaround time
    int total_wait_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < processes.size(); i++)
    {
        total_wait_time += processes[i].Waiting_Time;
        total_turnaround_time += processes[i].Turn_Around_Time;
    }
    double avg_wait_time = (double)total_wait_time / processes.size();
    double avg_turnaround_time = (double)total_turnaround_time / processes.size();

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
                cout << "Shortest Job First : Preemptive";
                cout << "Enter the number of processes: ";
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

                SJF_P(processes);
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
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
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