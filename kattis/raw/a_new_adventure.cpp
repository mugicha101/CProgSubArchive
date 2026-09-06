// 2023-03-08 15:51:47 
#include <bits/stdc++.h>

typedef long long ll;
typedef long double ld;
#define INPUT false

using namespace std;

struct Pos {
    int r;
    int c;
    int t;
    Pos(int r, int c, int t) : r(r), c(c), t(t) {}
};

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    // input
    int circs, arcs;
    cin >> circs >> arcs;
    // storing movement relative to bike starting position
    cin.ignore(100, '\n');
    vector<vector<bool>> visited(circs, vector<bool>(arcs, false));
    for (int c = 0; c < circs; ++c) {
        string circle;
        getline(cin, circle);
        for (int a = 0; a < arcs; ++a) {
            if (circle[a] != 'M')
                continue;
            visited[c][a == 0? arcs - 1 : a - 1] = true;
            visited[c][a] = true;
        }
    }
    vector<Pos> heap;
    auto cmp = [&](Pos& a, Pos& b) {
        return a.t == b.t? a.r < b.r : a.t > b.t;
    };
    heap.emplace_back(0, 0, 0);
    visited[0][0] = false;
    int time = -1;
    while (time == -1 && !heap.empty()) {
        pop_heap(heap.begin(), heap.end(), cmp);
        Pos p = move(heap.back());
        heap.pop_back();
        if (visited[p.r][p.c])
            continue;
        visited[p.r][p.c] = true;
        auto check = [&](Pos p) {
            if (p.r == circs) {
                time = p.t;
                return;
            }
            if (visited[p.r][p.c])
                return;
            heap.emplace_back(p.r, p.c, p.t);
            push_heap(heap.begin(), heap.end(), cmp);
        };
        int c1 = p.c == 0? arcs - 1 : p.c - 1;
        int c2 = c1 == 0? arcs - 1 : c1 - 1;
        check(Pos(p.r + 1, c1, p.t + 1));
        check(Pos(p.r, c1, p.t + 1));
        if (arcs != 1)
            check(Pos(p.r, c2, p.t + 1));
        if (p.r != 0)
            check(Pos(p.r - 1, c1, p.t + 1));
    }
    cout << time << endl;
}
