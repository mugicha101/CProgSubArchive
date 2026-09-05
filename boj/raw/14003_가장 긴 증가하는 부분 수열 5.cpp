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

    // lis constructive
    int n; cin >> n;
    vector<int> vals(n); vcin(vals);
    vector<int> s; // s[i] = last element ending an lis of length i+1
    vector<int> si; // index of s[i]
    s.reserve(n);
    vector<int> parent(n, -1);
    for (int i = 0; i < (int)vals.size(); ++i) {
        int x = vals[i];
        if (s.empty() || s.back() < x) {
            parent[i] = s.empty() ? -1 : si.back();
            s.push_back(x);
            si.push_back(i);
            continue;
        }

        int j = distance(s.begin(), lower_bound(s.begin(), s.end(), x));
        parent[i] = j == 0 ? -1 : si[j-1];
        si[j] = i;
        s[j] = x;
    }
    int curr = si.back();
    vector<int> lis;
    lis.reserve(s.size());
    while (curr != -1) {
        lis.push_back(vals[curr]);
        curr = parent[curr];
    }
    reverse(all(lis));
    cout << lis.size() << "\n";
    for (int x : lis) cout << x << " ";
    cout << "\n";
}
