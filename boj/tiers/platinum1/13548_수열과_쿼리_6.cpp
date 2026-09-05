/*
Platinum 1
13548 - 수열과 쿼리 6
meta: {"problemId": 13548, "titleKo": "수열과 쿼리 6", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "수열과 쿼리 6", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 1626, "level": 20, "votedUserCount": 287, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.9470999240875244, "official": true, "tags": [{"key": "offline_queries", "isMeta": false, "bojTagId": 123, "problemCount": 372, "displayNames": [{"language": "ko", "name": "오프라인 쿼리", "short": "오프라인 쿼리"}, {"language": "en", "name": "offline queries", "short": "offline query"}, {"language": "ja", "name": "offline queries", "short": "offline query"}], "aliases": [{"alias": "offlinequery"}]}, {"key": "mo", "isMeta": false, "bojTagId": 50, "problemCount": 51, "displayNames": [{"language": "ko", "name": "mo's", "short": "Mo's"}, {"language": "en", "name": "mo's", "short": "mo's"}, {"language": "ja", "name": "mo's", "short": "mo's"}], "aliases": [{"alias": "squarerootdecomposition"}, {"alias": "sqrtdecomposition"}, {"alias": "평방분할법"}]}], "metadata": {}}
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

    // seq of nums length n <= 10^5
    // up to 10^5 queries
    // given query [i, j] find max frequency of num
    // mo's algo - group queries by i in sqrt(n) buckets and handle by sorted j
    int n; cin >> n;
    vector<int> arr(n); for (int &x : arr) cin >> x;
    int m; cin >> m;
    vector<pair<int,int>> queries(m);
    vector<int> res(m);
    for (auto &[i, j] : queries) {
        cin >> i >> j;
        --i; --j;
    }
    int s = 1; // bucket size
    while (s * s < n) ++s;
    vector<vector<int>> buckets(n + (s - 1) / s);
    for (int i = 0; i < m; ++i) {
        buckets[queries[i].first / s].push_back(i);
    }

    int wl = 0, wr = -1, mf = 0;
    vector<int> count(100001);
    vector<int> freq(n+1);
    freq[0] = INT_MAX >> 2;
    auto mlr = [&]() {
        int c = --count[arr[wl++]];
        --freq[c+1];
        ++freq[c];
        mf -= freq[mf] == 0;
    };
    auto mll = [&]() {
        int c = ++count[arr[--wl]];
        --freq[c-1];
        ++freq[c];
        mf += c-1 == mf;
    };
    auto mrl = [&]() {
        int c = --count[arr[wr--]];
        --freq[c+1];
        ++freq[c];
        mf -= freq[mf] == 0;
    };
    auto mrr = [&]() {
        int c = ++count[arr[++wr]];
        --freq[c-1];
        ++freq[c];
        mf += c-1 == mf;
    };
    for (auto &b : buckets) {
        sort(all(b), [&](int i, int j) {
            return queries[i].second < queries[j].second;
        });
        for (int qi : b) {
            auto [i, j] = queries[qi];
            while (wr > j) mrl();
            while (wr < j) mrr();
            while (wl < i) mlr();
            while (wl > i) mll();
            res[qi] = mf;
        }
    }
    for (int x : res) cout << x << "\n";
}
