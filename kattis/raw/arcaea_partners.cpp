// 2024-02-07 02:57:53 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false

typedef long long ll;
typedef long double ld;

struct Partner {
    int x;
    int y;
    bool a;
    Partner() {}
    Partner(int x, int y, bool a = false) : x(x), y(y), a(a) {}
};

struct MaxSegTree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	MaxSegTree(int n = 0, T def = unit) : s(n << 1, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos >>= 1;)
			s[pos] = f(s[pos << 1], s[(pos << 1) + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b >>= 1, e >>= 1) {
			if (b & 1) ra = f(ra, s[b++]);
			if (e & 1) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    // get list of all partners (x=frag, y=step, a=ascended)
    int n, k;
    cin >> n >> k;
    static Partner partners[4000];
    int t = 0;
    for (int i = 0; i < n; ++i) {
        int x2, y2;
        cin >> partners[t].x >>  partners[t].y >> x2 >> y2;
        partners[t++].a = false;
        if (x2) {
            partners[t].x = x2;
            partners[t].y = y2;
            partners[t++].a = true;
        }
    }
    n = t; // for convenience, commented n do not refer to reassigned value

    // sort by increasing x first then decreasing y
    sort(partners, partners + t, [&](Partner& a, Partner& b) {
        return a.x == b.x ? a.y > b.y : a.x < b.x;
    });

    // remap y to its rank (new y < 2n)
    set<int> yVals;
    uint16_t vals[4000];
    for (Partner& p : partners) yVals.insert(p.y);
    for (int i = 0; i < n; ++i) vals[i] = ((int)partners[i].a << 12) | distance(yVals.begin(), yVals.find(partners[i].y));

    // find longest non-increasing subsequence with k awakens
    // since awakened strictly increasing, can never have both in non-increasing subseq
    // keep track of used awakenings with dp state
    // dp[i][a] = longest increasing subsequence with a awakens used ending at partner i-1 (a <= k, i <= 2n)
    // dp[i][a] = max(dp[j<i][a-p[i-1].a] where p[j-1] >= p[i-1]) + 1
    // dp[0][0] = 0
    // dp[-1][a] = 0
    // dp is O(nk) space
    // to find these max vals, can use seg trees such that s[a] maps v to max(dp[j][a] such that p[j] == v) (j < i, v < 2n, a <= k) which is O(nk) space
    // dp[i][a] = s[a-p[i-1].a].query(p[i-1].y, MAX_Y) + 1
    // can discard dp[i][a] after computing since already stored in s (need to keep current row though for adding to s afterwards)

    int maxY = yVals.size();
    vector<MaxSegTree> s(k+1, MaxSegTree(maxY));
    int dp[4000];
    int cache[4000] = {};
    for (int i = 0; i < n; ++i) {
        uint16_t y = vals[i] & 0b111111111111;
        bool awakened = vals[i] & 0b1000000000000;
        dp[0] = 0;
        int cap = min(k, i);
        for (int a = awakened; a <= cap; ++a) {
            dp[a] = s[a-awakened].query(y, maxY) + 1;
        }
        for (int a = 0; a <= cap; ++a) {
            if (dp[a] > cache[y]) {
                cache[y] = dp[a];
                s[a].update(y, dp[a]);
            }
        }
    }
    
    int maxVal = 0;
    for (int a = 0; a <= k; ++a)
        maxVal = max(maxVal, s[a].query(0, maxY));
    cout << maxVal << endl;
}
