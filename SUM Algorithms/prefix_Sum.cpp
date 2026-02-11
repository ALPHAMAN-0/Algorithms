#include <iostream>
#include <vector>
using namespace std;

/*
 * PREFIX SUM ALGORITHM
 * ====================
 * Prefix sum is a technique where we precompute cumulative sums to answer
 * range sum queries in O(1) time after O(n) preprocessing.
 *
 * Visual Example:
 * Original Array:  [2,  4,  6,  8,  10]
 *                   ↓   ↓   ↓   ↓   ↓
 * Prefix Sum:      [2,  6, 12, 20, 30]
 *
 * prefix[i] = sum of all elements from index 0 to i
 * prefix[0] = arr[0] = 2
 * prefix[1] = arr[0] + arr[1] = 2 + 4 = 6
 * prefix[2] = arr[0] + arr[1] + arr[2] = 2 + 4 + 6 = 12
 * prefix[3] = arr[0] + arr[1] + arr[2] + arr[3] = 2 + 4 + 6 + 8 = 20
 * prefix[4] = arr[0] + arr[1] + arr[2] + arr[3] + arr[4] = 2 + 4 + 6 + 8 + 10 = 30
 */

// Build prefix sum array
// Time Complexity: O(n), Space Complexity: O(n)
vector<int> buildPrefixSum(const vector<int> &arr)
{
    int n = arr.size();
    vector<int> prefix(n);

    // Base case: first element is same as original array
    prefix[0] = arr[0];

    // Build prefix sum by adding current element to previous prefix sum
    for (int i = 1; i < n; i++)
    {
        prefix[i] = prefix[i - 1] + arr[i];
    }

    return prefix;
}

/*
 * Get range sum using prefix sum array in O(1) time
 * Returns sum of elements from index left to right (inclusive)
 *
 * Formula: RangeSum(left, right) = prefix[right] - prefix[left - 1]
 *
 * Visual Example: Get sum from index 1 to 3
 * Array:       [2,  4,  6,  8,  10]
 * Prefix:      [2,  6, 12, 20, 30]
 *               ↑       ↑
 *            left-1   right
 *
 * Sum(1 to 3) = prefix[3] - prefix[0] = 20 - 2 = 18
 * Verification: 4 + 6 + 8 = 18 ✓
 *
 * Special case: If left = 0, just return prefix[right]
 */
int getRangeSum(const vector<int> &prefix, int left, int right)
{
    // If querying from start, return prefix sum directly
    if (left == 0)
    {
        return prefix[right];
    }
    // Otherwise, subtract the prefix sum before 'left'
    return prefix[right] - prefix[left - 1];
}

int main()
{
    // Example array
    vector<int> arr = {2, 4, 6, 8, 10};

    // Display original array
    cout << "Original Array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    // Step 1: Build prefix sum array (O(n) preprocessing)
    vector<int> prefix = buildPrefixSum(arr);

    // Display prefix sum array
    cout << "Prefix Sum Array: ";
    for (int num : prefix)
    {
        cout << num << " ";
    }
    cout << endl;

    /*
     * Visualization of Prefix Sum Array:
     * Index:    0   1   2   3   4
     * Array:    2   4   6   8  10
     * Prefix:   2   6  12  20  30
     *           ↑   ↑   ↑   ↑   ↑
     *           2  2+4  6+6  12+8  20+10
     */

    // Step 2: Perform range sum queries (O(1) per query)
    cout << "\n========== Range Sum Queries ==========" << endl;

    // Query 1: Sum from index 0 to 2 → 2 + 4 + 6 = 12
    cout << "Sum from index 0 to 2: " << getRangeSum(prefix, 0, 2) << endl;

    // Query 2: Sum from index 1 to 3 → 4 + 6 + 8 = 18
    cout << "Sum from index 1 to 3: " << getRangeSum(prefix, 1, 3) << endl;

    // Query 3: Sum from index 2 to 4 → 6 + 8 + 10 = 24
    cout << "Sum from index 2 to 4: " << getRangeSum(prefix, 2, 4) << endl;

    return 0;
}
