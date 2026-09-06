// 2024-11-13 10:15:13 
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n;
    cin >> n;

    unordered_map<int, int> passengers; // passenger -> enter time
    ordered_set<int> enterTimes; // all active enter times
    unordered_map<int, int> locLast; // last time this location was visited
    ll complaints = 0;
    int nextLoc = 1;
    for (int i = 0; i < n * 2; ++i) {
        int c, l;
        cin >> c >> l;
        if (l == nextLoc) {
            // new location
            ++nextLoc;
        } else {
            // duplicate location
            // count passengers who got on before or at last loc (duplicate for them)
            complaints += enterTimes.order_of_key(locLast[l]+1);
        }
        locLast[l] = i;

        if (passengers.contains(c)) {
            enterTimes.erase(enterTimes.find(passengers[c]));
            passengers.erase(c);
        } else {
            enterTimes.insert(i);
            passengers[c] = i;
        }
    }
    cout << complaints << endl;
}
