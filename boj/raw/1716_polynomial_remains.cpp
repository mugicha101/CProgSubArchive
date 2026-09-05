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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    while (true) {
        int n, k;
        cin >> n >> k;
        if (n == -1) break;

        vector<int> coeffs(n+1);
        for (int &c : coeffs) cin >> c;
        
        if (k == 0) {
            cout << 0 << endl;
            continue;
        }

        // polynomial division
        for (int m = n - k; m >= 0; --m) {
            int d = coeffs[m + k];
            coeffs[m + k] -= d;
            coeffs[m] -= d;
        }
        while (coeffs.size() > 1 && coeffs.back() == 0) coeffs.pop_back();
        for (int c : coeffs) cout << c << " ";
        cout << endl;
    }
}
