/*
Gold 4
9663 - N-Queen
meta: {"problemId": 9663, "titleKo": "N-Queen", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "N-Queen", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 48370, "level": 12, "votedUserCount": 391, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.0957999229431152, "official": true, "tags": [{"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "backtracking", "isMeta": false, "bojTagId": 5, "problemCount": 656, "displayNames": [{"language": "ko", "name": "백트래킹", "short": "백트래킹"}, {"language": "en", "name": "backtracking", "short": "backtrack"}, {"language": "ja", "name": "バックトラック法", "short": "バックトラック"}], "aliases": [{"alias": "백트래킹"}, {"alias": "퇴각검색"}, {"alias": "퇴각 검색"}]}], "metadata": {}}
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

class Solution {
public:
    int n;
    vector<int8_t> colState;
    vector<int8_t> rightDiagState;
    vector<int8_t> leftDiagState;

    int dfs(int r) {
        if (r == n) {
            return 1;
        }
        int sum = 0;
        for (int c = 0; c < n; ++c) {
            if (colState[c] || leftDiagState[r+c] || rightDiagState[n-1-r+c])
                continue;
            ++colState[c];
            ++leftDiagState[r+c];
            ++rightDiagState[n-1-r+c];
            sum += dfs(r+1);
            --colState[c];
            --leftDiagState[r+c];
            --rightDiagState[n-1-r+c];
        }
        return sum;
    }
    int solveNQueens(int n) {
        this->n = n;
        colState.resize(n);
        rightDiagState.resize(n + n - 1);
        leftDiagState.resize(n + n - 1);
        return dfs(0);
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n;
    cin >> n;
    Solution s;
    cout << s.solveNQueens(n) << endl;
}
