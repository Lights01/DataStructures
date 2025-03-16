// C++ program to perform binary Merge on a sorted array and analyze its time complexity
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

// Function to generate a random array
void generateRandomArray(int arr[], int N) {
    srand(time(0)); // Initialize random seed based on current time
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100; // Generate a random number between 0 and 99
    }
}

// Function to display the elements of the array
void displayArray(int arr[], int N) {
    for (int i = 0; i < N; i++) 
        cout << arr[i] << " ";  
    cout << endl;
}

// Merge function for merge sort
void merge(int arr[], int strt, int mid, int end) {
    vector<int> temp; // Temporary vector to hold merged elements
    int i = strt, j = mid + 1;

    // Merge elements from the left and right subarrays in sorted order
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i]);
            i++;
        } else {
            temp.push_back(arr[j]);
            j++;
        }
    }

    // Add remaining elements from the left part (if any)
    while (i <= mid) {
        temp.push_back(arr[i]);
        i++;
    }

    // Add remaining elements from the right part (if any)
    while (j <= end) {
        temp.push_back(arr[j]);
        j++;
    }

    // Copy the sorted elements from temp back to the original array
    for (int idx = 0; idx < temp.size(); idx++) {
        arr[idx + strt] = temp[idx];
    }
}

// Merge sort function
void mergeSort(int arr[], int strt, int end) {
    if (strt < end) {
        int mid = strt + (end - strt) / 2; // Find the middle index
        mergeSort(arr, strt, mid);         // Recursively sort the left half
        mergeSort(arr, mid + 1, end);      // Recursively sort the right half
        merge(arr, strt, mid, end);        // Merge both sorted halves
    }
}

// Function to analyze and display time complexity and runtime
void analyzeMergeSort(int N) {
    int arr[N]; // Declare an array of size N
    generateRandomArray(arr, N); // Generate a random array

    cout << "\nGenerated Array: ";
    displayArray(arr, N);

    // Measure runtime for merge sort
    auto startMerge = high_resolution_clock::now();
    mergeSort(arr, 0, N - 1);
    auto stopMerge = high_resolution_clock::now();
    auto durationMerge = duration_cast<microseconds>(stopMerge - startMerge);

    cout << "\nSorted Array By Merge Sort: ";
    displayArray(arr, N);
    cout << "Merge Sort Runtime: " << durationMerge.count() << " microseconds\n";
}

int main() {
    vector<int> inputSizes = {10, 100, 1000, 10000}; // Different input sizes for analysis

    for (int N : inputSizes) {
        cout << "\nAnalyzing Merge Sort for N = " << N << ":\n";
        analyzeMergeSort(N);
    }

    // Time complexity analysis
    cout << "\nTime Complexity Analysis of Merge Sort:\n";
    cout << "Best Case: O(N log N)\n";
    cout << "Average Case: O(N log N)\n";
    cout << "Worst Case: O(N log N)\n";

    return 0;
}
