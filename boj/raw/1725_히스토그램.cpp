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
