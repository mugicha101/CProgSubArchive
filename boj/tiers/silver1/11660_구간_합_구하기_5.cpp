/*
Silver 1
11660 - 구간 합 구하기 5
meta: {"problemId": 11660, "titleKo": "구간 합 구하기 5", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "구간 합 구하기 5", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 37465, "level": 10, "votedUserCount": 103, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 2.226799964904785, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "prefix_sum", "isMeta": false, "bojTagId": 139, "problemCount": 1379, "displayNames": [{"language": "ko", "name": "누적 합", "short": "누적 합"}, {"language": "en", "name": "prefix sum", "short": "prefix sum"}, {"language": "ja", "name": "累積和", "short": "累積和"}], "aliases": [{"alias": "구간합"}, {"alias": "부분합"}, {"alias": "rangesum"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
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

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())

struct Matrix {
    ll v[4] = {};
    Matrix(ll a = 0, ll b = 0, ll c = 0, ll d = 0) {
        v[0] = a;
        v[1] = b;
        v[2] = c;
        v[3] = d;
    }

    Matrix operator *(Matrix o) {
        return {
            (v[0] * o.v[0] + v[1] * o.v[2]) % MOD, (v[0] * o.v[1] + v[1] * o.v[3]) % MOD,
            (v[2] * o.v[0] + v[3] * o.v[2]) % MOD, (v[2] * o.v[1] + v[3] * o.v[3]) % MOD
        };
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, q; cin >> n >> q;
    vector<vector<ll>> psum(n+1, vector<ll>(n+1));
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            ll x; cin >> x;
            psum[r+1][c+1] = x + psum[r][c+1] + psum[r+1][c] - psum[r][c];
        }
    }
    while (q--) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        cout << psum[x2][y2] - psum[x1-1][y2] - psum[x2][y1-1] + psum[x1-1][y1-1] << "\n";
    }
}
