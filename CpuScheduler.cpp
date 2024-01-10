#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
const int QUANTUM = 1;

struct Process
{

    int processID;
    int burstTime;
    int arrivalTime;
    int priority;
    int completionTime;
    int turnAroundTime;
    int waitingTime;
    int initialBurstTime;
    float AvgWaitingTime;
    Process *next;
};

void addProcess(Process *&head, Process *&tail, int burstTime, int arrivalTime, int priority)
{
    Process *newProcess = new Process;
    newProcess->processID = (tail != nullptr) ? tail->processID + 1 : 1; // Increment process ID
    newProcess->burstTime = burstTime;
    newProcess->arrivalTime = arrivalTime;
    newProcess->priority = priority;
    newProcess->next = nullptr;

    if (head == nullptr)
    {
        head = tail = newProcess;
    }
    else
    {
        tail->next = newProcess;
        tail = newProcess;
    }
}

// first come first serve method
void firstcomefirstserve(Process *head)
{
    Process *current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    ofstream outFile("out.txt");
    cout << "scheduling Method: First come First Serve" << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "scheduling Method: First come First Serve" << endl;
    outFile << "Process Waiting times:" << endl;
    while (current != nullptr)
    {
        //  waiting time
        current->waitingTime = currentTime - current->arrivalTime;
        currentTime += current->burstTime;
        cout << "Process " << count << ":" << current->waitingTime << "ms" << endl;
        outFile << "Process " << count << ":" << current->waitingTime << "ms" << endl;
        count++;
        // average waiting time
        totalWaitingTime += current->waitingTime;
        processCount++;
        current = current->next;
    }

    cout << "Average Waiting Time:" << totalWaitingTime / processCount;
    cout << "ms" << endl;
    outFile << "Average Waiting Time:" << totalWaitingTime / processCount;
    outFile << "ms" << endl;
    outFile.close();
}

// shortest jobfirst(Non Preemptive)
// Function to find the process with the shortest burst time
Process *findShortest(Process *start, int currentTime)
{
    Process *shortest = nullptr;
    Process *current = start;

    while (current != nullptr && current->arrivalTime <= currentTime)
    {
        if (shortest == nullptr || current->burstTime < shortest->burstTime || (current->burstTime == shortest->burstTime && current->arrivalTime < shortest->arrivalTime))
        {
            shortest = current;
        }
        current = current->next;
    }

    return shortest;
}

// Shortest Job First (Non Preemptive)
void shortestJobFirstNonPreemptive(Process *&head)
{
    Process *current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    ofstream outFile("out.txt");

    // Array to store waiting times
    int *waitingTimesArray = new int[count];

    cout << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;

    outFile << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;

    while (current != nullptr)
    {
        // Find the process with the shortest burst time
        Process *shortest = findShortest(current, currentTime);

        if (shortest != nullptr)
        {
            // Execute the shortest process
            shortest->waitingTime = currentTime - shortest->arrivalTime;
            currentTime += shortest->burstTime;

            // Store waiting time in the array
            waitingTimesArray[shortest->processID - 1] = shortest->waitingTime;

            totalWaitingTime += shortest->waitingTime;
            processCount++;
            count++;

            // Remove the executed process from the list
            if (current == shortest)
            {
                head = current->next;
            }
            else
            {
                Process *temp = head;
                while (temp->next != shortest)
                {
                    temp = temp->next;
                }
                temp->next = shortest->next;
            }

            delete shortest;
        }
        else
        {
            currentTime++;
        }

        // Update the current pointer to head
        current = head;
    }

    // Display process waiting times in order
    cout << "Process Waiting times:" << endl;
    outFile << "Process Waiting times:" << endl;
    for (int i = 0; i < processCount; i++)
    {
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
Process *findHighestPriority(Process *head, int currentTime)
{
    Process *highestPriority = nullptr;
    Process *temp = head;

    while (temp != nullptr && temp->arrivalTime <= currentTime)
    {
        if (highestPriority == nullptr || temp->priority < highestPriority->priority)
        {
            highestPriority = temp;
        }
        temp = temp->next;
    }

    return highestPriority;
}

// Function to schedule processes using Priority Scheduling (Non Preemptive) algorithm
void prioritySchedulingNonPreemptive(Process *&head)
{
    Process *current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;

    // Array to store waiting times
    int *waitingTimesArray = new int[processCount];

    cout << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;
    cout << "Process Waiting times:" << endl;

    ofstream outFile("out.txt");
    outFile << "Scheduling Method: Priority Scheduling (Non Preemptive)" << endl;
    outFile << "Process Waiting times:" << endl;

    // Loop to calculate waiting times and store them in the array
    while (current != nullptr)
    {
        Process *highestPriority = findHighestPriority(current, currentTime);

        if (highestPriority != nullptr)
        {
            // Execute the process with the highest priority
            highestPriority->waitingTime = currentTime - highestPriority->arrivalTime;
            currentTime += highestPriority->burstTime;

            // Store waiting time in the array
            waitingTimesArray[highestPriority->processID - 1] = highestPriority->waitingTime;

            totalWaitingTime += highestPriority->waitingTime;
            processCount++;

            // Remove the executed process from the list
            if (current == highestPriority)
            {
                current = current->next;
                head = current;
            }
            else
            {
                Process *temp = current;
                Process *prev = nullptr;

                while (temp != nullptr && temp != highestPriority)
                {
                    prev = temp;
                    temp = temp->next;
                }

                if (temp != nullptr)
                {
                    prev->next = temp->next;
                }
            }

            delete highestPriority;
        }
        else
        {
            currentTime++;
        }
    }

    // Display process waiting times in order
    // cout << "Process Waiting times:" << endl;
    for (int i = 0; i < processCount; i++)
    {
        cout << "Process " << (i + 1) << ": " << waitingTimesArray[i] << "ms" << endl;
        outFile << "Process " << (i + 1) << ": " << waitingTimesArray[i] << "ms" << endl;
    }

    // Display average waiting time
    cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;

    // Clean up memory
    delete[] waitingTimesArray;
    outFile.close();
}

struct QueueNode
{
    Process *data;
    QueueNode *next;
};

struct ProcessQueue
{
    QueueNode *front;
    QueueNode *rear;
};

void initializeQueue(ProcessQueue &q)
{
    q.front = nullptr;
    q.rear = nullptr;
}

void enqueue(ProcessQueue &q, Process *process)
{
    QueueNode *newNode = new QueueNode;
    newNode->data = process;
    newNode->next = nullptr;

    if (q.front == nullptr)
    {
        q.front = q.rear = newNode;
    }
    else
    {
        q.rear->next = newNode;
        q.rear = newNode;
    }
}

Process *dequeue(ProcessQueue &q)
{
    if (q.front == nullptr)
    {
        return nullptr;
    }

    QueueNode *temp = q.front;
    Process *processData = temp->data;

    q.front = q.front->next;

    if (q.front == nullptr)
    {
        q.rear = nullptr;
    }

    delete temp;
    return processData;
}

void printQueue(ProcessQueue &q)
{
    QueueNode *current = q.front;

    while (current != nullptr)
    {
        Process *currentProcess = current->data;
        cout << "Process ID: " << currentProcess->processID << "\tBurst Time: " << currentProcess->burstTime
             << "\tArrival Time: " << currentProcess->arrivalTime << "\tPriority: " << currentProcess->priority
             << "\tInitial Burst Time: " << currentProcess->initialBurstTime
             << "\tCompletion Time: " << currentProcess->completionTime
             << "\tTurn-Around Time: " << currentProcess->turnAroundTime << endl;

        current = current->next;
    }
    cout << endl;
}

ProcessQueue processQueue;
int currentProcessID = 1;
void addProcess1(int burstTime, int arrivalTime, int priority, int initialBurstTime, int completionTime, int turnAroundTime)
{
    Process *newProcess = new Process;
    newProcess->processID = currentProcessID++;
    newProcess->burstTime = burstTime;
    newProcess->arrivalTime = arrivalTime;
    newProcess->priority = priority;
    newProcess->initialBurstTime = initialBurstTime;
    newProcess->completionTime = completionTime;
    newProcess->turnAroundTime = turnAroundTime;
    newProcess->next = nullptr;

    enqueue(processQueue, newProcess);
}

Process *dequeue()
{
    return dequeue(processQueue);
}

void addProcess2(int processID, int burstTime, int arrivalTime, int priority, int initialBurstTime, int completionTime, int turnAroundTime)
{
    Process *newProcess = new Process;
    newProcess->processID = processID; // Use the provided processID
    newProcess->burstTime = burstTime;
    newProcess->arrivalTime = arrivalTime;
    newProcess->priority = priority;
    newProcess->initialBurstTime = initialBurstTime;
    newProcess->completionTime = completionTime; // Set later in the roundRobinScheduling function
    newProcess->turnAroundTime = turnAroundTime; // Set later in the roundRobinScheduling function
    newProcess->next = nullptr;

    enqueue(processQueue, newProcess);
}

// Round Robin Scheduling
void roundRobinScheduling(Process *head)
{

    Process *current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    int quantum = 2;

    ofstream outFile("out.txt");

    cout << "Scheduling Method: Round Robin" << endl;
    cout << "Quantum: " << quantum << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Round Robin" << endl;
    outFile << "Quantum: " << quantum << endl;
    outFile << "Process Waiting times:" << endl;

    // Enqueue processes that have arrived
    while (current != nullptr && current->arrivalTime <= currentTime)
    {
        current->burstTime = current->initialBurstTime;
        addProcess1(current->burstTime, current->arrivalTime, current->priority, current->initialBurstTime, current->completionTime, current->turnAroundTime);

        current = current->next;
    }
    // printQueue(processQueue);

    // Dequeue and execute processes
    // Dequeue and execute processes
    while (current != nullptr || processQueue.front != nullptr)
    {
        if (processQueue.front != nullptr)
        {
            Process *currentProcess = dequeue(processQueue);
            // printQueue(processQueue);
            int remainingTime = min(quantum, currentProcess->burstTime);

            // Calculate waiting time before execution
            // currentProcess->waitingTime = currentTime - currentProcess->arrivalTime;

            // Enqueue back if burst time is remaining
            if (currentProcess->burstTime > remainingTime)
            {
                currentProcess->burstTime -= remainingTime;
                addProcess2(currentProcess->processID, currentProcess->burstTime, currentProcess->arrivalTime, currentProcess->priority, currentProcess->initialBurstTime, currentProcess->completionTime, currentProcess->turnAroundTime);

                // printQueue(processQueue);
            }
            else
            {
                currentProcess->completionTime = currentTime + remainingTime;
                currentProcess->turnAroundTime = currentProcess->completionTime - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnAroundTime - currentProcess->initialBurstTime;
                // Process is completed
                // cout<<"current time before completion:"<<currentTime;

                cout << "Process " << currentProcess->processID << ": " << currentProcess->waitingTime << "ms" << endl;
                outFile << "Process " << currentProcess->processID << ": " << currentProcess->waitingTime << "ms" << endl;

                totalWaitingTime += currentProcess->waitingTime;
                processCount++;
                count++;
            }

            currentTime += remainingTime;
            // cout<<"curremt time after the funct:"<<currentTime<<endl;

            delete currentProcess;
        }
        else
        {
            currentTime++;
        }
    }

    cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;

    outFile.close();
}

// ... (existing code)

// Function to find the process with the shortest remaining burst time
// Function to find the process with the shortest remaining burst time
Process* dequeue(ProcessQueue& q, Process* processToRemove) {
    if (q.front == nullptr) {
        return nullptr;
    }

    QueueNode* current = q.front;
    QueueNode* previous = nullptr;

    while (current != nullptr) {
        Process* processData = current->data;

        if (processData == processToRemove) {
            if (previous == nullptr) {
                q.front = current->next;
            } else {
                previous->next = current->next;
            }

            if (current == q.rear) {
                q.rear = previous;
            }

            delete current;
            return processData;
        }

        previous = current;
        current = current->next;
    }

    return nullptr;
}

Process* findShortest1(int currentTime) {
    Process* shortest = nullptr;
    QueueNode* current = processQueue.front;

    while (current != nullptr) {
        Process* currentProcess = current->data;

        if (currentProcess->arrivalTime <= currentTime &&
            (shortest == nullptr ||
             currentProcess->burstTime < shortest->burstTime ||
             (currentProcess->burstTime == shortest->burstTime && currentProcess->arrivalTime < shortest->arrivalTime))) {
            shortest = currentProcess;
        }

        current = current->next;
    }

    return shortest;
}

void shortestJobFirstPreemptive() {
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    int QUANTUM = 1;
    ofstream outFile("out.txt");
    // Array to store waiting times
    int *waitingTimesArray = new int[count];

    cout << "Scheduling Method: Shortest Job First (Preemptive)" << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Shortest Job First (Preemptive)" << endl;
    outFile << "Process Waiting times:" << endl;

    while (processQueue.front != nullptr) {
        Process* shortest = findShortest1(currentTime);

        if (shortest != nullptr) {
            int remainingTime = min(QUANTUM, shortest->burstTime);
            shortest->burstTime -= remainingTime;

            shortest->waitingTime = currentTime - shortest->arrivalTime;
            currentTime += remainingTime;

            if (shortest->burstTime <= 0) {
                shortest->completionTime = currentTime;
                shortest->turnAroundTime = shortest->completionTime - shortest->arrivalTime;
                shortest->waitingTime = shortest->turnAroundTime - shortest->initialBurstTime;
                 // Store waiting time in the array
            waitingTimesArray[shortest->processID - 1] = shortest->waitingTime;

              //  cout << "Process " << shortest->processID << ": " << shortest->waitingTime << "ms" << endl;
              //  outFile << "Process " << shortest->processID << ": " << shortest->waitingTime << "ms" << endl;

                totalWaitingTime += shortest->waitingTime;
                processCount++;
                count++;

                // Remove the executed process from the queue
                dequeue(processQueue, shortest);
            }
        } else {
            currentTime++;
        }
    }
     // Display process waiting times in order
    cout << "Process Waiting times:" << endl;
    outFile << "Process Waiting times:" << endl;
    for (int i = 0; i < processCount; i++)
    {
        cout << "Process " << (i + 1) << ": " << waitingTimesArray[i] << "ms" << endl;
        outFile << "Process " << (i + 1) << ": " << waitingTimesArray[i] << "ms" << endl;
    }

    if (processCount > 0) {
        cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
        outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    } else {
        cout << "No processes executed." << endl;
        outFile << "No processes executed." << endl;
    }

    // Clean up memory
    delete[] waitingTimesArray;

    outFile.close();
}
// Priority Scheduling (Preemptive)
void prioritySchedulingPreemptive(Process *head)
{
    Process *current = head;
    int currentTime = 0;
    float totalWaitingTime = 0;
    int processCount = 0;
    int count = 1;
    ofstream outFile("out.txt");

    cout << "Scheduling Method: Priority Scheduling (Preemptive)" << endl;
    cout << "Process Waiting times:" << endl;

    outFile << "Scheduling Method: Priority Scheduling (Preemptive)" << endl;
    outFile << "Process Waiting times:" << endl;

    while (current != nullptr)
    {
        // Find the process with the highest priority
        Process *highestPriority = nullptr;
        Process *temp = current;

        while (temp != nullptr && temp->arrivalTime <= currentTime)
        {
            if (highestPriority == nullptr || temp->priority < highestPriority->priority)
            {
                highestPriority = temp;
            }
            temp = temp->next;
        }

        if (highestPriority != nullptr)
        {
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
            if (highestPriority->burstTime <= 0)
            {
                delete highestPriority;
            }
        }
        else
        {
            currentTime++;
        }
    }

    if (processCount > 0)
    {
        cout << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
        outFile << "Average Waiting Time: " << totalWaitingTime / processCount << "ms" << endl;
    }
    else
    {
        cout << "No processes executed." << endl;
        outFile << "No processes executed." << endl;
    }

    outFile.close();
}

// ... (existing code)

// Function to display results
void showResults()
{
    // Implement the logic to display the results here
    // You can read the "out.txt" file and print the results
    // This function should display the results based on the user's selection
}

int main()
{

    /*
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
             int initialBurstTime = burstTime;

            addProcess1( burstTime, arrivalTime, priority,initialBurstTime,0,0);

            addProcess(head, tail, burstTime, arrivalTime, priority);
        }

        inputFile.close();*/
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
        if (subOption1 == 1)
        {

            // if user choose none as their option, automactically use first come first serve!!!!

            fstream inputFile("input.txt");
            if (inputFile.fail())
            {
                cerr << "Error: Unable to open input file." << endl;
                return 1;
            }

            Process *head = nullptr;
            Process *tail = nullptr;
            string line;
            // get the burstTime, arrivalTime and Priority from the input file
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                int burstTime, arrivalTime, priority;
                char colon;

                ss >> burstTime >> colon >> arrivalTime >> colon >> priority;
                // int initialBurstTime = burstTime;

                // addProcess1( burstTime, arrivalTime, priority,initialBurstTime,0,0);

                addProcess(head, tail, burstTime, arrivalTime, priority);
            }

            inputFile.close();
            firstcomefirstserve(head);
            while (head != nullptr)
            {
                Process *temp = head;
                head = head->next;
                delete temp;
            }
        }
        else if (subOption1 == 2)
        {

            ifstream inputFile("input.txt");
            if (inputFile.fail())
            {
                cerr << "Error: Unable to open input file." << endl;
                return 1;
            }

            Process *head = nullptr;
            Process *tail = nullptr;
            string line;
            // get the burstTime, arrivalTime and Priority from the input file
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                int burstTime, arrivalTime, priority;
                char colon;

                ss >> burstTime >> colon >> arrivalTime >> colon >> priority;
                // int initialBurstTime = burstTime;

                // addProcess1( burstTime, arrivalTime, priority,initialBurstTime,0,0);

                addProcess(head, tail, burstTime, arrivalTime, priority);
            }

            inputFile.close();
            firstcomefirstserve(head);
            while (head != nullptr)
            {
                Process *temp = head;
                head = head->next;
                delete temp;
            }
        }
        else if (subOption1 == 3)
        {

            ifstream inputFile("input.txt");
            if (inputFile.fail())
            {
                cerr << "Error: Unable to open input file." << endl;
                return 1;
            }

            Process *head = nullptr;
            Process *tail = nullptr;
            string line;
            // get the burstTime, arrivalTime and Priority from the input file
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                int burstTime, arrivalTime, priority;
                char colon;

                ss >> burstTime >> colon >> arrivalTime >> colon >> priority;
                // int initialBurstTime = burstTime;

                // addProcess1( burstTime, arrivalTime, priority,initialBurstTime,0,0);

                addProcess(head, tail, burstTime, arrivalTime, priority);
            }

            inputFile.close();
            shortestJobFirstNonPreemptive(head);
            while (head != nullptr)
            {
                Process *temp = head;
                head = head->next;
                delete temp;
            }
        }
        else if (subOption1 == 4)
        {
            fstream inputFile("input.txt");
            if (inputFile.fail())
            {
                cerr << "Error: Unable to open input file." << endl;
                return 1;
            }

            Process *head = nullptr;
            Process *tail = nullptr;
            string line;
            // get the burstTime, arrivalTime and Priority from the input file
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                int burstTime, arrivalTime, priority;
                char colon;

                ss >> burstTime >> colon >> arrivalTime >> colon >> priority;
                // int initialBurstTime = burstTime;

                // addProcess1( burstTime, arrivalTime, priority,initialBurstTime,0,0);

                addProcess(head, tail, burstTime, arrivalTime, priority);
            }

            inputFile.close();
            prioritySchedulingNonPreemptive(head);
            while (head != nullptr)
            {
                Process *temp = head;
                head = head->next;
                delete temp;
            }
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
        if (subOption2 == 1)
        {

            ifstream inputFile("input.txt");
            if (inputFile.fail())
            {
                cerr << "Error: Unable to open input file." << endl;
                return 1;
            }

            Process *head = nullptr;
            Process *tail = nullptr;
            string line;
            // get the burstTime, arrivalTime and Priority from the input file
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                int burstTime, arrivalTime, priority;
                char colon;

                ss >> burstTime >> colon >> arrivalTime >> colon >> priority;
                 int initialBurstTime = burstTime;

                 addProcess1( burstTime, arrivalTime, priority,initialBurstTime,0,0);

               // addProcess(head, tail, burstTime, arrivalTime, priority);
            }

            inputFile.close();
            shortestJobFirstPreemptive();
            while (head != nullptr)
            {
                Process *temp = head;
                head = head->next;
                delete temp;
            }
        }
        else if (subOption2 == 2)
        {

            ifstream inputFile("input.txt");
            if (inputFile.fail())
            {
                cerr << "Error: Unable to open input file." << endl;
                return 1;
            }

            Process *head = nullptr;
            Process *tail = nullptr;
            string line;
            // get the burstTime, arrivalTime and Priority from the input file
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                int burstTime, arrivalTime, priority;
                char colon;

                ss >> burstTime >> colon >> arrivalTime >> colon >> priority;
                // int initialBurstTime = burstTime;

                // addProcess1( burstTime, arrivalTime, priority,initialBurstTime,0,0);

                addProcess(head, tail, burstTime, arrivalTime, priority);
            }

            inputFile.close();
            prioritySchedulingPreemptive(head);
            while (head != nullptr)
            {
                Process *temp = head;
                head = head->next;
                delete temp;
            }
        }
        else if (subOption2 == 3)
        {
            ifstream inputFile("input.txt");
            if (inputFile.fail())
            {
                cerr << "Error: Unable to open input file." << endl;
                return 1;
            }

            Process *head = nullptr;
            Process *tail = nullptr;
            string line;
            // get the burstTime, arrivalTime and Priority from the input file
            while (getline(inputFile, line))
            {
                stringstream ss(line);
                int burstTime, arrivalTime, priority;
                char colon;

                ss >> burstTime >> colon >> arrivalTime >> colon >> priority;
                int initialBurstTime = burstTime;

                addProcess1(burstTime, arrivalTime, priority, initialBurstTime, 0, 0);

                // addProcess(head, tail, burstTime, arrivalTime, priority);
            }

            inputFile.close();

            roundRobinScheduling(head);
            while (head != nullptr)
            {
                Process *temp = head;
                head = head->next;
                delete temp;
            }
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
    /*while (head != nullptr) {
        Process* temp = head;
        head = head->next;
        delete temp;
    }*/

    return 0;
}