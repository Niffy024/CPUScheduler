#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    cout << "Welcome User, this is CPU Scheduler Simulator.Make sure you already add your input file" << endl;
    cout << "1. Scheduling Method" << endl;
    cout << "2. Preemptive Mode" << endl;
    cout << "3. Show Result" << endl;
    cout << "4. End Program" << endl;
    int option;
    cout << "----------------------Choose your option------------------------- " << endl;
    cin >> option;
    switch ((option))
    {
        // scheduling Mehtod
    case 1:
        
        int subOption1;
        cout << "-----------------1. None--------------------------" << endl;
        cout << "-----------------2. First Come First Serve Scheduling-----------------------------" << endl;
        cout << "-----------------3. Shortest Job First Scheduling(Non Preemptive)------------------" << endl;
        cout << "-----------------4. Priority Scheduling(Non Preemptive)----------------------------" << endl;
        cout << "-----------------5. Round Robin Scheduling--------------------------" << endl;
        cout << "Choose your Sub Option" << endl;
        cin >> subOption1;
        break;
        // Preemptive Method
    case 2:
        
        int subOption2;
        cout << "--------------------1. Shortest Job First Scheduling(Preemptive)------------------------" << endl;
        cout << "--------------------2. Priority Scheduling(Preemptive)----------------------" << endl;
        cout << "Choose your Sub Option" << endl;
        cin >> subOption2;
        break;
        // Show Result
    case 3:
        break;

        // End Program
    case 4:
        cout << "Program is terminated sucessfully";
        break;

    default:
        // cout << "Please choose from the Options listed!!";
        break;
    }

    return 0;
}