/*
Platinum 5
16287 - Parcel
meta: {"problemId": 16287, "titleKo": "Parcel", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Parcel", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1601, "level": 16, "votedUserCount": 203, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.3078999519348145, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "mitm", "isMeta": false, "bojTagId": 46, "problemCount": 124, "displayNames": [{"language": "ko", "name": "중간에서 만나기", "short": "중간에서 만나기"}, {"language": "en", "name": "meet in the middle", "short": "meet in the middle"}, {"language": "ja", "name": "半分全列挙", "short": "半分全列挙"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
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
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int w, n; cin >> w >> n;
    vector<int> vals(n); vcin(vals);
    sort(all(vals));
    
    int numPairs = (n - 1) * n >> 1;
    vector<int> lowVals(w+1);
    vector<pair<int,int>> low;
    vector<pair<int,int>> high;
    low.reserve(numPairs);
    high.reserve(numPairs);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (vals[i] + vals[j] <= w) high.emplace_back(j, i);
        }
        for (int j = i+1; j < n; ++j) {
            if (vals[i] + vals[j] <= w) {
                low.emplace_back(i, j);
                ++lowVals[vals[i] + vals[j]];
            }
        }
    }
    int nextLow = 0;
    int p = low.size();
    for (auto [i, j] : high) {
        while (nextLow < p && low[nextLow].first <= j) {
            --lowVals[vals[low[nextLow].first] + vals[low[nextLow].second]];
            ++nextLow;
        }
        int v = vals[i] + vals[j];
        if (lowVals[w - v]) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}
