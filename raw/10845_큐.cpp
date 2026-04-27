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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    queue<int> s;
    int n; cin >> n;
    while (n--) {
        string op; cin >> op;
        if (op == "push") {
            int x; cin >> x; s.push(x);
        } else if (op == "pop") {
            if (s.empty()) cout << -1 << "\n";
            else {
                cout << s.front() << "\n";
                s.pop();
            }
        } else if (op == "front") cout << (s.empty() ? -1 : s.front()) << "\n";
        else if (op == "back") cout << (s.empty() ? -1 : s.back()) << "\n";
        else if (op == "empty") cout << s.empty() << "\n";
        else cout << s.size() << "\n";
    }
}
