/*
Gold 2
31523 - Balanced Tree Path
meta: {"problemId": 31523, "titleKo": "Balanced Tree Path", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Balanced Tree Path", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 35, "level": 14, "votedUserCount": 9, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.114300012588501, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "dfs", "isMeta": false, "bojTagId": 127, "problemCount": 964, "displayNames": [{"language": "ko", "name": "깊이 우선 탐색", "short": "깊이 우선 탐색"}, {"language": "en", "name": "depth-first search", "short": "dfs"}, {"language": "ja", "name": "深さ優先探索", "short": "dfs"}], "aliases": [{"alias": "depth first"}, {"alias": "depthfirst"}]}, {"key": "stack", "isMeta": false, "bojTagId": 71, "problemCount": 493, "displayNames": [{"language": "ko", "name": "스택", "short": "스택"}, {"language": "en", "name": "stack", "short": "stack"}, {"language": "ja", "name": "スタック", "short": "スタック"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

vector<vector<int>> adj;
vector<char> seq;
vector<char> pstack;

int dfs(int p, int i) {
    int sum = 0;
    auto next = [&]() {
        for (int j : adj[i]) {
            if (j == p) continue;
            sum += dfs(i, j);
        }
    };
    if (seq[i] & 0b100) {
        if (pstack.empty() || pstack.back() != seq[i])
            return 0;
        char t = pstack.back();
        pstack.pop_back();
        sum += pstack.empty();
        next();
        pstack.push_back(t);
    } else {
        pstack.push_back(seq[i] | 0b100);
        next();
        pstack.pop_back();
    }
    return sum;
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    int n;
    cin >> n;
    string str;
    cin >> str;
    seq.resize(n);
    for (int i = 0; i < n; ++i) {
        switch (str[i]) {
            case '(': seq[i] = 0b001; break;
            case '[': seq[i] = 0b010; break;
            case '{': seq[i] = 0b011; break;
            case ')': seq[i] = 0b101; break;
            case ']': seq[i] = 0b110; break;
            case '}': seq[i] = 0b111; break;
        }
    }
    adj.resize(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int count = 0;
    for (int i = 0; i < n; ++i) {
        count += dfs(-1, i);
    }
    cout << count << endl;
}

