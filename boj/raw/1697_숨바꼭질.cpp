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

    int x, t; cin >> x >> t;
    if (x >= t) {
        cout << x - t << endl;
        return 0;
    }

    // given x < t
    // bfs, guaranteed to find within O(lg(t)) steps
    // by iteration t, fringe is size O(3^t)
    // thus bfs takes O(3^O(lg(n))) = O(n) time

    unordered_set<int> visited;
    queue<int> q;
    q.push(x);
    visited.insert(x);
    int dist = -1;
    while (true) {
        ++dist;
        for (int qi = q.size(); qi > 0; --qi) {
            int curr = q.front();
            q.pop();
            if (curr == t) {
                cout << dist << endl;
                return 0;
            }
            auto check = [&](int next) {
                if (visited.count(next)) return;

                visited.insert(next);
                q.push(next);
            };
            if (curr > 0) check(curr - 1);
            if (curr < t) {
                check(curr + 1);
                check(curr * 2);
            }
        }
    }
}
