/*
Gold 3
33041 - 마작 거신병 9
meta: {"problemId": 33041, "titleKo": "마작 거신병 9", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "마작 거신병 9", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 121, "level": 13, "votedUserCount": 25, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.834700107574463, "official": true, "tags": [{"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "constructive", "isMeta": false, "bojTagId": 128, "problemCount": 1581, "displayNames": [{"language": "ko", "name": "해 구성하기", "short": "해 구성하기"}, {"language": "en", "name": "constructive", "short": "constructive"}, {"language": "ja", "name": "構成的", "short": "構成的"}], "aliases": [{"alias": "constructive"}, {"alias": "컨스트럭티브"}, {"alias": "구성적"}]}], "metadata": {}}
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

    // greedily assign 0,1,2,3,... 9s
    // assign remaining 9s greedily from bottom up
    // rows ordered from highest to lowest
    int rows; cin >> rows;
    vector<int> width(rows); vcin(width);
    int a, b; cin >> a >> b;
    vector<int> asn(rows);
    vector<int> sum(rows+1);
    sum.back() = INT_MAX >> 1;
    sum[0] = width[0];

    for (int i = 1; i < rows; ++i) {
        sum[i] = width[i];
        if (sum[i] > sum[i-1]) continue;

        int needed = (sum[i-1] + 8 - sum[i]) / 8;
        asn[i] += needed;
        sum[i] += needed * 8;
        b -= needed;
        if (asn[i] > width[i]) {
            cout << -1 << "\n";
            return 0;
        }
    }
    if (b < 0) {
        cout << -1 << "\n";
        return 0;
    }
    for (int i = 0; i < rows; ++i) {
        if (asn[i] > width[i]) {
            cout << -1 << "\n";
            return 0;
        }
    }
    for (int i = rows-1; b > 0 && i >= 0; --i) {
        int addable = min({b, width[i] - asn[i], (sum[i+1] - sum[i] - 1) / 8});
        sum[i] += addable * 8;
        asn[i] += addable;
        b -= addable;
    }
    if (b > 0) {
        cout << -1 << "\n";
        return 0;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < width[i]; ++j) {
            cout << (j < asn[i] ? 9 : 1) << " ";
        }
        cout << "\n";
    }
}
