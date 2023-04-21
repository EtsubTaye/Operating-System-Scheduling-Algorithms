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
void main_menu(){
 cout<<"Main Menu";

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
            main_menu();
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