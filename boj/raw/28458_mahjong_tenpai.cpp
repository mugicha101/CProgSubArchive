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

string names[1 << 6] = {};
vector<string> db;
bool dfs(vector<uint8_t> &tiles, int used = 0) {
    if (used == 0) {
        // check validity
        int sum = 0;
        for (int i = 0; i < (int)tiles.size(); ++i) {
            sum += tiles[i];
            assert(tiles[i] == 0 || names[i] != "");
        }
        assert(sum == 14);

        // check for 7 pairs
        int p = 0;
        for (int x : tiles) p += x == 2;
        if (p == 7) return true;

        // check for orphans
        int numOrphans = 0;
        int pairOrphans = 0;
        const uint8_t orphans[13] = { 0b110000, 0b110001, 0b110010, 0b110011, 0b110100, 0b110101, 0b110110, 0b000001, 0b001001, 0b010001, 0b011001, 0b100001, 0b101001 };
        for (uint8_t t : orphans) {
            if (tiles[t] > 2) {
                numOrphans = 0;
                break;
            }
            numOrphans += tiles[t] > 0;
            pairOrphans += tiles[t] == 2;
        }
        if (numOrphans == 13 && pairOrphans == 1) return true;

        // choose pair
        for (int t = 0; t < (1 << 6); ++t) {
            if (tiles[t] < 2) continue;
            
            db.push_back("pair " + names[t]);
            tiles[t] -= 2;
            bool win = dfs(tiles, used + 2);
            tiles[t] += 2;
            db.pop_back();
            if (win) return true;
        }

        return false;
    }
    
    if (used >= 14) {
        assert(used == 14);
        for (int x : tiles) assert(x == 0);
        return true;
    }

    // try seq
    for (int i = 0; i < (1 << 6); ++i) {
        if (i < 0b110000 && tiles[i] && tiles[i+1] && tiles[i+2]) {
            assert((i & 0b111) <= 7);
            assert((i & 0b111) >= 1);
            assert((i >> 4) <= 0b10);
            db.push_back("seq " + names[i]);
            assert(names[i].size() == 2 && names[i+1].size() == 2 && names[i+2].size() == 2);
            --tiles[i]; --tiles[i+1]; --tiles[i+2];
            bool win = dfs(tiles, used + 3);
            ++tiles[i]; ++tiles[i+1]; ++tiles[i+2];
            db.pop_back();
            if (win) return true;
        }
        
        // try set
        if (tiles[i] >= 3) {
            db.push_back("set " + names[i]);
            tiles[i] -= 3;
            bool win = dfs(tiles, used + 3);
            tiles[i] += 3;
            
            db.pop_back();
            if (win) return true;
        }
    }

    return false;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // suit num | represents
    //   00 xxxx | xxx of s (001-101)
    //   01 xxxx | xxx of t (001-101)
    //   10 xxxx | xxx of m (001-101)
    //   11 00xx | xx of winds (00: e, 01: s, 10: w, 11: n)
    //   11 01xx | xx of dragons (00: h, 01: b, 10: j)
    for (uint8_t suit = 0; suit <= 2; ++suit) {
        char s = suit == 0 ? 's' : suit == 1 ? 't' : 'm';
        for (uint8_t num = 1; num <= 9; ++num) {
            uint8_t t = (suit << 4) | num;
            names[t] = "";
            names[t] += '0' + num;
            names[t] += s;
        }
    }
    names[0b110000] = "e";
    names[0b110001] = "s";
    names[0b110010] = "w";
    names[0b110011] = "n";
    names[0b110100] = "h";
    names[0b110101] = "b";
    names[0b110110] = "j";

    vector<uint8_t> tiles(1 << 6);
    for (int i = 0; i < 13; ++i) {
        string s; cin >> s;
        uint8_t t = 0;
        while (names[t] != s) ++t;
        ++tiles[t];
    }

    // try all possible last tiles
    bitset<1 << 6> wins;
    for (uint8_t t = 0; t < (1 << 6); ++t) {
        if (names[t] == "" || tiles[t] == 4) continue;

        ++tiles[t];

        // check for tsumo
        wins[t] = dfs(tiles);

        --tiles[t];
    }

    if (wins.count() == 0) {
        cout << "no tenpai" << endl;
    } else {
        cout << "tenpai\n" << wins.count() << "\n";
        vector<string> valid;
        for (int t = 0; t < (1 << 6); ++t) {
            if (wins[t]) valid.push_back(names[t]);
        }
        sort(valid.begin(), valid.end());
        for (string &s : valid) cout << s << " ";
        cout << endl;
    }
}
