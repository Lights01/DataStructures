#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stack>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to generate an array of random numbers between 0 and 99
void generateRandomArray(int arr[], int N) {
    srand(time(0)); // Initialize random seed based on current time (ensures that the random numbers are different every time the program is run)
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

// Function to merge two sorted halves of the array
void merge(int arr[], int strt, int mid, int end) {
  stack<int> tempStack;  // Temporary stack to hold merged elements
  int i = strt, j = mid + 1;

  // Merge elements from the left and right subarrays in sorted order
  while(i <= mid && j <= end) {
    if(arr[i] <= arr[j]){
      tempStack.push(arr[i]);  // Add smaller element from left part
      i++;
    } else {
      tempStack.push(arr[j]);  // Add smaller element from right part
      j++;
    }
  }

  // Add remaining elements from the left part (if any)
  while (i <= mid){
    tempStack.push(arr[i]);
    i++;
  }

  // Add remaining elements from the right part (if any)
  while (j <= end){
    tempStack.push(arr[j]);
    j++;
  }

  // Copy the sorted elements from the stack back to the original array
  int idx = end;
  while (!tempStack.empty()) {
    arr[idx] = tempStack.top();
    tempStack.pop();
    idx--;
  }
}

// Function to perform merge sort on the array
// strt = start
void mergeSort(int arr[], int strt, int end){
  if(strt < end){
    // Find the middle index
    int mid = strt + (end - strt) / 2;

    // Recursively sort the left half
    mergeSort(arr, strt, mid);

    // Recursively sort the right half
    mergeSort(arr, mid + 1, end);

    // Merge both sorted halves
    merge(arr, strt, mid, end);
  }
}

// Function to perform binary search on the sorted array
int binarySearch(int arr[], int N, int tar){
  int strt = 0, end = N - 1;
  int steps = 0; // Variable to count the number of steps taken

  // Binary search loop
  while(strt <= end) {
    steps++; // Increment step count on each iteration
    int mid = strt + (end - strt) / 2;  // Find the middle index

    if(tar > arr[mid]){
      strt = mid + 1; // Search in the second half
    } else if(tar < arr[mid]) {
      end = mid - 1; // Search in the first half
    } else {
      cout << "Steps taken: " << steps << endl;  // Display number of steps
      return mid; // Return the index of the found element
    }
  }

  return -1;  // target is not found
}

int main() {
    int N;
    // Ask user for the number of elements in the array
    cout << "Enter the number of elements: ";
    cin >> N;
    
    int arr[N];  // Declare an array of size N
    generateRandomArray(arr, N);  // Generate a random array
    
    // Display the randomly generated array
    cout << "\nGenerated Array: ";
    displayArray(arr, N);

    // Measure the time taken by merge sort
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, N - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by merge sort: " << duration.count() << " microseconds" << endl;

    // Display the sorted array
    cout << "\nSorted Array By Merge sort is: ";
    displayArray(arr, N);

    int target;
    // Ask the user for the value they want to search for
    cout << "\nEnter the value to search for: ";
    cin >> target;

    // Measure the time taken by binary search
    start = high_resolution_clock::now();
    int result = binarySearch(arr, N, target);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by binary search: " << duration.count() << " microseconds" << endl;
    
    // Display the result of the search
    if (result != -1) {
        cout << "Element found at index: " << result << endl;
    } else {
        cout << "Element not found." << endl;
    }

    return 0;
} 