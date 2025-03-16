#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate a random array of integers
void generateRandomArray(int arr[], int N) {
    srand(time(0));  // Seed the random number generator with the current time
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;  // Generate random numbers between 0 and 99
    }
}

// Function to display the contents of the array
void displayArray(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";  // Print each element in the array
    }
    cout << endl;  // Print a newline after displaying the array
}

// Function to sort the array using Selection Sort algorithm
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {  // Loop through each element of the array
        int smIdx = i;  // Assume the current index is the smallest
        for (int j = i + 1; j < n; j++) {  // Loop through the remaining elements
            if (arr[j] < arr[smIdx]) {  // If a smaller element is found
                smIdx = j;  // Update the index of the smallest element
            }
        }
        swap(arr[i], arr[smIdx]);  // Swap the smallest element with the current element
    }
}

// Function to perform Interpolation Search
// It finds the target element in the sorted array and returns its index
int interpolationSearch(int arr[], int N, int tar) {
    int high = N - 1;  // The last index in the array
    int low = 0;  // The first index in the array
    int steps = 0;  // To count the number of steps taken during the search
    
    // Continue searching while the target is within the range of low and high
    while (tar >= arr[low] && tar <= arr[high] && low <= high) {
        steps++;  // Increment the steps counter
        
        // Estimate the position of the target element based on interpolation
        int guess = low + (high - low) * (tar - arr[low]) / (arr[high] - arr[low]);

        cout << "Guess index: " << guess << endl;  // Print the current guess index

        if (arr[guess] > tar) {
            high = guess - 1;  // If the guessed value is greater, move the high pointer
        } else if (arr[guess] < tar) {
            low = guess + 1;  // If the guessed value is smaller, move the low pointer
        } else {
            cout << "Number of steps required: " << steps << endl;
            return guess;  // Target found at the guessed index
        }
    }
  
    return -1;  // If target not found, return -1
}

int main() {
    int N;
    cout << "Enter the number of elements: ";
    cin >> N;  // Input the size of the array

    int arr[N];  // Declare an array of size N
    generateRandomArray(arr, N);  // Call function to generate a random array

    cout << "\nGenerated Array: ";
    displayArray(arr, N);  // Display the generated random array

    // Measure the runtime of selection sort
    auto start = high_resolution_clock::now();
    selectionSort(arr, N);  // Sort the array using selection sort
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Selection Sort Time: " << duration.count() << " milliseconds" << endl;

    cout << "\nSorted Array: ";
    displayArray(arr, N);  // Display the sorted array

    int target;
    cout << "\nEnter the value to search for: ";
    cin >> target;  // Input the target value to search for

    // Measure the runtime of interpolation search
    start = high_resolution_clock::now();
    int result = interpolationSearch(arr, N, target);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Interpolation Search Time: " << duration.count() << " milliseconds" << endl;

    // Display the result of the search
    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found." << endl;
    }

    // Time complexity analysis
    cout << "\nTime Complexity Analysis:" << endl;
    cout << "Selection Sort:" << endl;
    cout << "Best Case: O(N^2)" << endl;
    cout << "Average Case: O(N^2)" << endl;
    cout << "Worst Case: O(N^2)" << endl;

    cout << "Interpolation Search:" << endl;
    cout << "Best Case: O(1)" << endl;
    cout << "Average Case: O(log(log(N)))" << endl;
    cout << "Worst Case: O(N)" << endl;

    return 0;  // End of the program
}
