/*
Platinum 3
31509 - Cramming for Finals
meta: {"problemId": 31509, "titleKo": "Cramming for Finals", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Cramming for Finals", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 20, "level": 18, "votedUserCount": 3, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.4000000953674316, "official": true, "tags": [{"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "geometry", "isMeta": false, "bojTagId": 100, "problemCount": 2046, "displayNames": [{"language": "ko", "name": "기하학", "short": "기하학"}, {"language": "en", "name": "geometry", "short": "geom"}, {"language": "ja", "name": "幾何学", "short": "幾何"}], "aliases": []}, {"key": "sweeping", "isMeta": false, "bojTagId": 106, "problemCount": 708, "displayNames": [{"language": "ko", "name": "스위핑", "short": "스위핑"}, {"language": "en", "name": "sweeping", "short": "sweeping"}, {"language": "ja", "name": "平面走査", "short": "平面走査"}], "aliases": [{"alias": "라인 스위핑"}]}, {"key": "two_pointer", "isMeta": false, "bojTagId": 80, "problemCount": 490, "displayNames": [{"language": "ko", "name": "두 포인터", "short": "두 포인터"}, {"language": "en", "name": "two-pointer", "short": "two-pointer"}, {"language": "ja", "name": "尺取り法", "short": "尺取り"}], "aliases": [{"alias": "투포인터"}, {"alias": "인치웜"}, {"alias": "inchworm"}, {"alias": "twopointer"}]}], "metadata": {}}
*/

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

    cout << minCircles << "\n";
    return 0;

    empty:
    cout << 0 << "\n";
}
