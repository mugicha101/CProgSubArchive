/*
Platinum 1
5044 - Code Theft
meta: {"problemId": 5044, "titleKo": "코드 절도", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "코드 절도", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "Code Theft", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 39, "level": 20, "votedUserCount": 7, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 8.359000205993652, "official": true, "tags": [{"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "hashing", "isMeta": false, "bojTagId": 8, "problemCount": 208, "displayNames": [{"language": "ko", "name": "해싱", "short": "해싱"}, {"language": "en", "name": "hashing", "short": "hash"}, {"language": "ja", "name": "ハッシュ化", "short": "ハッシュ"}], "aliases": []}, {"key": "suffix_array", "isMeta": false, "bojTagId": 77, "problemCount": 133, "displayNames": [{"language": "ko", "name": "접미사 배열과 LCP 배열", "short": "접미사 배열과 LCP 배열"}, {"language": "en", "name": "suffix array and lcp array", "short": "suffix array and lcp array"}, {"language": "ja", "name": "接尾辞配列・LCP配列", "short": "接尾辞配列・LCP配列"}], "aliases": []}], "metadata": {}}
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

#define MOD 1000000009
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

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

#define EPS 1e-9
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

inline void madd(int &x, int v) {
    x += v;
    x = x >= MOD ? x - MOD : x;
}

double randDbl() {
    return (double)rand() / (double)RAND_MAX;
}
uint64_t microsecs() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}
uint64_t seed;
hash<std::string> hasher;
unordered_map<uint64_t, string> col;
uint64_t sh(const string &s) {
    uint64_t h = 3ULL | (seed ^ (uint64_t)hasher(s));
    auto it = col.find(h);
    if (it == col.end()) col[h] = s;
    else assert(it->second == s);

    return h;
}

using h_t = uint64_t; // string hash
typedef pair<ll, int> pli;
using vi = vector<int>;
struct SuffixArray {
	vi a;
	vector<h_t> s;
	SuffixArray(const vector<h_t>& _s) : s(_s) {
        s.push_back(0);
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
			sort(all(b)); // sort(all(b)) can be used as well
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
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);
    
    // n <= 100
    // chars per line <= 254
    // lines <= 10^4*n <= 10^6
    // chars <= 10^6 * 254 < 3*10^8
    // string hash each line so lines become a single char
    // for each candidate t, find max overlap using suffix array on t|m
    // for lcp[i] need to check for s[i] and s[i-1] one is in t, other is in m
    // find max such lcp[i], represents max overlapping substring between t and m

    std::mt19937_64 rng(time(0));
    seed = rng();

    int n; cin >> n;
    cin.ignore(100, '\n');
    vector<string> fname(n);
    vector<vector<h_t>> sc(n);
    auto scan = [&](vector<h_t> &out) {
        string s;
        while (getline(cin, s), s != "***END***") {
            int l = 0;
            int r = s.size()-1;
            while (l < (int)s.size() && s[l] == ' ') ++l;
            while (r >= 0 && s[r] == ' ') --r;
            if (r < 0) continue;

            s = s.substr(l, r+1-l);
            int b = 0;
            int j = 0;
            for (int i = 0; i < (int)s.size(); ++i) {
                b = s[i] == ' ' ? b + 1 : 0;
                if (b <= 1) s[j++] = s[i];
            }
            s.resize(j);
            out.push_back(sh(s));
        }
    };
    for (int i = 0; i < n; ++i) {
        getline(cin, fname[i]);
        auto &lines = sc[i];
        scan(lines);

        // cout << "NAME: " << fname[i] << endl;
        // for (uint64_t h : lines) cout << hex << setfill('0') << setw(16) << h << endl;
        // cout << "\n";
    }
    vector<h_t> m;
    scan(m);
    int k = m.size();
    m.push_back(1);
    
    // for (uint64_t h : m) cout << hex << setfill('0') << setw(16) << h << endl;

    // for each prefix of m and offset in a code snippet, need to find longest common prefix
    int bestLen = 0;
    vector<int> best;
    for (int i = 0; i < n; ++i) {
        auto &lines = sc[i];
        int nl = lines.size();
        m.resize(k+1+nl);
        for (int i = 0; i < nl; ++i) m[i+k+1] = lines[i];
        SuffixArray sa(m);
        int res = 0;
        auto lcp = sa.lcp();
        // cout << lcp << endl;
        for (int i = 1; i < (int)lcp.size(); ++i) {
            if ((sa.a[i-1] < k) == (sa.a[i] < k)) continue;
            // cout << lcp[i] << " " << sa.a[i-1] << " " << sa.a[i] << endl;
            res = max(res, lcp[i]);
        }
        // cout << res << endl;
        // cout << endl;
        if (res == 0 || res < bestLen) continue;

        if (res > bestLen) best.clear();
        bestLen = res;
        best.push_back(i);
    }

    cout << bestLen << " ";
    for (int i : best) cout << fname[i] << " ";
    cout << "\n";
}
