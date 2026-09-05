#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(false);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    string s;
    getline(cin, s);
    vector<string> digs = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    vector<vector<int>> adjList(s.size(), vector<int>(1,1));
    for (int i = 0; i < s.size(); ++i) {
        bitset<10> dset;
        for (int j = 0; j < 10; ++j) {
            if (s.size() - i < digs[j].size())
                continue;
            bool match = true;
            for (int k = 0; match && k < digs[j].size(); ++k)
                match = digs[j][k] == s[i+k];
            if (match) {
                adjList[i].push_back(digs[j].size());
                break;
            }
        }
    }

    vector<int> minDist(s.size()+1, INT_MAX);
    vector<int> ways(s.size()+1, 0);
    minDist[0] = 0;
    ways[0] = 1;
    const int MOD = 9302023;
    for (int i = 0; i < s.size(); ++i) {
        for (int nb : adjList[i]) {
            int j = i + nb;
            if (minDist[j] >= minDist[i]+1) {
                if (minDist[j] > minDist[i]+1)
                    ways[j] = 0;
                minDist[j] = minDist[i]+1;
                ways[j] += ways[i];
                ways[j] = ways[j] >= MOD ? ways[j] - MOD : ways[j];
            }
        }
    }
    cout << minDist.back() << endl;
    cout << ways.back() << endl;
}
