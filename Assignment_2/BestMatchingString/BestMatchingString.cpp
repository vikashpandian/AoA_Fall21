#include <iostream>
#include <vector>

using namespace std;

int frequency[26] = { 812, 149, 271, 432, 1202, 230, 203, 592, 731, 10, 69, 398, 261, 695, 768, 182, 11, 602, 628, 910, 288, 111, 209, 17, 211, 7 };

string findBestMatchingString(string a, string b, int penalty) 
{
    int m = a.length();
    int n = b.length();
    vector<vector<pair<int, int>>> dp(2, vector<pair<int, int>>(n + 1, { 0,0 }));
    string res = "";
    int maxWeight = 0;

    for (int i = 1; i <= m; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            if (a[i - 1] == b[j - 1]) 
            {
                dp[i % 2][j].first = dp[(i - 1) % 2][j - 1].first + 1;
                dp[i % 2][j].second = dp[(i - 1) % 2][j - 1].second + frequency[a[i - 1] - 'A'];
                if (dp[i % 2][j].second > maxWeight) 
                {
                    maxWeight = dp[i % 2][j].second;
                    res = a.substr(i - dp[i % 2][j].first, i);
                }
            }
            else if (dp[(i - 1) % 2][j - 1].second > 0) 
            {
                dp[i % 2][j].first = dp[(i - 1) % 2][j - 1].first + 1;
                dp[i % 2][j].second = dp[(i - 1) % 2][j - 1].second - penalty;
            }
        }
    }
    return res;
}

int main(void) {
    string a = "ABBCAACCBBBBBB";
    string b = "ABCAABCAA";
    int penalty = 10;
    cout << "String 1 : " << a << "\n" <<"String 2 : " << b << "\n Penalty : " << penalty << "\nLCS: " << findBestMatchingString(a, b, penalty) << "\n\n\n";
}
