// 2023-10-11 18:52:28 
#include <unordered_set>
#include <bits/stdc++.h>
 
typedef long long ll;
typedef long double ld;
#define INPUT false
 
using namespace std;

const int INF = 1 << 25;

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    // cin.tie(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    // input
    int nodes, edges;
    cin >> nodes >> edges;
    vector<vector<int>> adjList(nodes);
    for (int i = 0; i < edges; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }
    vector<int> seq(nodes);
    for (int i = 0; i < nodes; ++i) {
        cin >> seq[i];
        --seq[i];
    }

    // sort nodes by order in sequence
    vector<int> invSeq(nodes);
    for (int i = 0; i < nodes; ++i)
        invSeq[seq[i]] = i;
    auto cmp = [&](int i, int j) {
        return invSeq[i] < invSeq[j];
    };
    for (auto& row : adjList)
        sort(row.begin(), row.end(), cmp);
    
    // bash
    vector<bool> bread(nodes, false);
    deque<int> queue;
    vector<int> visited(nodes);
    vector<int> temp(nodes); // spare memory pool used for adding bread to front of queue in right order
    int breadCount = 0;
    while (true) {
        // reset state
        queue.clear();
        queue.push_back(0);
        for (int i = 0; i < nodes; ++i)
            visited[i] = false;

        // try traversing, set error to bread
        int i;
        for (i = 0; i < nodes; ++i) {
            while (!queue.empty() && visited[queue.front()])
                queue.pop_front();
            if (queue.empty() || queue.front() != seq[i])
                break;
            int curr = queue.front();
            visited[curr] = true;
            queue.pop_front();
            int p = 0;
            for (int nb : adjList[curr]) {
                if (visited[nb])
                    continue;
                if (bread[nb])
                    temp[p++] = nb;
                else
                    queue.push_back(nb);
            }
            while (p--)
                queue.push_front(temp[p]);
        }
        if (i == nodes) // finished
            break;
        else {
            ++breadCount;
            if (bread[seq[i]])
                return -1;
            bread[seq[i]] = true;
        }
    }
    cout << breadCount << endl;
}
