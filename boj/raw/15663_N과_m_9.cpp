#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, k; cin >> n >> k;
    vector<int> vals(n);
    for (int &x : vals) cin >> x;
    sort(all(vals));

    vector<int8_t> stack;
    stack.reserve(k+1);
    vector<int8_t> curr;
    vector<vector<int8_t>> out;
    curr.reserve(k+1);
    stack.push_back(-1);
    while (!stack.empty()) {
        int i = (int)stack.size() - 1;

        if (i == k) {
            out.push_back(curr);
            stack.pop_back();
            if (!stack.empty()) {
                vals[stack.back()] = curr.back();
                curr.pop_back();
            }
            continue;
        }

        while (++stack.back() < n && vals[stack.back()] == -1);
        if (stack.back() == n) {
            stack.pop_back();
            if (!stack.empty()) {
                vals[stack.back()] = curr.back();
                curr.pop_back();
            }
            continue;
        }

        curr.push_back(vals[stack.back()]);
        vals[stack.back()] = -1;
        stack.push_back(-1);
    }
    sort(all(out));
    out.resize(distance(out.begin(), unique(all(out))));
    for (vector<int8_t> &v : out) {
        for (int x : v) cout << x << " ";
        cout << "\n";
    }
}
