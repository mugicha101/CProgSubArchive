/*
Gold 1
31506 - ABC String
meta: {"problemId": 31506, "titleKo": "ABC String", "titles": [{"language": "en", "languageDisplayName": "en", "title": "ABC String", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 59, "level": 15, "votedUserCount": 9, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.5254000425338745, "official": true, "tags": [{"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}], "metadata": {}}
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    string s;
    cin >> s;
    int counts[3] = {0,0,0};
    int maxSeq = 0;
    for (char x : s) {
        ++counts[x-'A'];
        int minV = min(min(counts[0], counts[1]), counts[2]);
        for (int i = 0; i < 3; ++i) counts[i] -= minV;
        int maxV = max(max(counts[0], counts[1]), counts[2]);
        maxSeq = max(maxSeq, maxV);
    }
    cout << maxSeq << "\n";
}
