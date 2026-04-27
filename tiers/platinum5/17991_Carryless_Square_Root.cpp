/*
Platinum 5
17991 - Carryless Square Root
meta: {"problemId": 17991, "titleKo": "Carryless Square Root", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Carryless Square Root", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 58, "level": 16, "votedUserCount": 13, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.482800006866455, "official": true, "tags": [{"key": "backtracking", "isMeta": false, "bojTagId": 5, "problemCount": 656, "displayNames": [{"language": "ko", "name": "백트래킹", "short": "백트래킹"}, {"language": "en", "name": "backtracking", "short": "backtrack"}, {"language": "ja", "name": "バックトラック法", "short": "バックトラック"}], "aliases": [{"alias": "백트래킹"}, {"alias": "퇴각검색"}, {"alias": "퇴각 검색"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007

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

const int N = 26;
const int K = 15;
using digs_t = array<uint8_t, N>;

digs_t to_digs(string s) {
    digs_t r = {};
    for (int i = 0; i < (int)s.size(); ++i) {
        r[i] = s[(int)s.size() - i - 1] - '0';
    }
    return r;
}

void print(digs_t ds) {
    for (uint8_t d : ds) cout << (int)d;
    cout << endl;
}

ll dfs(const digs_t &n, digs_t &a, int k) {
    ll res = LLONG_MAX;
    if (k == K) {
        // for (int i = 0; i < k; ++i) cout << (int)a[i];
        // cout << endl;
        // keep fixing 0s
        bool valid = true;
        for (; valid && k < N; ++k) {
            a[k] = 0;
            int s = 0;
            for (int i = 0; i <= k; ++i) s += a[i] * a[k-i];
            s %= 10;
            valid = s == n[k];
        }

        if (valid) {
            res = 0;
            for (int i = N-1; i >= 0; --i)
                res = res * 10 + a[i];
            return res;
        } else {
            return LLONG_MAX;
        }
    }

    // n[k] = sum(a[i] * a[k-i]) % 10
    // first calc a[1] * a[k-i] for 1 < i < k
    int s = 0;
    for (int i = 1; i < k; ++i) s += a[i] * a[k-i];
    s %= 10;

    // find a[k] that satisfies this
    for (uint8_t d = 0; d < 10; ++d) {
        // s + a[k] * a[0] * (k == 0 ? 1 : 2) = n[k]
        a[k] = d;
        int t = (s + a[k] * a[0] * (1 + (k != 0))) % 10;
        if (t == n[k]) res = min(res, dfs(n, a, k+1));
    }
    return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    string s; cin >> s;
    digs_t n = to_digs(s);
    
    digs_t a = {};
    ll res = dfs(n, a, 0);
    cout << (res == LLONG_MAX ? -1 : res) << endl;
}
