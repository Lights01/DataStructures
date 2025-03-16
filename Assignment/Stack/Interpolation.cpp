#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate a stack of random numbers
void generateRandomStack(stack<int>& s, int N) {
    srand(time(0));  // Seed the random number generator
    for (int i = 0; i < N; i++) {
        s.push(rand() % 100);  // Push random numbers onto the stack
    }
}

// Function to display the elements of a stack
void displayStack(stack<int> s) {
    vector<int> temp;
    
    // Extract elements from stack to display in order
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }
    
    // Display elements in reverse order (original order)
    for (int i = temp.size() - 1; i >= 0; i--) {
        cout << temp[i] << " ";
    }
    cout << endl;
}

// Function to sort a stack using selection sort
void selectionSort(stack<int>& s) {
    vector<int> temp;
    
    // Transfer elements from stack to vector
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }

    int n = temp.size();
    for (int i = 0; i < n - 1; i++) {
        int smIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (temp[j] < temp[smIdx]) {
                smIdx = j;
            }
        }
        swap(temp[i], temp[smIdx]);  // Swap elements
    }

    // Push sorted elements back to stack (in reverse order)
    for (int i = n - 1; i >= 0; i--) {
        s.push(temp[i]);
    }
}

// Function to perform Interpolation Search on a sorted stack
int interpolationSearch(stack<int> s, int target) {
    vector<int> temp;
    
    // Extract elements from stack to vector
    while (!s.empty()) {
        temp.push_back(s.top());
        s.pop();
    }

    int low = 0, high = temp.size() - 1;
    int steps = 0;

    while (low <= high && target >= temp[low] && target <= temp[high]) {
        steps++;

        // Estimate position
        int guess = low + ((high - low) / (temp[high] - temp[low])) * (target - temp[low]);

        cout << "Guess index: " << guess << endl;

        if (temp[guess] > target)
            high = guess - 1;
        else if (temp[guess] < target)
            low = guess + 1;
        else {
            cout << "Number of steps required: " << steps << endl;
            return guess;
        }
    }
    return -1;  // Target not found
}

int main() {
    int N;
    cout << "Enter the number of elements: ";
    cin >> N;

    stack<int> s;  // Stack to store elements
    generateRandomStack(s, N);  // Generate random elements and push onto the stack

    cout << "\nGenerated Stack (as array): ";
    displayStack(s);  // Display the generated stack

    // Measure time for selection sort
    auto start = high_resolution_clock::now();
    selectionSort(s);  // Sort the stack using selection sort
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "\nSorted Stack (as array): ";
    displayStack(s);  // Display the sorted stack
    cout << "Time taken for selection sort: " << duration.count() << " milliseconds" << endl;

    int target;
    cout << "\nEnter the value to search for: ";
    cin >> target;

    // Measure time for interpolation search
    start = high_resolution_clock::now();
    int result = interpolationSearch(s, target);  // Perform interpolation search on the sorted stack
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);

    if (result != -1) {
        cout << "Element found at index: " << result << endl;  // Element found
    } else {
        cout << "Element not found." << endl;  // Element not found
    }
    cout << "Time taken for interpolation search: " << duration.count() << " milliseconds" << endl;

    return 0;
}

/*
Time Complexity Analysis:

Selection Sort:
- Best Case: O(N^2) - Even if the array is already sorted, the algorithm still performs N^2 comparisons.
- Average Case: O(N^2) - The algorithm performs N^2/2 comparisons on average.
- Worst Case: O(N^2) - The algorithm performs N^2 comparisons in the worst case.

Interpolation Search:
- Best Case: O(1) - If the target is at the estimated position.
- Average Case: O(log(log(N))) - On average, the algorithm performs log(log(N)) comparisons.
- Worst Case: O(N) - If the distribution of elements is non-uniform or if the target is not present.
*/