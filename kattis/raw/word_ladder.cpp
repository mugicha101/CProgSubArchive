// 2025-05-17 18:12:50 
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

using namespace std;

const int MOD = 1000000007;

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
// #define endl "\n"

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n; cin >> n;

    string s(10, 'a');
    static vector<string> buff;
    auto valid = [&]() {
        for (int i = 0; i+1 < (int)buff.size(); ++i) {
            string &t = buff[i];
            int diff = 0;
            for (int j = 0; j < 10; ++j) diff += s[j] != t[j];
            if (diff <= 1) return false;
        }
        return true;
    };
    while (buff.size() < 5000) {
        int i = rand() % 10;
        char c = 'a' + (rand() % 26);
        char t = s[i];
        s[i] = c;
        if (valid()) buff.push_back(s);
        else s[i] = t;
    }
    for (int i = 0; i < n; ++i) cout << buff[i] << "\n";
}
