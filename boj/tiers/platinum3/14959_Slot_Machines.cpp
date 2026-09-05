/*
Platinum 3
14959 - Slot Machines
meta: {"problemId": 14959, "titleKo": "Slot Machines", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Slot Machines", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 415, "level": 18, "votedUserCount": 74, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.484299898147583, "official": true, "tags": [{"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "kmp", "isMeta": false, "bojTagId": 40, "problemCount": 115, "displayNames": [{"language": "ko", "name": "KMP", "short": "KMP"}, {"language": "en", "name": "knuth–morris–pratt", "short": "kmp"}, {"language": "ja", "name": "クヌース–モリス–プラット法", "short": "kmp"}], "aliases": []}], "metadata": {}}
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

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

// z algorithm
vector<int> zarr(const vector<int> &s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i >= r) {
            l = i;
            r = i;
            while (r < n && s[r] == s[r-l])
                ++r;
            z[i] = r - l;
        } else if (i + z[i-l] >= r) {
            l = i;
            while (r < n && s[r] == s[r-l])
                ++r;
            z[i] = r-l;
        } else
            z[i] = z[i-l];
    }
    return z;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // find suffix at k that has a repeating cycle of len p s.t. k + p minimal (if tie smaller p)
    // n <= 10^6
    // reverse s - find prefix that has a repeating cycle of len p, k is remaining that doesn't match
    // z-algo - cycle length = i - start
    int n; cin >> n;
    vector<int> s(n);
    for (int i = n-1; i >= 0; --i) cin >> s[i];
    vector<int> z = zarr(s);
    // for (int x : s) cout << x << " ";
    // cout << endl;
    // for (int x : z) cout << x << " ";
    // cout << endl;
    int resP = n, resK = 0;
    for (int p = 1; p < n; ++p) {
        int k = n - (p + z[p]);
        if (p + k < resP + resK || (p + k == resP + resK && p < resP)) {
            resP = p;
            resK = k;
        }
    }
    cout << resK << " " << resP << "\n";
}
