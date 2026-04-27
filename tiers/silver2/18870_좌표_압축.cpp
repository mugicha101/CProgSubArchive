/*
Silver 2
18870 - 좌표 압축
meta: {"problemId": 18870, "titleKo": "좌표 압축", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "좌표 압축", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 45289, "level": 9, "votedUserCount": 245, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.431999921798706, "official": true, "tags": [{"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "coordinate_compression", "isMeta": false, "bojTagId": 161, "problemCount": 314, "displayNames": [{"language": "ko", "name": "값 / 좌표 압축", "short": "값 / 좌표 압축"}, {"language": "en", "name": "value / coordinate compression", "short": "compression"}, {"language": "ja", "name": "value / coordinate compression", "short": "compression"}], "aliases": [{"alias": "zip"}]}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<int> vals(n);
    for (int &x : vals) cin >> x;
    vector<int> order(n);
    vector<int> rank(n);
    iota(all(order), 0);
    sort(all(order), [&](int i, int j) {
        return vals[i] < vals[j];
    });
    rank[order[0]] = 0;
    for (int i = 1; i < n; ++i) {
        rank[order[i]] = rank[order[i-1]] + (vals[order[i-1]] < vals[order[i]]);
    }
    for (int x : rank) cout << x << " ";
    cout << endl;
}
