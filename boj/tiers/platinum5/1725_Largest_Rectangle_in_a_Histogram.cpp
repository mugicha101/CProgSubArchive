/*
Platinum 5
1725 - Largest Rectangle in a Histogram
meta: {"problemId": 1725, "titleKo": "히스토그램", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "히스토그램", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Largest Rectangle in a Histogram", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 9161, "level": 16, "votedUserCount": 439, "sprout": false, "givesNoRating": true, "isLevelLocked": false, "averageTries": 2.468899965286255, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "divide_and_conquer", "isMeta": false, "bojTagId": 24, "problemCount": 509, "displayNames": [{"language": "ko", "name": "분할 정복", "short": "분할 정복"}, {"language": "en", "name": "divide and conquer", "short": "d&c"}, {"language": "ja", "name": "分割統治法", "short": "分割統治法"}], "aliases": [{"alias": "dnc"}]}, {"key": "stack", "isMeta": false, "bojTagId": 71, "problemCount": 493, "displayNames": [{"language": "ko", "name": "스택", "short": "스택"}, {"language": "en", "name": "stack", "short": "stack"}, {"language": "ja", "name": "スタック", "short": "スタック"}], "aliases": []}], "metadata": {"warn": [{"type": "same", "data": 6549}]}}
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

// extend a using b
void extendKnap(vector<ll> &a, vector<ll> &b) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; i + j < n; ++j) {
            a[i + j] = min(a[i + j], a[i] + b[j]);
        }
    }
}

int dfs(vector<vector<ll>> &knap, vector<ll> &cost, vector<vector<int>> &adj, int curr) {
    int subtreeSize = 1;
    for (int next : adj[curr]) {
        subtreeSize += dfs(knap, cost, adj, next);
        extendKnap(knap[curr], knap[next]);
    }
    knap[curr][subtreeSize] = min(knap[curr][subtreeSize], cost[curr]);
    return subtreeSize;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<int> hist(n); vcin(hist);
    hist.push_back(0);
    vector<pair<int,int>> s; // height -> start
    s.emplace_back(0,-1);
    ll maxArea = 0;
    for (int i = 0; i <= n; ++i) {
        while (s.back().first > hist[i]) {
            maxArea = max(maxArea, (ll)(i - s.back().second) * (ll)s.back().first);
            s.pop_back();
        }
        if (s.back().first < hist[i]) s.emplace_back(hist[i], s.back().second+1);
        s.emplace_back(hist[i], i);
    }
    cout << maxArea << "\n";
}
