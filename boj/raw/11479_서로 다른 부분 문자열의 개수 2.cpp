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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

using vi = vector<int>;
using pli = pair<ll,int>;
void count_sort(vector<pli> &b, int bits) { // (optional)
    //this is just 3 times faster than stl sort for N=10^6
    int mask = (1 << bits) - 1;
    for(int it = 0; it < 2; ++it) {
        int move = it * bits;
        vi q(1 << bits), w(sz(q) + 1);
        for (int i = 0; i < sz(b); ++i)
            q[(b[i].first >> move) & mask]++;
        partial_sum(q.begin(), q.end(), w.begin() + 1);
        vector<pli> res(b.size());
        for(int i = 0; i < sz(b); ++i)
            res[w[(b[i].first >> move) & mask]++] = b[i];
        swap(b, res);
    }
}
struct SuffixArray {
    vi a;
    string s;
    SuffixArray(const string& _s) : s(_s + '\0') {
        int N = sz(s);
        vector<pli> b(N);
        a.resize(N);
        for(int i = 0; i < N; ++i) {
            b[i].first = s[i];
            b[i].second = i;
        }

        int q = 8;
        while ((1 << q) < N) q++;
        for (int moc = 0;; moc++) {
            count_sort(b, q); // sort(all(b)) can be used as well
            a[b[0].second] = 0;
            for(int i = 1; i < N; ++i)
                a[b[i].second] = a[b[i - 1].second] +
                    (b[i - 1].first != b[i].first);

            if ((1 << moc) >= N) break;
            for (int i = 0; i < N; ++i) {
                b[i].first = (ll)a[i] << q;
                if (i + (1 << moc) < N)
                    b[i].first += a[i + (1 << moc)];
                b[i].second = i;
            }
        }
        for(int i = 0; i < sz(a); ++i) a[i] = b[i].second;
    }
    vi lcp() {
        // longest common prefixes: res[i] = lcp(a[i], a[i-1])
        int n = sz(a), h = 0;
        vi inv(n), res(n);
        for (int i = 0; i < n; ++i) inv[a[i]] = i;
        for (int i = 0; i < n; ++i) if (inv[i] > 0) {
            int p0 = a[inv[i] - 1];
            while (s[i + h] == s[p0 + h]) h++;
            res[inv[i]] = h;
            if(h > 0) h--;
        }
        return res;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // given lcp[i] = k
    // we know suffix i only unique after k chars long
    // thus add |suffix|-k to result
    // last suffix has no next suffix so treat entire as unique
    // since we cant easily get length of each suffix, we calculate total lengths of all suffixes using geo sum and subtract k from them
    string s; cin >> s;
    SuffixArray sa(s);
    vi lcp = sa.lcp();
    ll res = s.size() * (s.size() + 1) / 2;
    for(int i = 1; i < sz(lcp); ++i) res -= lcp[i];
    cout << res << '\n';
}