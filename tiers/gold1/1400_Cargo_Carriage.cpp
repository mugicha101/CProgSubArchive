/*
Gold 1
1400 - Cargo Carriage
meta: {"problemId": 1400, "titleKo": "화물차", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "화물차", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Cargo Carriage", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 306, "level": 15, "votedUserCount": 22, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.104599952697754, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "shortest_path", "isMeta": false, "bojTagId": 215, "problemCount": 990, "displayNames": [{"language": "ko", "name": "최단 경로", "short": "최단 경로"}, {"language": "en", "name": "shortest path", "short": "shortest path"}, {"language": "ja", "name": "最短経路", "short": "最短経路"}], "aliases": []}, {"key": "dijkstra", "isMeta": false, "bojTagId": 22, "problemCount": 725, "displayNames": [{"language": "ko", "name": "데이크스트라", "short": "데이크스트라"}, {"language": "en", "name": "dijkstra's", "short": "dijkstra's"}, {"language": "ja", "name": "ダイクストラ法", "short": "ダイクストラ法"}], "aliases": [{"alias": "다익"}, {"alias": "다익스트라"}, {"alias": "데이크스트라"}]}], "metadata": {}}
*/

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

template <class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
};

struct Light {
    int nsOffset; // first time ns is on
    int nsPeriod; // length of period spent with ns on (period always starts ns on)
    int totalPeriod; // total length of period

    void set(int ewPeriod, int nsPeriod, bool nsFirst) {
        nsOffset = nsFirst ? 1 : 1 + ewPeriod;
        this->nsPeriod = nsPeriod;
        totalPeriod = nsPeriod + ewPeriod;
    }

    inline bool nsOn(int turn) const { return ((((turn - nsOffset) % totalPeriod) + totalPeriod) % totalPeriod) < nsPeriod; }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    while (true) {
        int rows, cols;
        cin >> rows >> cols;
        if (rows == 0 && cols == 0) break;

        vector<string> grid(rows);
        vector<Light> lights;
        pair<int,int> src;
        pair<int,int> dst;
        for (int r = 0; r < rows; ++r) {
            cin >> grid[r];
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] >= '0' && grid[r][c] <= '9') lights.emplace_back();
                else if (grid[r][c] == 'A') src = make_pair(r, c);
                else if (grid[r][c] == 'B') dst = make_pair(r, c);
            }
        }
        for (Light &l : lights) {
            int idx, ewPeriod, nsPeriod;
            char first;
            cin >> idx >> first >> ewPeriod >> nsPeriod;
            l.set(ewPeriod, nsPeriod, first == '|');
        }
        int turn = 0;
        grid[dst.first][dst.second] = '#';

        queue<pair<int,int>> q;
        q.push(src);
        while (!q.empty() && grid[dst.first][dst.second] == '#') {
            ++turn;
            for (int qi = q.size(); qi > 0; --qi) {
                auto [r, c] = q.front();
                q.pop();
                bool offLight = false;

                auto check = [&](int r, int c, bool ns) {
                    if (grid[r][c] == 'A' || grid[r][c] == '.') return;
                    if (grid[r][c] != '#' && lights[grid[r][c]-'0'].nsOn(turn) ^ ns) {
                        offLight = true;
                        return;
                    }

                    grid[r][c] = 'A';
                    q.emplace(r, c);
                };

                if (r) check(r-1, c, true);
                if (c) check(r, c-1, false);
                if (r+1 < rows) check(r+1, c, true);
                if (c+1 < cols) check(r, c+1, false);
                if (offLight) q.emplace(r, c);
            }
        }
        cout << (grid[dst.first][dst.second] == 'A' ? to_string(turn) : "impossible") << endl;
    }
}
