/*
Platinum 2
1227 - SABOR
meta: {"problemId": 1227, "titleKo": "그녀의 마음", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "그녀의 마음", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "SABOR", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 32, "level": 19, "votedUserCount": 8, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.625, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "case_work", "isMeta": false, "bojTagId": 137, "problemCount": 1205, "displayNames": [{"language": "ko", "name": "많은 조건 분기", "short": "많은 조건 분기"}, {"language": "en", "name": "case work", "short": "case work"}, {"language": "ja", "name": "ケースワーク", "short": "ケースワーク"}], "aliases": [{"alias": "케이스"}, {"alias": "케이스워크"}, {"alias": "케이스 워크"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

struct Diagonal {
    static ll sumLen;
    ll dx, dy; // direction (eg: -1, 1)
    ll sx, sy; // start
    ll len = 1; // length
    Diagonal(ll dx, ll dy, ll sx, ll sy) : dx(dx), dy(dy), sx(sx), sy(sy) {
        ++Diagonal::sumLen;
    };

    inline void shiftStart(ll a) {
        sx += dx * a;
        sy += dy * a;
        len -= a;
        Diagonal::sumLen -= a;
    }

    inline void shiftEnd(ll a) {
        len += a;
        Diagonal::sumLen += a;
    }
};
ll Diagonal::sumLen = 0;

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // b <= 10^4 s <= 10^7
    // go reverse - start at dest, end at each source
    // grid bfs
    // parity maintained regardless of obstacles, so only need to figure out if they can reach in time
    // approach - for each distance from dest, ends at party, find all tiles that are at this distance
    // since obstacles at most 2000 away from origin, just naive bfs until no more inner gaps (final shape consists of entirely diagonals).
    // from final shape can extrapolate to arbitrary d
    // edge case: obstacles enclose origin, in which case just halt

    // need to ensure all obstacles have been accounted for by time of final shape
    // this can be done by just setting a lower bound for sim dist high enough
    // worst case:
    //  /\/\ 
    // /    \ 
    // \    /
    //  \/\/
    // in this case, enclosed y is minY/2 to maxY/2
    // so just ensure minY < 2000 and maxY > 2000
    // same for x


    int b, s; cin >> b >> s;
    const int N = 4096; // radius of grid
    const int D = 2024; // distance threshold before checking for diamond
    int minX = N, minY = N, maxX = N, maxY = N;
    vector<bitset<N*2+1>> grid(N*2+1, 0ULL);
    for (int i = 0; i < b; ++i) {
        int x, y; cin >> x >> y;
        swap(x, y);
        x += N; y += N;
        grid[x][y] = true;
    }

    auto showGrid = [&]() {
        cout << minX << " " << maxX << " " << minY << " " << maxY << "\n";
        const int P = 1;
        for (int y = maxY; y >= minY; y -= P) {
            for (int x = minX; x <= maxX; x += P) {
                bool v = false;
                for (int ox = 0; !v && ox < P; ++ox) {
                    for (int oy = 0; !v && oy < P; ++oy) {
                        v = grid[x+ox][y-oy];
                    }
                }
                cout << (v ? '#' : '.');
            }
            cout << "\n";
        }
        cout << "\n";
    };

    array<ll,2> res;
    res[0] = 1;
    res[1] = 0;
    
    auto checkFinal = [&]() {
        return minX < N-D && maxX > N+D && minY < N-D && maxY > N+D;
    };

    ll d = 0;
    queue<pair<int,int>> q; // tiles d dist away stored in q by end of iteration
    q.emplace(N, N);
    grid[N][N] = true;
    while (d < s && !checkFinal()) {
        ++d;
        assert(min(minX, minY) > 0 && max(maxX, maxY) <= N*2);
        for (int qi = (int)q.size(); qi > 0; --qi) {
            auto [x, y] = q.front();
            q.pop();
            auto check = [&](int x, int y) {
                if (grid[x][y]) return false;
                grid[x][y] = true;
                q.emplace(x, y);
                return true;
            };
            minX -= check(x-1, y) && x == minX;
            minY -= check(x, y-1) && y == minY;
            maxX += check(x+1, y) && x == maxX;
            maxY += check(x, y+1) && y == maxY;
        }
        res[d & 1] += (ll)q.size();
    }
    
    if (q.empty() || d == s) {
        cout << res[0] << " " << res[1] << "\n";
        return 0;
    }
    
    // since d guaranteed to be a single parity, never have 2 tiles cardinaly adjacent on fringe
    // clear grid aside from fringe
    for (auto &r : grid) r = 0ULL;
    while (!q.empty()) {
        auto [x, y] = q.front();
        grid[x][y] = true;
        q.pop();
    }
    // showGrid();

    // find diagonals
    Diagonal::sumLen = 0;
    vector<Diagonal> diags; // clockwise
    int x = maxX;
    int y = minY;
    while (!grid[x][y]) ++y;
    diags.emplace_back(-1, -1, x, y);
    while (true) {
        grid[x][y] = false;
        Diagonal &l = diags.back();

        // expand diagonal
        if (grid[x+l.dx][y+l.dy]) {
            x += l.dx;
            y += l.dy;
            l.shiftEnd(1);
            continue;
        }

        // look for next diagonal (either rot left or right)
        // rot left: dx=-dy, dy=dx
        // rot right: dx=dy, dy=-dx
        // if neither, we are done
        if (grid[x-l.dy][y+l.dx]) {
            x -= l.dy;
            y += l.dx;
            diags.emplace_back(-l.dy, l.dx, x, y);
        } else if (grid[x+l.dy][y-l.dx]) {
            x += l.dy;
            y -= l.dx;
            diags.emplace_back(l.dy, -l.dx, x, y);
        } else break;
    }

    // simulate expanding diagonals from now onward
    // no more obstacles to track
    // worst case:
    //  /\/\ 
    // /    \ 
    // \    /
    // /    \ 
    // \    /
    //  \/\/
    // track boundary of diagonals, when expanding diagonals make sure to account for overlaps
    // for (auto &r : grid) r = 0ULL;
    // for (auto &d : diags) {
    //     for (int i = 0; i < d.len; ++i) {
    //         int x = d.sx+d.dx*i;
    //         int y = d.sy+d.dy*i;
    //         grid[x][y] = true;
    //     }
    // }
    // minX -= 10;
    // maxX += 10;
    // minY -= 10;
    // maxY += 10;
    // showGrid();

    while (d < s) {
        ++d;

        // expand
        for (int i = 0; i < (int)diags.size(); ++i) {
            Diagonal &a = diags[i];
            Diagonal &b = diags[i+1 == (int)diags.size() ? 0 : i+1];
            a.sy += a.dx;

            // \/ and /\ are all fine (where dx same)
            if (a.dx == b.dx) continue;
            
            bool dirR = b.dx == a.dy; // 0 if left turn 1 if right

            // diverge
            // \ a shift end 1
            // / b shift start -1
            // diverge
            // / b shift start -1
            // \ a shift end 1
            if (dirR) {
                a.shiftEnd(1);
                b.shiftStart(-1);
            }

            // converge
            // / a shift end -1
            // \ b shift start 1
            // converge
            // / b shift start 1
            // \ a shift end -1
            if (!dirR) {
                a.shiftEnd(-1);
                b.shiftStart(1);
            }
        }

        // for (auto &d : diags) {
        //     for (int i = 0; i < d.len; ++i) {
        //         int x = d.sx+d.dx*i;
        //         int y = d.sy+d.dy*i;
        //         grid[x][y] = true;
        //     }
        // }
        // showGrid();

        // add to res
        res[d & 1] += Diagonal::sumLen;
    }
    cout << res[0] << " " << res[1] << "\n";
    return 0;
}
