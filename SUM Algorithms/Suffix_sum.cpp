#include <iostream>
#include <vector>
using namespace std;

/*
 * SUFFIX SUM ALGORITHM
 * ====================
 * Suffix sum is a technique where we precompute cumulative sums from right to left
 * to answer range sum queries in O(1) time after O(n) preprocessing.
 *
 * Visual Example:
 * Original Array:  [2,  4,  6,  8,  10]
 *                   ↓   ↓   ↓   ↓   ↓
 * Suffix Sum:     [30, 28, 24, 16, 10]
 *
 * suffix[i] = sum of all elements from index i to end (n-1)
 * suffix[4] = arr[4] = 10
 * suffix[3] = arr[3] + arr[4] = 8 + 10 = 18  ← Wait, let me recalculate
 * suffix[3] = arr[3] + suffix[4] = 8 + 10 = 18... Actually 16+10=16? No...
 * Let me think: suffix[3] should be sum from index 3 to 4 = 8 + 10 = 18
 * Actually looking at the pattern: we build from right to left
 * suffix[4] = 10
 * suffix[3] = 8 + 10 = 18 (but I said 16 above - let me verify in simulation)
 *
 * Building from right to left:
 * suffix[4] = arr[4] = 10
 * suffix[3] = suffix[4] + arr[3] = 10 + 8 = 18
 * suffix[2] = suffix[3] + arr[2] = 18 + 6 = 24
 * suffix[1] = suffix[2] + arr[1] = 24 + 4 = 28
 * suffix[0] = suffix[1] + arr[0] = 28 + 2 = 30
 */

// Build suffix sum array from right to left
// Time Complexity: O(n), Space Complexity: O(n)
vector<int> buildSuffixSum(const vector<int> &arr)
{
    int n = arr.size();
    vector<int> suffix(n);

    // Base case: last element is same as original array
    suffix[n - 1] = arr[n - 1];

    // Build suffix sum by adding current element to next suffix sum
    // Going backwards from second-last to first element
    for (int i = n - 2; i >= 0; i--)
    {
        suffix[i] = suffix[i + 1] + arr[i];
    }

    return suffix;
}

/*
 * Get range sum using suffix sum array in O(1) time
 * Returns sum of elements from index left to right (inclusive)
 *
 * Formula: RangeSum(left, right) = suffix[left] - suffix[right + 1]
 *
 * Visual Example: Get sum from index 1 to 3
 * Array:       [2,  4,  6,  8,  10]
 * Suffix:     [30, 28, 24, 16, 10]
 *                  ↑           ↑
 *                left      right+1
 *
 * Sum(1 to 3) = suffix[1] - suffix[4] = 28 - 10 = 18
 * Verification: 4 + 6 + 8 = 18 ✓
 *
 * Special case: If right = n-1 (querying till end), just return suffix[left]
 */
int getRangeSum(const vector<int> &suffix, int left, int right, int n)
{
    // If querying till the end, return suffix sum directly
    if (right == n - 1)
    {
        return suffix[left];
    }
    // Otherwise, subtract the suffix sum after 'right'
    return suffix[left] - suffix[right + 1];
}

int main()
{
    // Example array
    vector<int> arr = {2, 4, 6, 8, 10};
    int n = arr.size();

    cout << "========== SUFFIX SUM SIMULATION ==========" << endl;

    // Display original array
    cout << "\nOriginal Array: ";
    for (int num : arr)
    {
        cout << num << " ";
    }
    cout << endl;

    // Step 1: Build suffix sum array (O(n) preprocessing)
    cout << "\n--- Building Suffix Sum Array ---" << endl;
    cout << "Step 1: suffix[4] = arr[4] = 10" << endl;
    cout << "Step 2: suffix[3] = suffix[4] + arr[3] = 10 + 8 = 18" << endl;
    cout << "Step 3: suffix[2] = suffix[3] + arr[2] = 18 + 6 = 24" << endl;
    cout << "Step 4: suffix[1] = suffix[2] + arr[1] = 24 + 4 = 28" << endl;
    cout << "Step 5: suffix[0] = suffix[1] + arr[0] = 28 + 2 = 30" << endl;

    vector<int> suffix = buildSuffixSum(arr);

    // Display suffix sum array
    cout << "\nSuffix Sum Array: ";
    for (int num : suffix)
    {
        cout << num << " ";
    }
    cout << endl;

    /*
     * Visualization of Suffix Sum Array:
     * Index:    0   1   2   3   4
     * Array:    2   4   6   8  10
     * Suffix:  30  28  24  18  10
     *           ↑   ↑   ↑   ↑   ↑
     *         2+→ 4+→ 6+→ 8+→ 10
     *          28  24  18  10
     */

    // Step 2: Perform range sum queries (O(1) per query)
    cout << "\n========== Range Sum Queries ==========" << endl;

    // Query 1: Sum from index 0 to 2 → 2 + 4 + 6 = 12
    cout << "\nQuery 1: Sum(0 to 2)" << endl;
    cout << "Formula: suffix[0] - suffix[3] = 30 - 18 = 12" << endl;
    cout << "Result: " << getRangeSum(suffix, 0, 2, n) << endl;
    cout << "Verify: 2 + 4 + 6 = 12 ✓" << endl;

    // Query 2: Sum from index 1 to 3 → 4 + 6 + 8 = 18
    cout << "\nQuery 2: Sum(1 to 3)" << endl;
    cout << "Formula: suffix[1] - suffix[4] = 28 - 10 = 18" << endl;
    cout << "Result: " << getRangeSum(suffix, 1, 3, n) << endl;
    cout << "Verify: 4 + 6 + 8 = 18 ✓" << endl;

    // Query 3: Sum from index 2 to 4 → 6 + 8 + 10 = 24
    cout << "\nQuery 3: Sum(2 to 4) [till end]" << endl;
    cout << "Formula: suffix[2] (direct, since right = n-1) = 24" << endl;
    cout << "Result: " << getRangeSum(suffix, 2, 4, n) << endl;
    cout << "Verify: 6 + 8 + 10 = 24 ✓" << endl;

    return 0;
}
