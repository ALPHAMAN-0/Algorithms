#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
 * KADANE'S ALGORITHM
 * ==================
 * Finds the maximum sum of any contiguous subarray in O(n) time.
 * This is a dynamic programming approach that scans the array once.
 * 
 * Key Idea:
 * At each position, decide whether to:
 * 1. Extend the current subarray (add current element to sum)
 * 2. Start a new subarray (from current element)
 * 
 * Formula: maxEndingHere = max(arr[i], maxEndingHere + arr[i])
 * 
 * Visual Example with array: [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 * 
 * Index:    0   1   2   3   4   5   6   7   8
 * Array:   -2   1  -3   4  -1   2   1  -5   4
 * 
 * Maximum subarray: [4, -1, 2, 1] with sum = 6
 */

// Kadane's Algorithm - Returns maximum subarray sum
// Time Complexity: O(n), Space Complexity: O(1)
int kadane(const vector<int>& arr) {
    int n = arr.size();
    
    // maxSoFar: Maximum sum found so far
    // maxEndingHere: Maximum sum of subarray ending at current position
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    
    for (int i = 0; i < n; i++) {
        // Either extend the existing subarray or start fresh
        maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
        
        // Update the maximum sum found so far
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    
    return maxSoFar;
}

// Extended version: Returns the maximum sum AND the subarray indices
struct SubarrayResult {
    int maxSum;
    int start;
    int end;
};

SubarrayResult kadaneWithIndices(const vector<int>& arr) {
    int n = arr.size();
    
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    
    int start = 0;      // Start of current subarray
    int end = 0;        // End of maximum subarray
    int tempStart = 0;  // Temporary start when starting new subarray
    
    for (int i = 0; i < n; i++) {
        // If starting fresh is better, update temp start
        if (arr[i] > maxEndingHere + arr[i]) {
            maxEndingHere = arr[i];
            tempStart = i;
        } else {
            maxEndingHere = maxEndingHere + arr[i];
        }
        
        // Update maximum sum and indices if we found a better sum
        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            start = tempStart;
            end = i;
        }
    }
    
    return {maxSoFar, start, end};
}

int main() {
    cout << "========== KADANE'S ALGORITHM SIMULATION ==========" << endl;
    
    // Example array with negative and positive numbers
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n = arr.size();
    
    // Display the array
    cout << "\nOriginal Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    // Simulate Kadane's algorithm step by step
    cout << "\n--- Step-by-Step Simulation ---" << endl;
    cout << "i\tarr[i]\tmaxEndingHere\t\tmaxSoFar" << endl;
    cout << "---------------------------------------------------" << endl;
    
    int maxSoFar = INT_MIN;
    int maxEndingHere = 0;
    
    for (int i = 0; i < n; i++) {
        // Previous state
        int prevMaxEndingHere = maxEndingHere;
        
        // Update maxEndingHere
        maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
        
        // Update maxSoFar
        maxSoFar = max(maxSoFar, maxEndingHere);
        
        // Print the step
        cout << i << "\t" << arr[i] << "\t";
        
        // Show the decision made
        if (arr[i] > prevMaxEndingHere + arr[i]) {
            cout << arr[i] << " (start fresh)\t\t";
        } else {
            cout << maxEndingHere << " (extend)\t\t";
        }
        
        cout << maxSoFar << endl;
    }
    
    // Get result with indices
    SubarrayResult result = kadaneWithIndices(arr);
    
    cout << "\n========== RESULT ==========" << endl;
    cout << "Maximum Subarray Sum: " << result.maxSum << endl;
    cout << "Subarray Indices: [" << result.start << ", " << result.end << "]" << endl;
    
    cout << "Maximum Subarray: [";
    for (int i = result.start; i <= result.end; i++) {
        cout << arr[i];
        if (i < result.end) cout << ", ";
    }
    cout << "]" << endl;
    
    // Verification
    cout << "\nVerification: ";
    int sum = 0;
    for (int i = result.start; i <= result.end; i++) {
        sum += arr[i];
        if (i > result.start) cout << " + ";
        cout << arr[i];
    }
    cout << " = " << sum << " ✓" << endl;
    
    // Additional test case with all negative numbers
    cout << "\n========== TEST CASE 2: All Negative Numbers ==========" << endl;
    vector<int> arr2 = {-5, -2, -8, -1, -4};
    cout << "Array: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    
    int maxSum = kadane(arr2);
    cout << "Maximum Subarray Sum: " << maxSum << " (least negative)" << endl;
    
    return 0;
}
