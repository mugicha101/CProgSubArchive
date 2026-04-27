/*
Gold 3
27580 - Family Visits
meta: {"problemId": 27580, "titleKo": "Family Visits", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Family Visits", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 31, "level": 13, "votedUserCount": 3, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.19350004196167, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "priority_queue", "isMeta": false, "bojTagId": 59, "problemCount": 575, "displayNames": [{"language": "ko", "name": "우선순위 큐", "short": "우선순위 큐"}, {"language": "en", "name": "priority queue", "short": "priority queue"}, {"language": "ja", "name": "優先度付きキュー", "short": "優先度付きキュー"}], "aliases": [{"alias": "heap"}, {"alias": "힙"}]}], "metadata": {}}
*/

#include <unordered_set>
#include <bits/stdc++.h>

typedef long long ll;
#define INPUT false

using namespace std;

int handleVisit(vector<int>& mess, vector<int>& clean, vector<int>& prefixMess, vector<int>& prefixClean, int firstDay, int visitDay) {
    vector<int> heap; // possible remaining cleans
    int messSum = 0;
    for (int i = visitDay; i >= firstDay; --i) {
        messSum += mess[i];
        heap.push_back(clean[i]);
        push_heap(heap.begin(), heap.end());
        while (!heap.empty() && messSum > 0) {
            pop_heap(heap.begin(), heap.end());
            messSum -= heap.back();
            heap.pop_back();
        }
        if (messSum > 0) {
            return -1;
        }
    }
    return visitDay - firstDay + 1 - heap.size();
}

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    int days, visits;
    cin >> days >> visits;
    vector<int> clean(days);
    vector<int> mess(days);
    vector<int> prefixClean(1,0);
    vector<int> prefixMess(1,0);
    vector<int> visitDays(visits, 0);
    prefixClean.reserve(days + 1);
    prefixMess.reserve(days + 1);
    for (int i = 0; i < days; ++i) {
        cin >> mess[i] >> clean[i];
        prefixMess.push_back(prefixMess.back() + mess[i]);
        prefixClean.push_back(prefixClean.back() + clean[i]);
    }
    for (int i = 0; i < visits; ++i) {
        cin >> visitDays[i];
        --visitDays[i];
    }
    int totalCleans = 0;
    int firstDay = 0;
    for (int visitDay : visitDays) {
        int cleans = handleVisit(mess, clean, prefixMess, prefixClean, firstDay, visitDay);
        if (cleans == -1) {
            cout << -1 << "\n";
            return 0;
        }
        totalCleans += cleans;
        firstDay = visitDay + 1;
    }
    cout << totalCleans << "\n";
}