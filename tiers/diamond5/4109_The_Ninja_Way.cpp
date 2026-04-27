/*
Diamond 5
4109 - The Ninja Way
meta: {"problemId": 4109, "titleKo": "The Ninja Way", "titles": [{"language": "en", "languageDisplayName": "en", "title": "The Ninja Way", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 18, "level": 21, "votedUserCount": 7, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.6110999584198, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}, {"key": "bellman_ford", "isMeta": false, "bojTagId": 10, "problemCount": 49, "displayNames": [{"language": "ko", "name": "벨만–포드", "short": "벨만–포드"}, {"language": "en", "name": "bellman–ford", "short": "bellman-ford"}, {"language": "ja", "name": "ベルマンフォード法", "short": "ベルマンフォード"}], "aliases": [{"alias": "bellmanford"}, {"alias": "벨만포드"}, {"alias": "spfa"}]}], "metadata": {}}
*/

    #include <bits/stdc++.h>
    
    using namespace std;
    
    typedef long long ll;
    typedef long double ld;
    typedef unsigned long long ull;
    
    const int MOD = 1000000007;

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

    using namespace std;

    using ll = long long;
    const ll INF = LLONG_MAX >> 2;

    #define sz(x) ((int)x.size())
    #define all(x) x.begin(), x.end()
    #define rep(i,a,b) for (int i = a; i < b; ++i)

    int main() {
        // env setup
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        // cout.tie(0); // comment out for baekjoon
        cout << fixed << setprecision(12);

        while (true) {
            // cout << "AAAAA" << endl;
            int n;
            ll d;
            cin >> n >> d;
            if (n == 0) break;

            vector<int> trees(n);
            for (int &h : trees) cin >> h;

            vector<int> order(n);
            iota(all(order), 0);
            sort(all(order), [&](int i, int j) {
                return trees[i] < trees[j];
            });

            // find range between shortest and tallest
            int first = order.front();
            int last = order.back();
            if (first > last) swap(first, last);

            // construct edges
            vector<pair<int,int>> edges(n-1);
            for (int i = 1; i < n; ++i) {
                edges[i-1] = make_pair(order[i-1], order[i]);
                if (order[i-1] > order[i]) swap(edges[i-1].first, edges[i-1].second);
            }

            // initialize positions to as close as possible
            vector<ll> pos(n);
            iota(pos.begin(), pos.end(), 0);

            // check if initial state feasible
            bool valid = true;
            for (auto [a, b] : edges) {
                if (pos[b] - pos[a] > d) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                cout << -1 << endl;
                continue;
            }

            // perform shifts to elements after smallest tree up till largest tree
            for (int i = first+1; i <= last; ++i) {
                // find shift amount
                ll shift = d;
                for (auto [a, b] : edges) {
                    if (a >= i || b < i) continue;

                    // a fixed, b shifts
                    shift = min(shift, pos[a] + d - pos[b]);
                }
                if (shift < 0) exit(-1);

                // shift
                for (int j = i; j < n; ++j) {
                    pos[j] += shift;
                }
            }
            
            cout << pos[last] - pos[first] << endl;
        }
    }
