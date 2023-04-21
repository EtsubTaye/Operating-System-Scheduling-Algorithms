#include "iostream"
#include "vector"
#include "algorithm"
using  namespace std ;
struct Process{
    int Process_Id;
    int Arrival_Time;
    int Burst_Time;
    int Waiting_Time;
    int Turn_Around_Time;
    int Remaining_Time ;

};
void displayMenu() {
    int choice;

    while (true) {
        cout << "Main Menu" << endl;
        cout << "---------" << endl;
        cout << "1. FCFS" << endl;
        cout << "2. SJF_NP" << endl;
        cout << "3. SJF_P" << endl;
        cout << "4. Round Robin" << endl;
        cout << "5. Priority" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Call function for FCFS algorithm
                break;
            case 2:
                // Call function for SJF_NP algorithm
                break;
            case 3:
                // Call function for SJF_P algorithm
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

void welcome (){
    cout << "Welcome to the OS Scheduling Algorithms Model |-- O.S.A.M -- | !\n";
    int choice;
    do {
    cout << "Please select an option:\n";
    cout << "1. Continue\n";
    cout << "2. Exit\n";
    cin >> choice;
    switch (choice){
        case 1:
            displayMenu();
            break;
        case 2:
            cout <<"Exiting O.S.A.M ...."<<endl;
            exit(0);
        default:
            cout<<"Invalid choice . Please try again ." << endl;
    }

    } while (choice != 1);

}

int main (){
   welcome();

}