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

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

ostream& operator<<(ostream& os, i128 x) {
    if (x < 0) {
        x = -x;
        os << '-';
    }
    static char s[40];
    int i = 0;
    while (x) {
        s[i++] = '0' + x % 10;
        x /= 10;
    }
    if (i == 0) s[i++] = '0';
    while (i) os << s[--i];
    return os;
}

istream& operator>>(istream& is, i128 &x) {
    static string s; is >> s;
    x = 0;
    bool neg = s[0] == '-';
    for (int i = 0; i < s.size(); ++i) {
        x = x * 10 + (s[i] - '0');
    }
    if (neg) x = -x;
    return is;
}


ostream& operator<<(ostream& os, u128 x) {
    static char s[40];
    int i = 0;
    while (x) {
        s[i++] = '0' + x % 10;
        x /= 10;
    }
    if (i == 0) s[i++] = '0';
    while (i) os << s[--i];
    return os;
}

istream& operator>>(istream& is, u128 &x) {
    static string s; is >> s;
    x = 0;
    bool neg = s[0] == '-';
    for (int i = 0; i < s.size(); ++i) {
        x = x * 10 + (s[i] - '0');
    }
    if (neg) x = -x;
    return is;
}

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}

template <typename T, typename U>
istream& operator>>(istream& is, pair<T, U>& p) {
    return is >> p.first >> p.second;
}

template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

template <typename... Args>
ostream& operator<<(ostream& os, const tuple<Args...>& t) {
    os << "(";
    apply([&os](const auto&... args) {
        size_t n = 0;
        ((os << (n++ ? ", " : "") << args), ...);
    }, t);
    return os << ")";
}

template <typename... Args>
istream& operator>>(istream& is, tuple<Args...>& t) {
    apply([&is](auto&... args) {
        ((is >> args), ...);
    }, t);
    return is;
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) {
    os << '{';
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream& operator>>(istream &is, T_container &v) {
    for (T &x : v) is >> x;
    return is;
}

template<typename T>
using min_priority_queue = priority_queue<T, vector<T>, greater<T>>;

const ll INF = LLONG_MAX >> 2;

// all primes necessary for the prime factorization of a number <= 100,000
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 
    137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313};

bool prime(ll a) { if (a==1) return 0; ll cap = sqrt(a); for (int i=2;i<=cap;++i) if (a%i==0) return 0; return 1; }

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ hash<T2>{}(p.second); }
};

#define EPS 1e-12
#define each(i, x) for (auto &i : x)
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)
#define getx(a) a.first
#define gety(a) a.second

/**
 * Author: Simon Lindholm
 * Date: 2015-02-18
 * License: CC0
 * Source: marian's (TC) code
 * Description: Aho-Corasick automaton, used for multiple pattern matching.
 * Initialize with AhoCorasick ac(patterns); the automaton start node will be at index 0.
 * find(word) returns for each position the index of the longest word that ends there, or -1 if none.
 * findAll($-$, word) finds all words (up to $N \sqrt N$ many if no duplicate patterns)
 * that start at each position (shortest first).
 * Duplicate patterns are allowed; empty patterns are not.
 * To find the longest words that start at each position, reverse all input.
 * For large alphabets, split each symbol into chunks, with sentinel bits for symbol boundaries.
 * Time: construction takes $O(26N)$, where $N =$ sum of length of patterns.
 * find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
 * Status: stress-tested
 */

// note: findAll returns array m where m[i] = list of indices j where word.substr(i, pat[j].size()) == pat[j]

struct AhoCorasick {
    using vi = vector<int>;
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vi backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[c - first];
			if (m == -1) { n = m = sz(N); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(1, -1) {
		rep(i,0,sz(pat)) insert(pat[i], i);
		N[0].back = sz(N);
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
			rep(i,0,alpha) {
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vi find(string word) {
		int n = 0;
		vi res; // ll count = 0;
		for (char c : word) {
			n = N[n].next[c - first];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vi> findAll(vector<string>& pat, string word) {
		vi r = find(word);
		vector<vi> res(sz(word));
		rep(i,0,sz(word)) {
			int ind = r[i];
			while (ind != -1) {
				res[i - sz(pat[ind]) + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(9);

    int n; cin >> n;
    bool vow[256] = {};
    vow['A'] = vow['E'] = vow['I'] = vow['O'] = vow['U'] = true;
    vector<string> words(n); cin >> words;
    vector<int> wvows(n);
    vector<string> pats;
    map<string,int> patmap; // pat --> index in pats
    vector<int> pws; // pat -> word with max vows
    for (int i = 0; i < n; ++i) {
        string t;
        for (char c : words[i]) {
            if (!vow[c]) t.push_back(c);
            wvows[i] += vow[c];
        }
        auto it = patmap.find(t);
        if (it == patmap.end()) {
            patmap[t] = pats.size();
            pats.push_back(t);
            pws.push_back(-1);
            it = patmap.find(t);
        }
        int &w = pws[it->second];
        if (w == -1 || wvows[w] < wvows[i]) w = i;
    }
    string s; cin >> s;
    n = s.size();

    // find indices that could form a valid word
    // this can be done efficiently with aho
    AhoCorasick aho(pats);
    vector<vector<int>> adj = aho.findAll(pats, s);
    vector<pair<int,int>> dp(n+1, make_pair(-1, -1)); // index -> max vows, prev pattern
    dp[0] = {0,-1};
    for (int i = 0; i < n; ++i) {
        if (dp[i].first == -1) continue;
        
        for (int j : adj[i]) {
            assert(j >= 0 && j < pws.size());
            int w = pws[j];
            int k = i + pats[j].size();
            assert(k <= n);
            int nvows = dp[i].first + wvows[w];
            if (dp[k].first >= nvows) continue;

            dp[k].first = nvows;
            dp[k].second = j;
        }
    }
    assert(dp.back().first != -1);
    vector<int> seq;
    int curr = n;
    while (curr > 0) {
        assert(dp[curr].second != -1);
        assert(dp[curr].second < pws.size());
        int p = dp[curr].second;
        int w = pws[p];
        assert(p >= 0 && p < pats.size() && w >= 0 && w < words.size());
        seq.push_back(w);
        curr -= pats[p].size();
    }
    assert(curr == 0);
    reverse(all(seq));
    for (int i : seq) cout << words[i] << " ";
    cout << "\n";
}