#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void lcs(string &s1, string &s2)
{
    int m = s1.size();
    int n = s2.size();
    string LcsWord = "";

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    cout << "Length of LCS: " << dp[m][n] << endl;

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            LcsWord.push_back(s1[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    reverse(LcsWord.begin(), LcsWord.end());
    cout << "LCS: " << LcsWord << endl;
}

int main()
{
    string s1, s2;
    cout << "X = ";
    cin >> s1;
    cout << "Y = ";
    cin >> s2;
    lcs(s1, s2);
    return 0;
}
