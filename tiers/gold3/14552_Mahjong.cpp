/*
Gold 3
14552 - Mahjong
meta: {"problemId": 14552, "titleKo": "Mahjong", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "Mahjong", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 173, "level": 13, "votedUserCount": 17, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.7109999656677246, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}], "metadata": {}}
*/

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

bool dfs(vector<int> &tiles, int used) {
    if (used == 14) return true;
    if (used == 0) {
        // check for 7 pairs
        int p = 0;
        for (int x : tiles) p += x == 2;
        if (p == 7) return true;

        // fix pair
        for (int t = 1; t <= 9; ++t) {
            if (tiles[t] < 2) continue;

            tiles[t] -= 2;
            bool win = dfs(tiles, used + 2);
            tiles[t] += 2;
            if (win) return true;
        }
        return false;
    }

    // try seq
    for (int t = 1; t <= 7; ++t) {
        if (!(tiles[t] && tiles[t+1] && tiles[t+2])) continue;
        --tiles[t]; --tiles[t+1]; --tiles[t+2];
        bool win = dfs(tiles, used + 3);
        ++tiles[t]; ++tiles[t+1]; ++tiles[t+2];
        if (win) return true;
    }

    // try set
    for (int t = 1; t <= 9; ++t) {
        if (tiles[t] < 3) continue;
        tiles[t] -= 3;
        bool win = dfs(tiles, used + 3);
        tiles[t] += 3;
        if (win) return true;
    }
    return false;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    vector<int> tiles(10);
    for (int i = 0; i < 13; ++i) {
        int x; cin >> x; ++tiles[x];
    }

    bool any = false;
    for (int i = 1; i <= 9; ++i) {
        if (tiles[i] == 4) continue;

        ++tiles[i];
        if (dfs(tiles, 0)) {
            any = true;
            cout << i << " ";
        }
        --tiles[i];
    }
    if (!any) cout << -1;
    cout << endl;
}
