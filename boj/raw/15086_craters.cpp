#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

#define M_PI 3.14159265358979323846L
const ld ROT_FULL = M_PI * 2.L;
const ld ROT_HALF = M_PI;
const ld ROT_QUARTER = M_PI * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

ld distSqd(ld x1, ld y1, ld x2, ld y2) {
    ld dx = x2 - x1;
    ld dy = y2 - y1;
    return dx * dx + dy * dy;
}

ld dist(ld x1, ld y1, ld x2, ld y2) {
    return sqrt(distSqd(x1, y1, x2, y2));
}

// convert angle in [-2pi,2pi) to [0,2pi)
ld angleNorm(ld a) {
    return a < 0 ? a + ROT_FULL : a;
}

// positive angle diff between a and b s.t. (a + diff) mod 2pi = b mod 2pi
// a and b must be in [0,2pi)
// result in [0,2pi)
ld angleDiff(ld a, ld b) {
    return angleNorm(b - a);
}

// add angles
// a and b must be in [0,2pi)
// result in [0,2pi)
ld angleSum(ld a, ld b) {
    ld s = a + b;
    return s >= ROT_FULL ? s - ROT_FULL : s;
}

// angle from one point to another
// result in [0,2pi)
ld angleTo(ld x1, ld y1, ld x2, ld y2) {
    return angleNorm(atan2(y2 - y1, x2 - x1));
}

ld prop(ld angle) { return angle / ROT_FULL; };

struct Circ {
    ld x;
    ld y;
    ld r;
    bool a; // true if circle is valid and not yet on the hull

    // find line tangent to both circles
    // return angle between vector from A to B and the point
    static ld chAngle(Circ a, Circ b) {
        // printf("A=(%lf,%lf,%lf) B=(%lf,%lf,%lf)\n", (double)a.x, (double)a.y, (double)a.r, (double)b.x, (double)b.y, (double)b.r);
        // let the input circles be A and B s.t. A's radius >= B's radius
        // math works the same without this

        // let T be the line tangent to A and B
        // let D be the line from A's center to B's center
        // ld dMagSqd = distSqd(a.x, a.y, b.x, b.y);
        
        // let circle C be A with its radius reduced by B's radius
        // ld cr = a.r - b.r;

        // let H be the line tangent to C and B's center
        // H's angle and distance matches T
        // right triangle formed with H as a leg and D as the hypotenuse
        // |T| = |H| = sqrt(|D|^2 - (C's radius)^2)
        // ld hMag = sqrt(dMagSqd - cr * cr);

        // relative to angle from A to B:
        // let t be the angle from A and B's centers to its point on T
        // this is the same as the angle from C's center to its point on H
        // |H| = |D|cos(t)
        // t = atan2(x=C's radius, y=|H|)
        // actually returning -t since need righthand tangent

        // ld t = ROT_FULL - angleTo(0, 0, cr, hMag);
        // cout << "t=" << prop(t) << endl;

        // COMBINED EQUATION:
        return angleNorm(-atan2(sqrt(distSqd(a.x, a.y, b.x, b.y) - (a.r - b.r) * (a.r - b.r)), a.r - b.r));
    }

    // point on circle at given angle from center
    ld px(ld angle) { return x + r * cos(angle); }
    ld py(ld angle) { return y + r * sin(angle); }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    int n;
    cin >> n;
    vector<Circ> circs(n);
    for (Circ &c : circs) {
        cin >> c.x >> c.y >> c.r;
        c.r += 10.L;
        c.a = true;
    }

    // remove any circles inside another circle
    // also handles duplicate circles
    for (int i = 0; i < n; ++i) {
        if (!circs[i].a) continue;
        for (int j = 0; j < n; ++j) {
            if (i == j || !circs[j].a) continue;

            if (circs[j].r >= circs[i].r) {
                // invalidate j if circ i == circ j and j > i
                // this keeps only the first instance of a circle valid
                circs[j].a = j < i || !(circs[j].r == circs[i].r && circs[i].x == circs[j].x && circs[i].y == circs[j].y);
            } else {
                // invalidate j if circ j inside circ i
                ld rdiff = circs[i].r - circs[j].r;
                circs[j].a = distSqd(circs[i].x, circs[i].y, circs[j].x, circs[j].y) > rdiff * rdiff;
            }
        }
    }

    // filter out invalid circles
    int j = 0;
    for (int i = 0; i < n; ++i) {
        // cout << circs[i].a << " ";
        if (circs[i].a) circs[j++] = circs[i];
    }
    // cout << endl;
    circs.resize(j);

    /*
    for (Circ &c : circs) {
        cout << c.x << " " << c.y << " " << c.r << endl;
    }
    */
    n = circs.size();

    // convex hull on circles
    // use gift-wrapping algorithm (pick leftmost, wrap ccw) since n is small

    // find circle with left-most point
    ld minX = circs[0].x - circs[0].r;
    int minXCirc = 0;
    for (int i = 0; i < n; ++i) {
        ld left = circs[i].x - circs[i].r;
        if (left < minX) {
            minX = left;
            minXCirc = i;
        }
    }

    // handle edge cases:
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    if (n == 1) {
        cout << circs[0].r * ROT_FULL << endl;
        return 0;
    }

    // giftwrapping
    ld fencing = 0.L;
    vector<int> hull(1, minXCirc); // list of circles on the hull in ccw order
    ld hullAngle = ROT_FULL - ROT_QUARTER; // previous angle in hull
    ld firstAngle = 0.L;
    int curr = minXCirc;
    do {
        int next = curr;
        ld nextAngleDiff = M_PI * 2L;
        ld nextAngle = hullAngle;
        ld nextP = 0.L;
        // cout << "curr: " << curr << " hullAngle: " << prop(hullAngle) << endl;
        for (int i = 0; i < n; ++i) {
            if (curr == i) continue;
            Circ &a = circs[curr];
            Circ &b = circs[i];

            // find angle of tangent line
            ld t = Circ::chAngle(a, b);
            ld dir = angleTo(a.x, a.y, b.x, b.y);
            ld p = angleSum(t, dir);
            ld tangentAngle = angleTo(a.px(p), a.py(p), b.px(p), b.py(p));
            ld diff = angleDiff(hullAngle, tangentAngle);
            // cout << "tangent: (" << a.px(p) << "," << a.py(p) << ") -> (" << b.px(p) << "," << b.py(p) << ")" << endl;
            // cout << "target: " << i << " p: " << prop(p) << " dir: " << prop(dir) << " tangentAngle: " << prop(tangentAngle) << " diff: " << prop(diff) << endl;
            if (diff >= nextAngleDiff) continue;

            // next is the angle with the lowest diff to the current hull angle
            next = i;
            nextAngleDiff = diff;
            nextAngle = tangentAngle;
            nextP = p;
        }
        if (hull.size() > 1 && curr == hull[0] && next == hull[1]) break;

        // update fencing
        fencing += dist(circs[curr].px(nextP), circs[curr].py(nextP), circs[next].px(nextP), circs[next].py(nextP));
        if (curr == minXCirc) firstAngle = nextAngle;
        else fencing += nextAngleDiff * circs[curr].r;
        // printf("%d -> %d: p: %lf hullAngle: %lf -> %lf, fencing=%lf\n", curr, next, (double)nextP, (double)prop(hullAngle), (double)prop(nextAngle), (double)fencing);

        // add next to the hull
        hull.push_back(next);
        circs[next].a = false;
        hullAngle = nextAngle;
        curr = next;
    } while (true);
    fencing += angleDiff(hullAngle, firstAngle) * circs[curr].r;

    cout << fencing << endl;
}
