// 2024-11-12 20:59:30 
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

#include <bits/extc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

int dfs(vector<int> &teams, int i, int m) {
    if (i == (int)teams.size()) return 0;

    int res = 0;
    
    // pick if no overlap with already chosen
    if ((teams[i] & m) == 0) {
        res = dfs(teams, i+1, m | teams[i]) + 1;
    }

    // skip
    res = max(res, dfs(teams, i+1, m));

    return res;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    string s;
    cin >> s;

    // outward greedy
    // for same value, fix leftmost as greatest
    int n = s.size();
    vector<ll> rightGreater(n); // offset of next element > curr element on right
    vector<ll> leftGreater(n); // offset of next element >= curr element on left
    vector<int> t;
    for (int i = 0; i < n; ++i) {
        while (!t.empty() && s[t.back()] < s[i]) t.pop_back();
        leftGreater[i] = i - (t.empty() ? -1 : t.back());
        t.push_back(i);
    }
    t.clear();
    for (int i = n-1; i >= 0; --i) {
        while (!t.empty() && s[t.back()] <= s[i]) t.pop_back();
        rightGreater[i] = (t.empty() ? n : t.back()) - i;
        t.push_back(i);
    }
    ll counts[10] = {};
    for (int i = 0; i < n; ++i) {
        ll amt = leftGreater[i] * rightGreater[i];
        counts[s[i]-'0'] += amt;
    }
    ll num = 0;
    ll den = 0;
    for (int i = 0; i <= 9; ++i) {
        num += (ll)i * counts[i];
        den += counts[i];
    }
    if (num == 0) {
        cout << 0 << endl;
        return 0;
    }
    ll d = gcd(num, den);
    num /= d;
    den /= d;
    if (den == 1) {
        cout << num << endl;
        return 0;
    }

    ll whole = num / den;
    num %= den;
    if (whole > 0) {
        cout << whole << " ";
    }
    cout << num << "/" << den << endl;
}
