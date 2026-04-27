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

void solve() {
    // at most k=500 equations
    // |P| = n <= 2000
    // len of leaf at most 5
    // l0 = x
    // l1 = l0 + l0
    // l2 = l1 + l1
    // ...
    // l500 = l499 + l499
    // length of l{i} = 2^i
    // thus length can be 2^499 which makes it unparseable
    // need to greedily match P
    // dp[s][i] = given next char i in P, new i once s parsed
    // for leaf elements is easy enough in O(n)
    // for A = X + Y, dp[A][i] = dp[Y][dp[X][i]]
    int k; cin >> k;
    cin.ignore(100, '\n');
    vector<string> syms;
    vector<tuple<int,int,string>> val; // val[sym] = (a, b, c) means sym = a + b (if a = b = -1, sym has value in c)
    unordered_map<string,int> idMap;
    auto getId = [&](string s) -> int {
        auto it = idMap.find(s);
        if (it != idMap.end()) return it->second;
        syms.push_back(s);
        val.emplace_back(-1,-1,"");
        return idMap[s] = (int)idMap.size();
    };
    for (int i = 0; i < k; ++i) {
        string e;
        getline(cin, e);
        size_t a = e.find('=');
        int l = getId(e.substr(0, a-1));
        size_t b = e.find('+');
        if (b == string::npos) {
            // is not nested
            get<2>(val[l]) = e.substr(a+2);
        } else {
            // is nested
            get<0>(val[l]) = getId(e.substr(a+2, b-1-(a+2)));
            get<1>(val[l]) = getId(e.substr(b+2));
        }
    }
    string p;
    getline(cin, p);
    int start = getId(p);
    getline(cin, p);
    int n = p.size();
    p += ';';
    int m = val.size();

    // toposort dp
    vector<vector<int>> adj(m);
    vector<int> indeg(m);
    queue<int> q;
    vector<vector<int>> dp(m, vector<int>(n+1));
    for (int i = 0; i < m; ++i) {
        auto [a,b,_] = val[i];
        if (a == -1) {
            q.push(i);
            continue;
        }

        adj[a].push_back(i);
        adj[b].push_back(i);
        indeg[i] = 2;
    }
    while (!q.empty()) {
        int i = q.front(); q.pop();
        auto [a,b,v] = val[i];
        if (a == -1) {
            for (int o = 0; o < n; ++o) {
                int x = o;
                for (char c : v) x += c == p[x];
                dp[i][o] = x;
            }
            dp[i][n] = n;
        } else for (int o = 0; o <= n; ++o) dp[i][o] = dp[b][dp[a][o]];
        
        for (int j : adj[i]) if (--indeg[j] == 0) q.push(j);
    }

    cout << (dp[start][0] == n ? "YES" : "NO") << "\n";
}

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);

    int tc; cin >> tc;
    while (tc--) solve();
}
