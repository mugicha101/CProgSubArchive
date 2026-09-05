/*
Platinum 2
13547 - 수열과 쿼리 5
meta: {"problemId": 13547, "titleKo": "수열과 쿼리 5", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "수열과 쿼리 5", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1924, "level": 19, "votedUserCount": 291, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.2952001094818115, "official": true, "tags": [{"key": "offline_queries", "isMeta": false, "bojTagId": 123, "problemCount": 372, "displayNames": [{"language": "ko", "name": "오프라인 쿼리", "short": "오프라인 쿼리"}, {"language": "en", "name": "offline queries", "short": "offline query"}, {"language": "ja", "name": "offline queries", "short": "offline query"}], "aliases": [{"alias": "offlinequery"}]}, {"key": "mo", "isMeta": false, "bojTagId": 50, "problemCount": 51, "displayNames": [{"language": "ko", "name": "mo's", "short": "Mo's"}, {"language": "en", "name": "mo's", "short": "mo's"}, {"language": "ja", "name": "mo's", "short": "mo's"}], "aliases": [{"alias": "squarerootdecomposition"}, {"alias": "sqrtdecomposition"}, {"alias": "평방분할법"}]}], "metadata": {}}
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
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // input
    int n; cin >> n;
    vector<int> vals(n); vcin(vals);

    // setup window
    unordered_map<int,int> w;
    int unique = 0;
    auto add = [&](int x) {
        unique += x != -1 && ++w[x] == 1;
    };
    auto rem = [&](int x) {
        unique -= x != -1 && --w[x] == 0;
    };

    // mo's algo
    int b = (int)ceil(sqrt(n));
    int blocks = (n + b - 1) / b;
    vals.resize(blocks * b, -1);
    vector<vector<tuple<int,int,int>>> blockQueries(blocks);
    int k; cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r; cin >> l >> r; --l; --r;
        blockQueries[l / b].emplace_back(i, l, r);
    }
    for (int i = 0; i < blocks; ++i) {
        sort(all(blockQueries[i]), [&](auto &a, auto &b) {
            return get<2>(a) < get<2>(b);
        });
    }
    vector<int> ans(k);
    for (int i = 0; i < blocks; ++i) {
        w.clear();
        unique = 0;
        int wl = i * b;
        int wr = wl - 1;
        for (auto &[qi, l, r] : blockQueries[i]) {
            while (wr < r) add(vals[++wr]);
            while (wl > l) add(vals[--wl]);
            while (wl < l) rem(vals[wl++]);
            ans[qi] = unique;
        }
    }
    for (int x : ans) cout << x << "\n";
}
