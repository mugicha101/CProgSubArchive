/*
Diamond 5
18001 - Windmill Pivot
meta: {"problemId": 18001, "titleKo": "Windmill Pivot", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Windmill Pivot", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 13, "level": 21, "votedUserCount": 5, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.615399956703186, "official": true, "tags": [{"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "bulldozer", "isMeta": false, "bojTagId": 238, "problemCount": 15, "displayNames": [{"language": "ko", "name": "bulldozer 트릭", "short": "bulldozer"}, {"language": "en", "name": "bulldozer trick", "short": "bulldozer"}], "aliases": []}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // get points
    int n; cin >> n;
    vector<pair<ll,ll>> pts(n); for (auto &[x, y] : pts) cin >> x >> y;

    // nodes represent promotions: (x, y) - x = old pivot, y = new pivot
    // edge: rotation from one promotion to next clockwise (weight = rotation amount)
    // for each point x, sort angles to rest of points, can find (a, x) -> (x, b) in O(n) with 2ptr
    // total: O(n^2lgn) ~= 2000^2 * 10 = 40000000 = 10^7 < 10^9
    // indexing nodes: (x, y) -> x * n + y
    // number of nodes: n^2

    auto index = [n](int x, int y) -> int {
        return (x * n) + y;
    };
    auto deindex = [n](int i) -> pair<int,int> {
        return make_pair(i / n, i % n);
    };
    int v = n * n;
    vector<pair<int,ld>> next(v, make_pair(-1,-1.L)); // node -> next node, rotation amount

    vector<int> order(n-1);
    vector<pair<int,int>> opts(n); // pts offset by pivot
    vector<double> angles(n); // angle[i] = angle of opts[i] (clockwise)
    for (int x = 0; x < n; ++x) {
        for (int i = 0; i < n; ++i) {
            opts[i] = { pts[i].first - pts[x].first, pts[i].second - pts[x].second };
            angles[i] = -atan2((double)opts[i].second, (double)opts[i].first);
            if (angles[i] < 0) angles[i] += ROT_FULL;
        }

        // get pts in sorted angle order
        order.push_back(0);
        iota(order.begin(), order.end(), 0);
        swap(order[x], order.back());
        order.pop_back();
        sort(order.begin(), order.end(), [&](int i, int j) {
            return angles[i] < angles[j];
        });

        // clockwise rotation needed to go from pts[order[i]] to pts[order[j]] around pivot pts[x]
        auto angleTo = [&](int i, int j) {
            int ir = i / (n-1);
            int jr = j / (n-1);
            return angles[order[j - jr * (n-1)]] + jr * ROT_FULL - angles[order[i - ir * (n-1)]] - ir * ROT_FULL;
        };

        // 2 ptr - for each old pivot a, next pivot is either next on opposite side of line or next on this side of line (whichever requires least rotation)
        // let b be the closest point
        // if b is on this side: (a, x, s) -> (x, b, !s)
        // if b is on other side: (a, x, s) -> (x, b, s)
        int j = 0; // next pt on opposite side
        for (int i = 0; i < n-1; ++i) {
            int a = order[i];
            while (angleTo(i, j) < ROT_HALF) ++j;
            ld fsAngle = angleTo(i, j) - ROT_HALF;
            ld nsAngle = angleTo(i, i+1);
            if (fsAngle < nsAngle) {
                // b on opposite side
                next[index(a, x)] = { index(x, order[j % (n-1)]), fsAngle };
            } else {
                // b on same side
                next[index(a, x)] = { index(x, order[(i+1) % (n-1)]), nsAngle };
            }
        }
    }

    // traverse cycles, find most occuring pivot in cycle
    // mult by # cycles for full rotation
    vector<bool> visited(v);
    int overallBest = 0;
    for (int i = 0; i < v; ++i) {
        auto [ix, iy] = deindex(i);
        if (ix == iy || visited[i]) continue;

        unordered_map<int,int> occ;
        int curr = i;
        ld rot = 0;
        visited[curr] = true;
        ++occ[deindex(curr).second];
        int best = 1;
        while (next[curr].first != i) {
            rot += next[curr].second;
            curr = next[curr].first;
            visited[curr] = true;
            best += ++occ[(deindex(curr)).second] == best + 1;
        }
        rot += next[curr].second;
        ld m = ROT_FULL / rot;
        best = round((double)best * m);
        overallBest = max(overallBest, best);
    }
    cout << overallBest << endl;
}
