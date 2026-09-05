/*
Platinum 3
15337 - Starting a Scenic Railroad Service
meta: {"problemId": 15337, "titleKo": "Starting a Scenic Railroad Service", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Starting a Scenic Railroad Service", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 290, "level": 18, "votedUserCount": 72, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.582800030708313, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "prefix_sum", "isMeta": false, "bojTagId": 139, "problemCount": 1379, "displayNames": [{"language": "ko", "name": "누적 합", "short": "누적 합"}, {"language": "en", "name": "prefix sum", "short": "prefix sum"}, {"language": "ja", "name": "累積和", "short": "累積和"}], "aliases": [{"alias": "구간합"}, {"alias": "부분합"}, {"alias": "rangesum"}]}, {"key": "sweeping", "isMeta": false, "bojTagId": 106, "problemCount": 708, "displayNames": [{"language": "ko", "name": "스위핑", "short": "스위핑"}, {"language": "en", "name": "sweeping", "short": "sweeping"}, {"language": "ja", "name": "平面走査", "short": "平面走査"}], "aliases": [{"alias": "라인 스위핑"}]}], "metadata": {}}
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

    int n; cin >> n;
    vector<pair<int,int>> itvs(n); for (auto &[a, b] : itvs) cin >> a >> b;
    vector<int> lo(n); iota(all(lo), 0);
    vector<int> ro = lo;
    sort(all(lo), [&](int i, int j) {
        return itvs[i].first < itvs[j].first;
    });
    sort(all(ro), [&](int i, int j) {
        return itvs[i].second < itvs[j].second;
    });

    // tight
    // place greedily to open seat in order of start times
    // answer is max overlap at a point
    // sweepline
    int tight = 0;
    priority_queue<int, vector<int>, greater<int>> ends;
    for (int i : lo) {
        auto [a, b] = itvs[i];
        while (!ends.empty() && ends.top() <= a) ends.pop();
        ends.push(b);
        tight = max(tight, (int)ends.size());
    }

    // loose
    // find interval with maximum overlap with other intervals
    // can order other intervals so each one pushes the maximum overlap interval down 1 line
    // let target interval = [a, b] and other intervals be [a', b']
    // # to left of current: bsearch for b' <= a
    // # to right of current: bsearch for a' >= b
    // # intersecting current = n - 1 - # to left of current - # to right of current
    int loose = 0;
    for (auto [a, b] : itvs) {
        // find last interval to left of current
        int l = -1;
        int r = n-1;
        while (l != r) {
            int m = (l + r + 1) >> 1;
            if (itvs[ro[m]].second > a) r = m-1;
            else l = m;
        }
        int nl = l+1;

        // find first interval to right of current
        l = 0;
        r = n;
        while (l != r) {
            int m = (l + r) >> 1;
            if (itvs[lo[m]].first < b) l = m+1;
            else r = m;
        }
        int nr = n-l;

        // remaining is either this interval or inside this interval
        loose = max(loose, n - nl - nr);
    }
    cout << loose << " " << tight << "\n";
}
