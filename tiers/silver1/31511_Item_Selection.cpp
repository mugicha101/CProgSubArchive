/*
Silver 1
31511 - Item Selection
meta: {"problemId": 31511, "titleKo": "Item Selection", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Item Selection", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 33, "level": 10, "votedUserCount": 4, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.272700071334839, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "simulation", "isMeta": false, "bojTagId": 141, "problemCount": 1369, "displayNames": [{"language": "ko", "name": "시뮬레이션", "short": "시뮬레이션"}, {"language": "en", "name": "simulation", "short": "simulation"}, {"language": "ja", "name": "シミュレーション", "short": "シミュレーション"}], "aliases": []}], "metadata": {}}
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

    int numItems, numPageItems, startPage, numPre, numWant;
    cin >> numItems >> numPageItems >> startPage >> numPre >> numWant;
    --startPage;
    int numPages = (numItems + numPageItems - 1) / numPageItems;

    vector<bool> presel(numItems);
    vector<bool> want(numItems);
    for (int i = 0; i < numPre; ++i) {
        int x; cin >> x; --x;
        presel[x] = true;
    }
    for (int i = 0; i < numWant; ++i) {
        int x; cin >> x; --x;
        want[x] = true;
    }

    int totalOps = 0;
    int firstPage = startPage;
    int lastPage = startPage;
    for (int pageNum = 0; pageNum < numPages; ++pageNum) {
        int start = pageNum * numPageItems;
        int end = min((pageNum + 1) * numPageItems, numItems);
        int numWanted = 0;
        int numDiff = 0;
        for (int i = start; i < end; ++i) {
            numDiff += presel[i] ^ want[i];
            numWanted += want[i];
        }
        int pageOps = min(numDiff, min(numWanted + 1, (end - start) - numWanted + 1));
        if (pageOps) {
            firstPage = min(firstPage, pageNum);
            lastPage = max(lastPage, pageNum);
        }
        totalOps += pageOps;
    }
    int leftDist = startPage - firstPage;
    int rightDist = lastPage - startPage;
    totalOps += min(leftDist * 2 + rightDist, rightDist * 2 + leftDist);
    cout << totalOps << "\n";
}
