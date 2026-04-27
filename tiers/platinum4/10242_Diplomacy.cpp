/*
Platinum 4
10242 - Diplomacy
meta: {"problemId": 10242, "titleKo": "Diplomacy", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Diplomacy", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 31, "level": 17, "votedUserCount": 7, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.67739999294281, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "ad_hoc", "isMeta": false, "bojTagId": 109, "problemCount": 2310, "displayNames": [{"language": "ko", "name": "애드 혹", "short": "애드 혹"}, {"language": "en", "name": "ad-hoc", "short": "ad-hoc"}, {"language": "ja", "name": "アドホック", "short": "アドホック"}], "aliases": []}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);
    while (true) {
        // want to flip friends of opposite parties (frenemies)
        // greedy: pick node that would reduce components by most
        int n, m; cin >> n >> m;
        if (n == 0 && m == 0) break;

        vector<int> colors(n); for (auto &x : colors) {
            cin >> x; ++x;
        }
        vector<vector<int>> adj(n);
        for (int i = 0; i < m; ++i) {
            int a, b; cin >> a >> b; --a; --b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        auto numComps = [&adj, n](vector<int> &colors) {
            queue<int> q;
            int comps = 0;
            for (int root = 0; root < n; ++root) {
                if (colors[root] < 0) continue;

                ++comps;
                int c = colors[root];
                colors[root] = -c;
                q.emplace(root);
                while (!q.empty()) {
                    int curr = q.front();
                    q.pop();
                    for (int next : adj[curr]) {
                        if (colors[next] != c) continue;
    
                        colors[next] = -c;
                        q.push(next);
                    }
                }
            }

            for (int &c : colors) c = -c;
            return comps;
        };

        auto flip = [&adj, n](vector<int> &colors, int target) {
            queue<int> q;
            int c = colors[target];
            colors[target] = 3 - c;
            q.push(target);
            while (!q.empty()) {
                int curr = q.front();
                q.pop();
                for (int next : adj[curr]) {
                    if (colors[next] != c) continue;

                    colors[next] = 3 - c;
                    q.push(next);
                }
            }
        };
        
        // theory: optimal solution can be done by flipping same tile repeatedly
        int best = INT_MAX;
        for (int i = 0; i < n; ++i) {
            int days = 0;
            vector<int> t = colors;
            while (numComps(t) > 1) {
                ++days;
                flip(t, i);
            }
            best = min(best, days);
        }
        cout << best << "\n";
    }
}

/*
1(0) - 2(1) - 4(0)
        |
       3(0)



*/