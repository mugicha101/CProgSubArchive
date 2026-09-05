/*
Platinum 4
16417 - Count the Bits
meta: {"problemId": 16417, "titleKo": "Count the Bits", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Count the Bits", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 42, "level": 17, "votedUserCount": 16, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.11899995803833, "official": true, "tags": [{"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "dp_digit", "isMeta": false, "bojTagId": 217, "problemCount": 64, "displayNames": [{"language": "ko", "name": "자릿수를 이용한 다이나믹 프로그래밍", "short": "자릿수 dp"}, {"language": "en", "name": "digit dp", "short": "digit dp"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);
    
    // digit dp
    // dp[i][j] = (sum bits of all numbers formeable by i bits x s.t. x mod k = j, total such x)
    // to add bit to x, x = x * 2 + 1, x = x * 2
    // can compress
    int k, b; cin >> k >> b;
    vector<vector<pair<int,int>>> dp(2, vector<pair<int,int>>(k, mp(0,0)));
    dp[0][0].second = 1;
    for (int i = 1; i <= b; ++i) {
        for (int j = 0; j < k; ++j) dp[1][j] = mp(0,0);
        for (int j = 0; j < k; ++j) {

            // x = x * 2 + 1
            int nj = (j*2+1) % k;
            madd(dp[1][nj].first, dp[0][j].first);
            madd(dp[1][nj].first, dp[0][j].second);
            madd(dp[1][nj].second, dp[0][j].second);

            // x = x * 2
            nj = (j*2) % k;
            madd(dp[1][nj].first, dp[0][j].first);
            madd(dp[1][nj].second, dp[0][j].second);
        }   
        swap(dp[0], dp[1]);
    }
    cout << dp[0][0].first << "\n";
}
