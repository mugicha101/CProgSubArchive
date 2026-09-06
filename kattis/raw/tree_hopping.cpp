// 2023-02-23 23:39:59 
#include <unordered_set>
#include <bits/stdc++.h>

#define INPUT false

using namespace std;

void dfs(vector<vector<int>>& adjList, vector<int>& parentList, int node) {
    for (int i : adjList[node]) {
        if (i == parentList[node])
            continue;
        parentList[i] = node;
        dfs(adjList, parentList, i);
    }
}

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    // Tree Hopping
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // construct graph
        vector<vector<int>> adjList(n);
        for (int i = 1; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            adjList[a].push_back(b);
            adjList[b].push_back(a);
        }

        // preprocess graph
        vector<int> parentList(n, -1);
        dfs(adjList, parentList, 0);

        // handle permutation
        vector<int> perm(n);
        for (int i = 0; i < n; ++i) {
            cin >> perm[i];
            --perm[i];
        }
        bool valid = true;
        for (int i = 1; valid && i < n; ++i) {
            auto check = [&](int a, int b) {
                int pa = parentList[a];
                int pb = parentList[b];
                if (pa == -1)
                    return false;
                if (pa == b || pa == pb)
                    return true;
                int gpa = parentList[pa];
                return gpa != -1 && (gpa == pb || gpa == b || parentList[gpa] == b);
            };
            valid = check(perm[i-1], perm[i]) || check(perm[i], perm[i-1]);
        }
        cout << valid << '\n';
    }
}
