#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


struct Process {
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    float AvgWaitingTime;
    Process* next;
};

void addProcess(Process*& head, Process*& tail, int burstTime, int arrivalTime, int priority) {
    Process* newProcess = new Process;
    newProcess->burstTime = burstTime;
    newProcess->arrivalTime = arrivalTime;
    newProcess->priority = priority;
    newProcess->next = nullptr;

    if (head == nullptr) {
        head = tail = newProcess;
    } else {
        tail->next = newProcess;
        tail = newProcess;
    }
}

//use this printProcesses function to calculate and get each cpu scheduling method
void printProcesses(const Process* head) {
    const Process* current = head;
        int count=1;
        ofstream outFile("out.txt");
       
    while (current != nullptr) {
               
                
        
     
        cout << "P"<< count<< ":"<<"Burst Time: " << current->burstTime << ", Arrival Time: " << current->arrivalTime
             << ", Priority: " << current->priority << endl; 
            
        //current = current->next;
        outFile<<"P"<< count<< ":"<<"Burst Time: " << current->burstTime << ", Arrival Time: " << current->arrivalTime
             << ", Priority: " << current->priority << endl; 
            
        current = current->next;
         count++;
          
    }
   
     outFile.close();
}


int main()
{



     ifstream inputFile("input.txt");
    if (inputFile.fail()) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    Process* head = nullptr;
    Process* tail = nullptr;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        int burstTime, arrivalTime, priority;
        char colon;

        ss >> burstTime >> colon >> arrivalTime >> colon >> priority;

        addProcess(head, tail, burstTime, arrivalTime, priority);
    }

    inputFile.close();
     
     
    // Output the assigned values
     
     
   



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
        if(subOption1==1){
             cout << "Assigned values: " << endl;
    printProcesses(head);
        }
       //add  printProcesses(head); functions for each scenerio here

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
 // Cleanup: free allocated memory
    while (head != nullptr) {
        Process* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}