/*
Platinum 4
16419 - Knockout
meta: {"problemId": 16419, "titleKo": "Knockout", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Knockout", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 28, "level": 17, "votedUserCount": 7, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.142899990081787, "official": true, "tags": [{"key": "bitmask", "isMeta": false, "bojTagId": 14, "problemCount": 1027, "displayNames": [{"language": "ko", "name": "비트마스킹", "short": "비트마스킹"}, {"language": "en", "name": "bitmask", "short": "bitmask"}, {"language": "ja", "name": "ビット表現", "short": "ビット表現"}], "aliases": [{"alias": "비트필드"}, {"alias": "비트마스크"}]}, {"key": "combinatorics", "isMeta": false, "bojTagId": 6, "problemCount": 1292, "displayNames": [{"language": "ko", "name": "조합론", "short": "조합론"}, {"language": "en", "name": "combinatorics", "short": "combinatorics"}, {"language": "ja", "name": "組み合わせ", "short": "組み合わせ"}], "aliases": [{"alias": "combination"}, {"alias": "permutation"}, {"alias": "probability"}, {"alias": "확률"}, {"alias": "순열"}]}, {"key": "dp", "isMeta": false, "bojTagId": 25, "problemCount": 5152, "displayNames": [{"language": "ko", "name": "다이나믹 프로그래밍", "short": "다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming", "short": "dp"}, {"language": "ja", "name": "動的計画法", "short": "dp"}], "aliases": [{"alias": "동적계획법"}, {"alias": "동적 계획법"}, {"alias": "다이나믹프로그래밍"}]}, {"key": "dp_tree", "isMeta": false, "bojTagId": 92, "problemCount": 597, "displayNames": [{"language": "ko", "name": "트리에서의 다이나믹 프로그래밍", "short": "트리에서의 다이나믹 프로그래밍"}, {"language": "en", "name": "dynamic programming on trees", "short": "tree dp"}, {"language": "ja", "name": "木上の動的計画法", "short": "tree dp"}], "aliases": [{"alias": "트리dp"}]}, {"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "probability", "isMeta": false, "bojTagId": 177, "problemCount": 508, "displayNames": [{"language": "ko", "name": "확률론", "short": "확률론"}, {"language": "en", "name": "probability theory", "short": "probability"}, {"language": "ja", "name": "確率論", "short": "確率論"}], "aliases": [{"alias": "expected value"}, {"alias": "기대값"}, {"alias": "기댓값"}]}, {"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}], "metadata": {}}
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

#define MOD 1000000007
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

int p[13] = {};
ld prob(int v) {
  return (ld)p[v] / 36.L;
}

pair<ld,int> dp[1 << 10][13]; // expected score, elimination mask
bool maxing = false;

int maskSum(int x) {
  int sum = 0;
  for (int i = 1; i <= 9; ++i) {
    if ((x >> i) & 1) sum += i;
  }
  return sum;
}

ld dfs(int m, int s) {
  // cout << bitset<10>(m) << " " << s << endl;
  auto &[best, bestMask] = dp[m][s];
  if (bestMask != 0) return best;

  for (int x = 2; x <= m; x += 2) {
    if ((x & m) != x || maskSum(x) != s) continue;

    int nm = m ^ x;
    ld res = 0;
    for (int ns = 1; ns <= 12; ++ns) {
      dfs(nm, ns);
      res += dp[nm][ns].first * prob(ns);
    }
    if ((maxing && res <= best) || (!maxing && res >= best)) continue;

    best = res;
    bestMask = x;
  }
  if (bestMask) return best;

  // no way to sum to s
  int res = 0;
  for (int i = 1; i <= 9; ++i) {
    if ((m >> i) & 1) res = res * 10 + i;
  }
  best = (ld)res;
  return best;
}

void output(int m, int s) {
  auto [ev, x] = dp[m][s];
  int res = -1;
  if (x) {
    res = 0;
    for (int i = 1; i <= 9; ++i) {
      if ((x >> i) & 1) res = res * 10 + i;
    }
  }
  cout << res << " " << ev << "\n";
}

int main() {
  cin.tie()->sync_with_stdio(0);
  cout << fixed << setprecision(5);

  for (int i = 1; i <= 6; ++i) {
    for (int j = 1; j <= 6; ++j) {
      ++p[i+j];
    }
  }

  string t;
  int d1, d2;
  cin >> t >> d1 >> d2;
  int m = 0;
  for (char c : t) {
    m |= 1 << (c-'0');
  }
  int s = d1 + d2;

  // minimize
  for (int i = 0; i < (1 << 10); ++i) {
    for (int j = 0; j < 13; ++j) dp[i][j] = {1000000000000.L, 0};
  }
  dfs(m, s);
  output(m, s);

  // maximize
  maxing = true;
  for (int i = 0; i < (1 << 10); ++i) {
    for (int j = 0; j < 13; ++j) dp[i][j] = {-1000000000000.L, 0};
  }
  dfs(m, s);
  output(m, s);
}
