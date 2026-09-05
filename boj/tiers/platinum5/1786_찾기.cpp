/*
Platinum 5
1786 - 찾기
meta: {"problemId": 1786, "titleKo": "찾기", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "찾기", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 10224, "level": 16, "votedUserCount": 450, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.1451001167297363, "official": true, "tags": [{"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "kmp", "isMeta": false, "bojTagId": 40, "problemCount": 115, "displayNames": [{"language": "ko", "name": "KMP", "short": "KMP"}, {"language": "en", "name": "knuth–morris–pratt", "short": "kmp"}, {"language": "ja", "name": "クヌース–モリス–プラット法", "short": "kmp"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef unsigned int uint;
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
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)

#include <bits/stdc++.h>
using namespace std;


// knuth morris pratt string matching
struct KMP {
    // returns p where p[i] = length of longest prefix of P that is a proper suffix of P[0..<i] (proper meaning cannot equal P[0..<i])
    vector<int> prefixFunc(const string &s) {
        vector<int> p(s.size());
        int k = 0;
        for (int q = 1; q < (int)s.size(); ++q) {
            while (k > 0 && s[k] != s[q]) k = p[k-1];
            k += s[k] == s[q];
            p[q] = k;
        }
        return p;
    }

    string pat;
    vector<int> pref;
    KMP(string pattern) : pat(pattern), pref(prefixFunc(pattern)) {
        pat += (char)0;
    }

    // finds first instance of pattern in s
    int match(const string &s) {
        int m = (int)pref.size();
        int q = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            while (q > 0 && pat[q] != s[i]) q = pref[q-1];
            q += pat[q] == s[i];
            if (q == m) return i-m+1;
        }
        return -1;
    }

    // finds all instances of pattern in s
    vector<int> matchAll(const string &s) {
        int m = (int)pref.size();
        int q = 0;
        vector<int> matches;
        for (int i = 0; i < (int)s.size(); ++i) {
            while (q > 0 && pat[q] != s[i]) q = pref[q-1];
            q += pat[q] == s[i];
            if (q == m) matches.push_back(i-m+1);
        }
        return matches;
    }

    // count number of matches
    int matchCount(const string &s) {
        int m = (int)pat.size();
        int q = 0;
        int matches = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            while (q > 0 && pat[q] != s[i]) q = pref[q-1];
            q += pat[q] == s[i];
            matches += q == m;
        }
        return matches;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);
    string t, p;
    getline(cin, t);
    getline(cin, p);

    KMP kmp(p);
    vector<int> matches = kmp.matchAll(t);
    cout << matches.size() << "\n";
    for (int x : matches) cout << x+1 << " ";
    cout << "\n";
}
