/*
Silver 3
15654 - N과 M (5)
meta: {"problemId": 15654, "titleKo": "N과 M (5)", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "N과 M (5)", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 32978, "level": 8, "votedUserCount": 62, "sprout": false, "givesNoRating": false, "isLevelLocked": true, "averageTries": 1.3877999782562256, "official": true, "tags": [{"key": "backtracking", "isMeta": false, "bojTagId": 5, "problemCount": 656, "displayNames": [{"language": "ko", "name": "백트래킹", "short": "백트래킹"}, {"language": "en", "name": "backtracking", "short": "backtrack"}, {"language": "ja", "name": "バックトラック法", "short": "バックトラック"}], "aliases": [{"alias": "백트래킹"}, {"alias": "퇴각검색"}, {"alias": "퇴각 검색"}]}], "metadata": {}}
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

void dfs(vector<int> &vals, vector<int> &curr, int i) {
    if (i == (int)curr.size()) {
        for (int x : curr) cout << x << " ";
        cout << "\n";
        return;
    }

    for (int j = 0; j < (int)vals.size(); ++j) {
        if (vals[j] == -1) continue;

        curr[i] = vals[j];
        vals[j] = -1;
        dfs(vals, curr, i+1);
        vals[j] = curr[i];
    }
}
int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, k; cin >> n >> k;
    vector<int> vals(n);
    for (int &x : vals) cin >> x;
    sort(all(vals));
    vector<int> curr(k);
    dfs(vals, curr, 0);
}
