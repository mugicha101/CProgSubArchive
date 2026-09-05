/*
Gold 3
27610 - A Musical Question
meta: {"problemId": 27610, "titleKo": "A Musical Question", "titles": [{"language": "en", "languageDisplayName": "en", "title": "A Musical Question", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 30, "level": 13, "votedUserCount": 4, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.333299994468689, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "knapsack", "isMeta": false, "bojTagId": 148, "problemCount": 345, "displayNames": [{"language": "ko", "name": "배낭 문제", "short": "배낭"}, {"language": "en", "name": "knapsack", "short": "knapsack"}, {"language": "ja", "name": "ナップサック問題", "short": "ナップサック"}], "aliases": [{"alias": "냅색"}]}], "metadata": {}}
*/

#include <bits/stdc++.h>
using namespace std;
int main(int argc, char **argv) {
    int c, n;
    cin >> c >> n;
    unordered_set<int> visited;
    vector<int> states;
    states.push_back(0);
    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;
        for (int i = states.size()-1; i >= 0; --i) {
            auto check = [&](int cd1, int cd2) {
                if (cd1 < cd2)
                    swap(cd1, cd2);
                int s = (cd1 << 16) | cd2;
                if (visited.count(s))
                    return;
                visited.insert(s);
                states.push_back(s);
            };
            if ((states[i] >> 16) + l <= c)
                check((states[i] >> 16) + l, states[i] & 0xffff);
            if ((states[i] & 0xffff) + l <= c)
                check((states[i] >> 16), (states[i] & 0xffff) + l);
        }
    }
    int best = 0;
    int bestSum = 0;
    int bestDiff = 0;
    for (auto& s : states) {
        int cd1 = s >> 16;
        int cd2 = s & 0xffff;
        int sum = cd1 + cd2;
        int diff = cd1 - cd2;
        if (sum < bestSum || (sum == bestSum && diff >= bestDiff))
            continue;
        best = s;
        bestSum = sum;
        bestDiff = diff;
    }
    cout << (best >> 16) << " " << (best & 0xffff) << "\n";
}
