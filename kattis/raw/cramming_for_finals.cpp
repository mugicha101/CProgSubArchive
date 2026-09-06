// 2024-02-25 14:46:19 
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

struct End {
    int row;
    int col;
    int d; // 1 = left, -1 = right, n = center left, -n = center right
    End() {}
    End(int row, int col, int d) : row(row), col(col), d(d) {}
    inline bool operator<(End &other) {
        return row == other.row ? col == other.col ? d > other.d : col < other.col : row < other.row;
    }
};

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    // input
    int rows, cols, d, n;
    cin >> rows >> cols >> d >> n;

    // calculate intervals of each circle on each row, store end points in sorted list
    // to ensure centers never picked (unless all tables occupied which presumably doesn't happen), treat them as n 0 radius tables
    ll dSqd = (ll)d * (ll)d;
    vector<End> ends;
    for (int i = 0; i < n; ++i) {
        int centerR, centerC;
        cin >> centerR >> centerC;
        --centerR; --centerC;
        int rStart = max(centerR - d, 0);
        int rEnd = min(centerR + d, rows - 1);
        for (int r = rStart; r <= rEnd; ++r) {
            ll dr = r - centerR;
            int dc = sqrt(dSqd - dr * dr);
            ends.emplace_back(r, max(centerC - dc, 0), 1);
            ends.emplace_back(r, min(centerC + dc, cols-1) + 1, -1);
        }
        ends.emplace_back(centerR, centerC, n);
        ends.emplace_back(centerR, centerC+1, -n);
    }
    ends.emplace_back(-1, -1, 0);
    ends.emplace_back(INT_MAX, INT_MAX, 1);
    sort(ends.begin(), ends.end());

    // traverse list of end points row by row to find minimum overlap
    int next = 1;
    int minCircles = INT_MAX;
    while (ends[next].row != INT_MAX) {
        int r = ends[next].row;
        int overlap = 0;
        while (ends[next].row == r && ends[next].col == 0) {
            overlap += ends[next].d;
            ++next;
        }
        if (overlap == 0) goto empty;
        minCircles = min(overlap, minCircles);
        while (ends[next].row == r && ends[next].col < cols) {
            overlap += ends[next].d;
            ++next;
            minCircles = min(overlap, minCircles);
        }
        if (overlap == 0) goto empty;
        while (ends[next].row == r) ++next;
    }

    cout << minCircles << endl;
    return 0;

    empty:
    cout << 0 << endl;
}

