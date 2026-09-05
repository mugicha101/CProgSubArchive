/*
Gold 3
9252 - LCS 2
meta: {"problemId": 9252, "titleKo": "LCS 2", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "LCS 2", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 17575, "level": 13, "votedUserCount": 312, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.499500036239624, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "traceback", "isMeta": false, "bojTagId": 235, "problemCount": 216, "displayNames": [{"language": "ko", "name": "역추적", "short": "역추적"}, {"language": "en", "name": "traceback", "short": "traceback"}], "aliases": []}, {"key": "lcs", "isMeta": false, "bojTagId": 219, "problemCount": 34, "displayNames": [{"language": "ko", "name": "최장 공통 부분 수열 문제", "short": "최장 공통 부분 수열"}, {"language": "en", "name": "longest common subsequence", "short": "lcs"}], "aliases": []}], "metadata": {}}
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
#define each(i, x) for (auto &i : x)
#define fill(x) for (auto &_e : x) cin >> _e;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    string a, b; cin >> a >> b;

    // dp state: dp[i][j] = (longest subsequence of a[0..<i] and b[0..<j], transition type)
    vector<vector<pair<int,char>>> dp(a.size()+1, vector<pair<int,char>>(b.size()+1));
    int cap = a.size() + b.size();
    for (int d = 1; d <= cap; ++d) {
        for (int i = 1; i <= (int)a.size(); ++i) {
            int j = d - i;
            if (j <= 0 || j > (int)b.size()) continue;

            if (dp[i-1][j].first >= dp[i][j-1].first) {
                dp[i][j] = make_pair(dp[i-1][j].first, 'I');
            } else {
                dp[i][j] = make_pair(dp[i][j-1].first, 'J');
            }
            if (a[i-1] == b[j-1] && dp[i][j].first < dp[i-1][j-1].first + 1) {
                dp[i][j] = make_pair(dp[i-1][j-1].first + 1, 'B');
            }
        }
    }
    pair<int,int> curr = make_pair((int)a.size(), (int)b.size());
    string out;
    out.reserve(dp[curr.first][curr.second].first);
    while (curr.first && curr.second) {
        auto [len, type] = dp[curr.first][curr.second];
        if (type == 'I') {
            --curr.first;
        } else if (type == 'J') {
            --curr.second;
        } else {
            --curr.first;
            --curr.second;
            out += a[curr.first];
        }
    }
    reverse(all(out));
    cout << out.size() << endl << out << endl;
}
