// 2024-02-20 14:50:19 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false

typedef long long ll;
typedef long double ld;

typedef pair<int,int> point;
typedef pair<point,point> line;
point zeroPoint = make_pair(0,0);
line zeroLine = make_pair(zeroPoint, zeroPoint);

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    // get words
    vector<string> words;
    unordered_set<string> seen;
    while (true) {
        string line;
        cin >> line;
        if (line == "***") break;
        line.push_back(' ');
        string word = "";
        for (char c : line) {
            if (c == ' ' || c == '\r' || c == '\n') {
                if (word.empty() || seen.count(word)) continue;
                seen.insert(word);
                words.push_back(word);
                word.clear();
            } else {
                if (c >= 'A' && c <= 'Z')
                    c += 'a'-'A';
                else if (c < 'a' || c > 'z')
                    continue;
                word += c;
            }
        }
    }
    sort(words.begin(), words.end());

    // compare words
    // delete op equiv to insert op on other word
    int n = words.size();
    vector<vector<int>> adj(n);
    bool similar = false;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int minIndex = words[i].size() <= words[j].size() ? i : j;
            int maxIndex = i == minIndex ? j : i;
            string& a = words[minIndex];
            string& b = words[maxIndex];
            bool valid = false;
            if (a.size()+1 == b.size()) {
                // insert into a
                int inserts = 0;
                for (int i = 0; inserts != 2 && i < b.size(); ++i)
                    inserts += a[i-inserts] != b[i];
                valid = inserts == 1;
            } else if (a.size() == b.size()) {
                // swap adjacent or replace one
                int di[2];
                int diff = 0;
                for (int i = 0; diff != 3 && i < a.size(); ++i) {
                    if (a[i] == b[i]) continue;
                    di[diff++] = i;
                }
                if (diff == 1) valid = true; // replace one
                else if (diff == 2) // swap adjacent
                    valid = di[0]+1 == di[1] && a[di[0]] == b[di[1]] && a[di[1]] == b[di[0]];
            }
            if (!valid) continue;
            similar = true;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    if (!similar) {
        cout << "***" << endl;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (adj[i].empty()) continue;
        cout << words[i] << ":";
        for (int j : adj[i])
            cout << " " << words[j];
        cout << endl;
    }
}

