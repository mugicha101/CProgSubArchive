/*
Platinum 2
3321 - Logs
meta: {"problemId": 3321, "titleKo": "가장 큰 직사각형", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "가장 큰 직사각형", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Logs", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 169, "level": 19, "votedUserCount": 28, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.1656999588012695, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "sweeping", "isMeta": false, "bojTagId": 106, "problemCount": 708, "displayNames": [{"language": "ko", "name": "스위핑", "short": "스위핑"}, {"language": "en", "name": "sweeping", "short": "sweeping"}, {"language": "ja", "name": "平面走査", "short": "平面走査"}], "aliases": [{"alias": "라인 스위핑"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int rows, cols; cin >> rows >> cols;

    // can reorder columns, find largest rectangle of 1s
    // rows <= 15000 = 1.5 * 10^4
    // cols <= 1500 = 1.5 * 10^3
    // for starting row, optimal to sort cols by decreasing heights from the current row
    // then just take max of (height of current column) * (column 1index)
    // O(rows * cols * lg(cols))
    vector<int> h(cols); // height of columns
    vector<int> order(cols); iota(all(order), 0); // columns sorted in decreasing order
    int res = 0;
    for (int r = 0; r < rows; ++r) {
        string s; cin >> s;
        for (int c = 0; c < cols; ++c) {
            h[c] = s[c] == '1' ? h[c] + 1 : 0;
        }
        sort(all(order), [&](int i, int j) {
            return h[i] > h[j];
        });
        for (int c = 0; c < cols; ++c) {
            res = max(res, h[order[c]] * (c+1));
        }
    }
    cout << res << "\n";
}
