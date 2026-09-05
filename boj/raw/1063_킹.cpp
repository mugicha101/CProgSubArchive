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

    string king, stone;
    cin >> king >> stone;

    int moves;
    cin >> moves;
    while (moves--) {
        string m;
        string newKing = king;
        string newStone = stone;
        cin >> m;

        int dr = m.find('T') != m.npos ? 1 : m.find('B') != m.npos ? -1 : 0;
        int dc = m.find('R') != m.npos ? 1 : m.find('L') != m.npos ? -1 : 0;

        auto move = [&](string &entity) {
            entity[0] += dc;
            entity[1] += dr;
            return entity[0] >= 'A' && entity[0] <= 'H' && entity[1] >= '1' && entity[1] <= '8';
        };

        if (move(newKing) && (newKing != newStone || move(newStone))) {
            king = newKing;
            stone = newStone;
        }
    }
    cout << king << endl;
    cout << stone << endl;
}
