#include <iostream> // For input and output operations
#include <vector>   // For using the vector container
#include <algorithm> // For using sorting functions
#include <queue> // For implementing the queue data structure used in Round Robin scheduling

using namespace std; // Allows the use of standard library components without prefixing them with std::

/*
   Class Job: Represents a job with its attributes.
   Attributes:
   - pname: The name of the process.
   - bt: Burst time required for the process.
   - at: Arrival time of the process.
   - pr: Priority of the process (lower value means higher priority).
*/
class Job {
public:
    string pname; // Process name
    int bt;       // Burst time
    int at;       // Arrival time
    int pr;       // Priority

    // Default constructor
    Job() {
        pname = ""; // Initialize process name to empty
        bt = 0;     // Initialize burst time to 0
        at = 0;     // Initialize arrival time to 0
        pr = 0;     // Initialize priority to 0
    }

    // Parameterized constructor for initializing job attributes
    Job(string name, int burst, int arrival, int priority) {
        pname = name; // Set the process name
        bt = burst;   // Set the burst time
        at = arrival; // Set the arrival time
        pr = priority; // Set the priority
    }

    // Method to take input for job attributes from the user
    void getdata() {
        cout << "Enter Process Name: ";
        cin >> pname; // Get process name from user
        cout << "Enter Burst Time: ";
        cin >> bt; // Get burst time from user
        cout << "Enter Arrival Time: ";
        cin >> at; // Get arrival time from user
        cout << "Enter Priority (lower value = higher priority): ";
        cin >> pr; // Get priority from user
    }
};

/*
   Function: printResultTable
   Purpose: Prints the result table with process details.
   Parameters:
   - jobs: A vector of Job objects representing all jobs.
   - wt: A vector of waiting times corresponding to each job.
   - tat: A vector of turnaround times corresponding to each job.
*/
void printResultTable(vector<Job> &jobs, vector<int> &wt, vector<int> &tat) {
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    cout << "------------------------------------------------------" << endl;
    for (int i = 0; i < jobs.size(); i++) {
        cout << jobs[i].pname << "\t" << jobs[i].bt << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }
}

/*
   Function: FCFS
   Purpose: Implements First-Come, First-Served (FCFS) scheduling.
   Parameters: jobs - A vector of Job objects.
*/
void FCFS(vector<Job> &jobs) {
    int n = jobs.size(); // Number of jobs

    cout << "\nFCFS Scheduling:" << endl;

    // Sort jobs based on arrival time
    sort(jobs.begin(), jobs.end(), [](Job &a, Job &b) {
        return a.at < b.at; // Sort based on arrival time
    });

    vector<int> wt(n, 0); // Waiting time
    vector<int> tat(n, 0); // Turnaround time

    // Calculate Waiting Time
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + jobs[i - 1].bt; // Waiting time for each job
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = jobs[i].bt + wt[i]; // Turnaround time = burst time + waiting time
    }

    // Print the result table
    printResultTable(jobs, wt, tat);
}

/* 
   Explanation of FCFS:
   - This algorithm processes jobs in the order they arrive.
   - It first sorts the jobs by arrival time and then calculates the waiting time
     for each job based on the burst time of the previous jobs.
   - The turnaround time is calculated as the sum of the burst time and waiting time.
*/

// SJF Scheduling Implementation
void SJF(vector<Job> &jobs) {
    int n = jobs.size(); // Number of jobs

    cout << "\nSJF Scheduling:" << endl;

    // Sort jobs based on burst time
    sort(jobs.begin(), jobs.end(), [](Job &a, Job &b) {
        return a.bt < b.bt; // Sort based on burst time
    });

    vector<int> wt(n, 0); // Waiting time
    vector<int> tat(n, 0); // Turnaround time

    // Calculate Waiting Time
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + jobs[i - 1].bt; // Waiting time for each job
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = jobs[i].bt + wt[i]; // Turnaround time = burst time + waiting time
    }

    // Print the result table
    printResultTable(jobs, wt, tat);
}

/* 
   Explanation of SJF:
   - This algorithm processes jobs based on their burst times.
   - It sorts the jobs by burst time and calculates the waiting time and turnaround time 
     in a similar manner as FCFS.
   - The job with the shortest burst time gets executed first, minimizing waiting time.
*/

// Round Robin Scheduling Implementation
void RoundRobin(vector<Job> &jobs, int tq) { // tq: Time Quantum
    int n = jobs.size(); // Number of jobs

    cout << "\nRound Robin Scheduling (Time Quantum: " << tq << "):" << endl;

    queue<int> q; // Queue to store the indices of jobs
    vector<int> rem_bt(n); // Remaining burst time
    vector<int> wt(n, 0);  // Waiting time
    vector<int> tat(n, 0); // Turnaround time

    // Queue Initialization: A queue is used to manage the jobs that need processing.
    // Remaining burst times are initialized.
    for (int i = 0; i < n; i++) {
        rem_bt[i] = jobs[i].bt; // Set remaining burst time to burst time
        q.push(i); // Add job index to queue
    }

    int time = 0; // Current time
    // Scheduling Logic: The algorithm processes each job in the queue:
    while (!q.empty()) {
        int i = q.front(); // Get the front job
        q.pop();

        // If a job's remaining burst time exceeds the time quantum (tq),
        // it runs for tq time and is put back in the queue.
        if (rem_bt[i] > tq) {
            time += tq; // Increase current time by time quantum
            rem_bt[i] -= tq; // Decrease remaining burst time
            q.push(i); // Process re-enters queue
        } else {
            // If a job can finish within the time quantum, it completes,
            // and its waiting time is calculated.
            time += rem_bt[i]; // Increase time by remaining burst time
            wt[i] = time - jobs[i].bt; // Calculate waiting time
            rem_bt[i] = 0; // Job completed
        }
    }

    // Calculate Turnaround Time: The turnaround time is calculated after all jobs are processed.
    for (int i = 0; i < n; i++) {
        tat[i] = jobs[i].bt + wt[i]; // Turnaround time = burst time + waiting time
    }

    // Print Results: The results are displayed using printResultTable().
    printResultTable(jobs, wt, tat);
}

/* 
   Explanation of Round Robin:
   - This algorithm uses a fixed time quantum for job execution.
   - Each job is executed for a time quantum; if it doesn't finish, it is placed back in the queue.
   - The waiting time is calculated based on how long each job has to wait to be processed again.
   - This method ensures that all jobs get a fair share of the CPU.
*/

// Priority Scheduling Implementation
void PriorityScheduling(vector<Job> &jobs) {
    int n = jobs.size(); // Number of jobs

    cout << "\nPriority Scheduling:" << endl;

    // Sort jobs based on priority
    sort(jobs.begin(), jobs.end(), [](Job &a, Job &b) {
        return a.pr < b.pr; // Higher priority has lower priority value
    });

    vector<int> wt(n, 0); // Waiting time
    vector<int> tat(n, 0); // Turnaround time

    // Calculate Waiting Time
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + jobs[i - 1].bt; // Waiting time for each job
    }

    // Calculate Turnaround Time
    for (int i = 0; i < n; i++) {
        tat[i] = jobs[i].bt + wt[i]; // Turnaround time = burst time + waiting time
    }

    // Print the result table
    printResultTable(jobs, wt, tat);
}

/* 
   Explanation of Priority Scheduling:
   - This algorithm processes jobs based on their priority.
   - It sorts the jobs by priority value and calculates the waiting time and turnaround time similarly to FCFS and SJF.
   - Higher priority jobs (lower priority value) are executed first.
*/

int main() {
    int n; // Number of jobs
    cout << "Enter the number of jobs: ";
    cin >> n; // Get number of jobs from user

    vector<Job> jobs; // Vector to store jobs
    for (int i = 0; i < n; i++) {
        Job j; // Create a Job object
        j.getdata(); // Get data for the job
        jobs.push_back(j); // Add the job to the vector
    }

    int choice, tq; // Variables for user choice and time quantum
    do {
        cout << endl;
        cout << "1. FCFS" << endl;
        cout << "2. SJF" << endl;
        cout << "3. Priority Scheduling" << endl;
        cout << "4. Round Robin" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice; // Get user's choice for scheduling algorithm

        switch (choice) {
            case 1:
                FCFS(jobs); // Call FCFS scheduling
                break;
            case 2:
                SJF(jobs); // Call SJF scheduling
                break;
            case 3:
                PriorityScheduling(jobs); // Call Priority scheduling
                break;
            case 4:
                cout << "Enter Time Quantum for Round Robin: ";
                cin >> tq; // Get time quantum for Round Robin
                RoundRobin(jobs, tq); // Call Round Robin scheduling
                break;
            case 5:
                cout << "Exiting..." << endl; // Exit the program
                break;
            default:
                cout << "Invalid choice, please try again." << endl; // Handle invalid choice
        }
    } while (choice != 5); // Repeat until the user chooses to exit

    return 0; // Indicate successful program termination
}

/*
   Explanation of Main Function:
   - The main function begins by prompting the user for the number of jobs.
   - It initializes a vector to store job data and collects input for each job.
   - The user can choose between different scheduling algorithms and execute them accordingly.
   - A loop continues until the user decides to exit the program, allowing for multiple scheduling calculations.
*/
