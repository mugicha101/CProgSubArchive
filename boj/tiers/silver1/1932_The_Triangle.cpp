/*
Silver 1
1932 - The Triangle
meta: {"problemId": 1932, "titleKo": "정수 삼각형", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "정수 삼각형", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "The Triangle", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 54120, "level": 10, "votedUserCount": 219, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.651900053024292, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}], "metadata": {}}
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

// E = T ( ( + | - ) T )*
// T = A ( ( * | / ) A )*
// A = literal | LParen E RParen

void parseE(string &s, string &t, size_t &i);

void parseA(string &s, string &t, size_t &i) {
    if (s[i] == '(') {
        parseE(s, t, ++i);
        assert(s[i++] == ')');
    }

    if (s[i] >= 'A' && s[i] <= 'Z') {
        t += s[i++];
    }
}

void parseT(string &s, string &t, size_t &i) {
    parseA(s, t, i);

    while (s[i] == '*' || s[i] == '/') {
        char op = s[i++];
        parseA(s, t, i);
        t += op;
    }
}

void parseE(string &s, string &t, size_t &i) {
    parseT(s, t, i);

    while (s[i] == '+' || s[i] == '-') {
        char op = s[i++];
        parseT(s, t, i);
        t += op;
    }
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<vector<int>> layers(n);
    layers[0].resize(1);
    cin >> layers[0][0];
    for (int i = 1; i < n; ++i) {
        layers[i].resize(i+1);
        for (int &x : layers[i]) cin >> x;
        layers[i][0] += layers[i-1][0];
        for (int j = 1; j < i; ++j) {
            layers[i][j] += max(layers[i-1][j-1], layers[i-1][j]);
        }
        layers[i][i] += layers[i-1][i-1];
    }
    cout << *max_element(all(layers.back())) << endl;
}
