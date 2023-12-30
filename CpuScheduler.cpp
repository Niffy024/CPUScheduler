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

//use this  function to calculate and get each cpu scheduling method
void firstcomefirstserve( Process* head) {
     Process* current = head;
       int currentTime = 0;
        float totalWaitingTime = 0;
         int processCount = 0;
        int count=1;
        ofstream outFile("out.txt");
       cout<<"scheduling Method: First come First Serve"<<endl;
       cout<<"Process Waiting times:"<<endl;

        outFile<<"scheduling Method: First come First Serve"<<endl;
       outFile<<"Process Waiting times:"<<endl;
    while (current != nullptr) {
        // Calculate waiting time
       current->waitingTime = currentTime - current->arrivalTime;  
        currentTime += current->burstTime;
        cout << "Process " << count << ":" << current->waitingTime<<"ms"<< endl;
        outFile << "Process " << count << ":" << current->waitingTime<<"ms"<< endl; 
            count++;
//calculate average waiting time
        totalWaitingTime += current->waitingTime;
        processCount++;
        current = current->next;
        
          
    }

    cout<<"Average Waiting Time:"<<totalWaitingTime / processCount;
    cout<<"ms"<<endl;
    outFile<<"Average Waiting Time:"<<totalWaitingTime / processCount;
    outFile<<"ms"<<endl;
     outFile.close();
}
// shortest jobfirst(Non Preemptive)
// Function to find the process with the shortest burst time
Process* findShortest(Process* start, int currentTime) {
    Process* shortest = nullptr;
    Process* current = start;

    while (current != nullptr && current->arrivalTime <= currentTime) {
        if (shortest == nullptr || current->burstTime < shortest->burstTime) {
            shortest = current;
        }
        current = current->next;
    }

    return shortest;
}

// Shortest Job First (Non Preemptive)
void shortestJobFirstNonPreemptive(Process* head) {
    Process* current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    ofstream outFile("out.txt");
    cout << "Scheduling Method: Shortest Job First (Non Preemptive)" << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Shortest Job First (Non Preemptive)" << endl;
    outFile << "Process Waiting times:" << endl;

    while (current != nullptr) {
        // Find the process with the shortest burst time
        Process* shortest = findShortest(current, currentTime);

        if (shortest != nullptr) {
            // Execute the shortest process
            shortest->waitingTime = currentTime - shortest->arrivalTime;
            currentTime += shortest->burstTime;

            cout << "Process " << count << ": " << shortest->waitingTime << "ms" << endl;
            outFile << "Process " << count << ": " << shortest->waitingTime << "ms" << endl;

            totalWaitingTime += shortest->waitingTime;
            processCount++;
            count++;

            // Remove the executed process from the list
        // Remove the executed process from the list
if (current == shortest) {
    current = current->next;
    head = current;
} else {
    Process* temp = current;
    while (temp->next != shortest) {
        temp = temp->next;
    }
    temp->next = shortest->next;
}


            delete shortest;
        } else {
            currentTime++;
        }
    }

    cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;

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
            //if user choose none as their option, automactically use first come first serve!!!!
            firstcomefirstserve(head);
        }
        else if(subOption1==2){
             
            firstcomefirstserve(head);
        } 
        else if(subOption1==3){

                 shortestJobFirstNonPreemptive(head);

        }
       

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