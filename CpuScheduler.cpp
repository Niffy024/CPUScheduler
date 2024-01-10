#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
const int QUANTUM = 4;



struct Process {

    int processID;
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    float AvgWaitingTime;
    Process* next;
};
Process* front = nullptr;
Process* rear = nullptr;
void addProcess(Process*& head, Process*& tail, int burstTime, int arrivalTime, int priority) {
    Process* newProcess = new Process;
    newProcess->processID = (tail != nullptr) ? tail->processID + 1 : 1; // Increment process ID
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

//first come first serve method
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
        //  waiting time
       current->waitingTime = currentTime - current->arrivalTime;  
        currentTime += current->burstTime;
        cout << "Process " << count << ":" << current->waitingTime<<"ms"<< endl;
        outFile << "Process " << count << ":" << current->waitingTime<<"ms"<< endl; 
            count++;
// average waiting time
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
        if (shortest == nullptr || current->burstTime < shortest->burstTime 
        || (current->burstTime == shortest->burstTime && current->arrivalTime<shortest->arrivalTime)) {
            shortest = current;
        }
        current = current->next;
    }

    return shortest;
}

// Shortest Job First (Non Preemptive)
void shortestJobFirstNonPreemptive(Process*& head) {
    Process* current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
     ofstream outFile("out.txt");

    // Array to store waiting times
    int* waitingTimesArray = new int[count];

    cout << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;

    outFile << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;
   

    while (current != nullptr) {
        // Find the process with the shortest burst time
        Process* shortest = findShortest(current, currentTime);

        if (shortest != nullptr) {
            // Execute the shortest process
            shortest->waitingTime = currentTime - shortest->arrivalTime;
            currentTime += shortest->burstTime;

            // Store waiting time in the array
            waitingTimesArray[shortest->processID - 1] = shortest->waitingTime;

            totalWaitingTime += shortest->waitingTime;
            processCount++;
            count++;

            // Remove the executed process from the list
            if (current == shortest) {
                head = current->next;
            } else {
                Process* temp = head;
                while (temp->next != shortest) {
                    temp = temp->next;
                }
                temp->next = shortest->next;
            }

            delete shortest;
        } else {
            currentTime++;
        }

        // Update the current pointer to head
        current = head;
    }

    // Display process waiting times in order
    cout << "Process Waiting times:" << endl;
     outFile << "Process Waiting times:" << endl;
    for (int i = 0; i < processCount; i++) {
        cout << "Process " << (i + 1) << ": " << waitingTimesArray[i] << "ms" << endl;
         outFile << "Process " << (i + 1) << ": " << waitingTimesArray[i] << "ms" << endl;
    }

    // Calculate and display average waiting time
    cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
     outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;

    // Clean up memory
    delete[] waitingTimesArray;
}




// prioroty scheduling (non preemptive)
void prioritySchedulingNonPreemptive(Process* &head) {
    Process* current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    
    ofstream outFile("out.txt");

    cout << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;
    outFile << "Process Waiting times:" << endl;

    while (current != nullptr) {
        // Find the process with the highest priority
        Process* highestPriority = nullptr;
        Process* temp = current;

        while (temp != nullptr && temp->arrivalTime <= currentTime) {
            if (highestPriority == nullptr || temp->priority < highestPriority->priority) {
                highestPriority = temp;
            }
            temp = temp->next;
        }

        if (highestPriority != nullptr) {
            // Execute the process with the highest priority
            highestPriority->waitingTime = currentTime - highestPriority->arrivalTime;
            currentTime += highestPriority->burstTime;

            cout << "Process " << highestPriority->processID << ": " << highestPriority->waitingTime << "ms" << endl;
            outFile << "Process " << highestPriority->processID << ": " << highestPriority->waitingTime << "ms" << endl;

            totalWaitingTime += highestPriority->waitingTime;
            processCount++;
            

            // Remove the executed process from the list
            if (current == highestPriority) {
                current = current->next;
                head = current;
            } else {
                Process* temp = current;
                Process* prev = nullptr;

                while (temp != nullptr && temp != highestPriority) {
                    prev = temp;
                    temp = temp->next;
                }

                if (temp != nullptr) {
                    prev->next = temp->next;
                }
            }

            delete highestPriority;
        } else {
            currentTime++;
        }
    } 
        cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
        outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;

    outFile.close();
}

// Dequeue a process from the front of the queue
Process* dequeue(Process*& front, Process*& rear) {
    if (front == nullptr) {
        return nullptr;
    }

    Process* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    return temp;
}

// Round Robin Scheduling
void roundRobinScheduling(Process* head) {
   
    Process* current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    int quantum=2;
    ofstream outFile("out.txt");

    cout << "Scheduling Method: Round Robin" << endl;
    cout << "Quantum: " << quantum  << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Round Robin" << endl;
    outFile << "Quantum: " << quantum  << endl;
    outFile << "Process Waiting times:" << endl;

    while (current != nullptr || front != nullptr) {
        // Enqueue processes that have arrived
        while (current != nullptr && current->arrivalTime <= currentTime) {
            addProcess(front, rear, current->burstTime, current->arrivalTime, current->priority);
            current = current->next;
        }

        // Dequeue and execute processes
        if (front != nullptr) {
            Process* currentProcess = dequeue(front, rear);

            int remainingTime = min(quantum, currentProcess->burstTime);
            currentProcess->burstTime -= remainingTime;

            // Calculate waiting time
            currentProcess->waitingTime = currentTime - currentProcess->arrivalTime;
            currentTime += remainingTime;

            // Enqueue back if burst time is remaining
            if (currentProcess->burstTime > 0) {
                addProcess(front, rear, currentProcess->burstTime, currentProcess->arrivalTime, currentProcess->priority);
            } else {
                // Process is completed
                cout << "Process " << count << ": " << currentProcess->waitingTime << "ms" << endl;
                outFile << "Process " << count << ": " << currentProcess->waitingTime << "ms" << endl;

                totalWaitingTime += currentProcess->waitingTime;
                processCount++;
                count++;
            }

            delete currentProcess;
        } else {
            currentTime++;
        }
    }

    if (processCount > 0) {
        cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
        outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    } else {
        cout << "No processes executed." << endl;
        outFile << "No processes executed." << endl;
    }

    outFile.close();
}

// ... (existing code)

// Function to find the process with the shortest remaining burst time
// Function to find the process with the shortest remaining burst time
Process* findShortestRemaining(Process* start, int currentTime) {
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

void shortestJobFirstPreemptive(Process* head) {
    Process* current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    ofstream outFile("out.txt");

    cout << "Scheduling Method: Shortest Job First (Preemptive)" << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Shortest Job First (Preemptive)" << endl;
    outFile << "Process Waiting times:" << endl;

    while (current != nullptr) {
        Process* shortest = findShortestRemaining(current, currentTime);

        if (shortest != nullptr) {
            int remainingTime = min(QUANTUM, shortest->burstTime);
            shortest->burstTime -= remainingTime;

            shortest->waitingTime = currentTime - shortest->arrivalTime;
            currentTime += remainingTime;

            cout << "Process " << count << ": " << shortest->waitingTime << "ms" << endl;
            outFile << "Process " << count << ": " << shortest->waitingTime << "ms" << endl;

            totalWaitingTime += shortest->waitingTime;
            processCount++;
            count++;

            if (shortest->burstTime <= 0) {
                // Remove the executed process from the list
                Process* temp = current;
                if (current == shortest) {
                    current = current->next;
                    head = current;
                } else {
                    while (temp->next != shortest) {
                        temp = temp->next;
                    }
                    temp->next = shortest->next;
                }

                delete shortest;
            }
        } else {
            currentTime++;
        }
    }

    if (processCount > 0) {
        cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
        outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    } else {
        cout << "No processes executed." << endl;
        outFile << "No processes executed." << endl;
    }

    outFile.close();
}


// Priority Scheduling (Preemptive)
void prioritySchedulingPreemptive(Process* head) {
    Process* current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    ofstream outFile("out.txt");

    cout << "Scheduling Method: Priority Scheduling (Preemptive)" << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Priority Scheduling (Preemptive)" << endl;
    outFile << "Process Waiting times:" << endl;

    while (current != nullptr) {
        // Find the process with the highest priority
        Process* highestPriority = nullptr;
        Process* temp = current;

        while (temp != nullptr && temp->arrivalTime <= currentTime) {
            if (highestPriority == nullptr || temp->priority < highestPriority->priority) {
                highestPriority = temp;
            }
            temp = temp->next;
        }

        if (highestPriority != nullptr) {
            // Execute the process for a quantum or until it completes
            int remainingTime = min(QUANTUM, highestPriority->burstTime);
            highestPriority->burstTime -= remainingTime;

            // Calculate waiting time
            highestPriority->waitingTime = currentTime - highestPriority->arrivalTime;
            currentTime += remainingTime;

            cout << "Process " << count << ": " << highestPriority->waitingTime << "ms" << endl;
            outFile << "Process " << count << ": " << highestPriority->waitingTime << "ms" << endl;

            totalWaitingTime += highestPriority->waitingTime;
            processCount++;
            count++;

            // Move to the next process
            current = (highestPriority->burstTime > 0) ? current : current->next;

            // Remove the executed process from the list
            if (highestPriority->burstTime <= 0) {
                delete highestPriority;
            }
        } else {
            currentTime++;
        }
    }

    if (processCount > 0) {
        cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
        outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    } else {
        cout << "No processes executed." << endl;
        outFile << "No processes executed." << endl;
    }

    outFile.close();
}

// ... (existing code)




// Function to display results
void showResults() {
    // Implement the logic to display the results here
    // You can read the "out.txt" file and print the results
    // This function should display the results based on the user's selection
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
//get the burstTime, arrivalTime and Priority from the input file
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int burstTime, arrivalTime, priority;
        char colon;

        ss >> burstTime >> colon >> arrivalTime >> colon >> priority;

        addProcess(head, tail, burstTime, arrivalTime, priority);
    }

    inputFile.close();
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
        else if(subOption1==4){
            prioritySchedulingNonPreemptive(head);
        }
       

        break;
        // Preemptive Method
    case 2:
        
        int subOption2;
        cout << "--------------------1. Shortest Job First Scheduling(Preemptive)------------------------" << endl;
        cout << "--------------------2. Priority Scheduling(Preemptive)----------------------" << endl;
        cout << "--------------------3. Round Robin Scheduling(Preemptive)----------------------" << endl;
        cout << "Choose your Sub Option" << endl;
        cin >> subOption2;
        if(subOption2==1){
            shortestJobFirstPreemptive(head);
        }
        else if(subOption2==2){
          prioritySchedulingPreemptive(head);
        }
        else if(subOption2==3){
            roundRobinScheduling(head);
        }
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
    // Cleanup: free allocated memory
while (head != nullptr) {
    Process* temp = head;
    head = head->next;
    delete temp;
}

// Add this additional cleanup loop
while (front != nullptr) {
    Process* temp = front;
    front = front->next;
    delete temp;
}

    return 0;
}