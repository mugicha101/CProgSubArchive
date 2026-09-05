/*
Platinum 5
16163 - #15164번_제보
meta: {"problemId": 16163, "titleKo": "#15164번_제보", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "#15164번_제보", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 987, "level": 16, "votedUserCount": 140, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.384000062942505, "official": true, "tags": [{"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "manacher", "isMeta": false, "bojTagId": 44, "problemCount": 34, "displayNames": [{"language": "ko", "name": "매내처", "short": "매내처"}, {"language": "en", "name": "manacher's", "short": "manacher's"}, {"language": "ja", "name": "manacher's", "short": "manacher's"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define endl "\n"

#include <bits/stdc++.h>

using namespace std;

// manacher's algorithm: computes longest palindrome centered at index i in O(N)
// output format:
//   pal = manacher(s)
//   pal[i].first = length of longest odd length palindrome in s centered at index i
//   pal[i].second = length of longest even length palindrome in s centered between index i and index i+1
// note: doesn't work if chars with ascii value 0, 1, 2 are used

vector<int> manacher_helper(const string &s) {
  int n = s.size() - 2;
  vector<int> p(n + 2);
  int l = 1, r = 1;
  for(int i = 1; i <= n; i++) {
    p[i] = max(0, min(r - i, p[l + (r - i)]));
    while(s[i - p[i]] == s[i + p[i]]) {
      p[i]++;
    }
    if(i + p[i] > r) {
      l = i - p[i], r = i + p[i];
    }
  }
  return p;
}

// finds odd and even palindromes
vector<pair<int,int>> manacher(const string &s) {
  string t;
  t += (char)1;
  for(char c : s) {
    t += (char)0;
    t += c;
  }
  t += (char)0;
  t += (char)2;
  vector<int> man = manacher_helper(t);
  vector<pair<int,int>> res(s.size());
  for (int i = 0; i < (int)s.size(); ++i) {
    res[i].first = man[i * 2 + 2] - 1; // odd
    res[i].second = man[i * 2 + 3] - 1; // even
  }
  return res;
}

// finds odd palindromes
vector<int> manacher_odd(const string &s) {
  string t;
  t += (char)1;
  t += s;
  t += (char)2;
  vector<int> man = manacher_helper(t);
  vector<int> res(man.size() - 2);
  for (int i = 0; i < (int)s.size(); ++i) {
    res[i] = man[i+1] * 2 - 1;
  }
  return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    string s; cin >> s;
    vector<pair<int,int>> pals = manacher(s);
    ll res = 0;
    for (int i = 0; i < (int)pals.size(); ++i) {
        res += (pals[i].first + 1) >> 1;
        res += pals[i].second >> 1;
    }
    cout << res << endl;
}
