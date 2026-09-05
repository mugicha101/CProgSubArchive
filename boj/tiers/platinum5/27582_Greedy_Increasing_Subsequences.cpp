/*
Platinum 5
27582 - Greedy Increasing Subsequences
meta: {"problemId": 27582, "titleKo": "Greedy Increasing Subsequences", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Greedy Increasing Subsequences", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 25, "level": 16, "votedUserCount": 5, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.5199999809265137, "official": true, "tags": [{"key": "binary_search", "isMeta": false, "bojTagId": 12, "problemCount": 1665, "displayNames": [{"language": "ko", "name": "이분 탐색", "short": "이분 탐색"}, {"language": "en", "name": "binary search", "short": "binary search"}, {"language": "ja", "name": "二分探索", "short": "二分探索"}], "aliases": [{"alias": "이분탐색"}, {"alias": "이진탐색"}]}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}], "metadata": {}}
*/

#include <unordered_set>
#include <bits/stdc++.h>

typedef long long ll;
#define INPUT false

using namespace std;

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    int n;
    cin >> n;
    vector<vector<int>> output;
    int x;
    while (n--) {
        cin >> x;
        // binary search for output to append to
        int l = 0; // max in bounds
        int r = output.size(); // min in bounds
        while (l < r) {
            int m = ((l + r) >> 1);
            if (output[m].back() >= x)
                l = m+1;
            else
                r = m;
        }
        if (l == output.size())
            output.push_back(vector<int>(1,x));
        else
            output[l].push_back(x);
    }
    cout << output.size() << "\n";
    for (int i = 0; i < output.size(); ++i) {
        for (int x : output[i])
            cout << x << " ";
        cout << "\n";
    }
}
