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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<int> s(n); vcin(s);

    // precompute all palindromes naively n^2 (manachers not necessary)
    vector<vector<bool>> pals(n, vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        // odd
        pals[i][i] = true;
        int l = 1;
        while (i-l >= 0 && i+l < n && s[i-l] == s[i+l]) {
            pals[i-l][i+l] = true;
            ++l;
        }
        
        // even
        l = 0;
        while (i-l >= 0 && i+l+1 < n && s[i-l] == s[i+l+1]) {
            pals[i-l][i+l+1] = true;
            ++l;
        }
    }

    int q; cin >> q;
    while (q--) {
        int a, b; cin >> a >> b; --a; --b;
        cout << pals[a][b] << "\n";
    }
}
