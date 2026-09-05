#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;

struct Triangle {
    pair<ll, ll> p[3];
    ll areaTimesTwo;
    Triangle(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
        p[0].first = ax;
        p[0].second = ay;
        p[1].first = bx;
        p[1].second = by;
        p[2].first = cx;
        p[2].second = cy;
        areaTimesTwo = p[0].first * p[1].second - p[0].second * p[1].first + p[1].first * p[2].second - p[1].second * p[2].first + p[2].first * p[0].second - p[2].second * p[0].first;
    }
};

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(true);
#if INPUT
    freopen("./input.txt","r",stdin);
#endif

    // input
    ll V;
    cin >> V;
    vector<pair<int,int>> points;
    points.reserve(V);
    for (ll v = 0; v < V; ++v) {
        ll x, y;
        cin >> x >> y;
        points.emplace_back(x, y);
    }

    // construct all triangles
    deque<Triangle> triangles;
    ll ox = points[0].first;
    ll oy = points[0].second;
    ll remainingArea = 0;
    for (ll v = 2; v < V; ++v) {
        triangles.emplace_back(ox, oy, points[v - 1].first, points[v - 1].second, points[v].first, points[v].second);
        remainingArea += triangles.back().areaTimesTwo;
    }

    // linear search
    while (triangles.size() > 1 && triangles.front().areaTimesTwo * 2 < remainingArea) {
        remainingArea -= triangles.front().areaTimesTwo * 2;
        triangles.pop_front();
    }

    // find proportion along edge to set poll
    Triangle& t = triangles.front();
    if (t.areaTimesTwo == 0)
        throw exception();
    double p = (double)remainingArea / (double)(t.areaTimesTwo * 2);
    double dx = p * (double)(t.p[2].first - t.p[1].first);
    double dy = p * (double)(t.p[2].second - t.p[1].second);
    printf("%.8lf %.8lf", (double)t.p[1].first + dx, (double)t.p[1].second + dy);
}
