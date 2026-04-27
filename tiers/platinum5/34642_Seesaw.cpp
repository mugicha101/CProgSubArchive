/*
Platinum 5
34642 - Seesaw
meta: {"problemId": 34642, "titleKo": "Seesaw", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Seesaw", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 11, "level": 16, "votedUserCount": 2, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.272700071334839, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "disjoint_set", "isMeta": false, "bojTagId": 81, "problemCount": 675, "displayNames": [{"language": "ko", "name": "분리 집합", "short": "분리 집합"}, {"language": "en", "name": "disjoint set", "short": "dsu"}, {"language": "ja", "name": "素集合データ構造", "short": "素集合データ構造"}], "aliases": [{"alias": "union"}, {"alias": "find"}, {"alias": "유니온"}, {"alias": "파인드"}, {"alias": "dsu"}]}], "metadata": {}}
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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

// #define DB 1
#if DB
#else
#define assert(c)
#endif

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    // seesaw pivot at 0
    // want sum(pos * weight) = 0
    // balance seesaw without changing ordering of people with minimal change in positions
    // end positions can be decimal

    // set left side to be heavier
    // want to maximize change in balance per change in distance
    // person p of weight w moving distance d changes balance by d * w
    // when a bunch of people overlap (a group), change in balance / change in distance = average weight of people at or right of person being moved
    // let f(g) = change in balance / change in distance for group g = average weight of person in g
    // invariant to maintain for all groups g: average weight of g >= average weight of suffix of g
    // this means when merging groups, optimal to either combine both groups or keep only right group
    // TODO: edge case of when avgs equal (split - less room to move right, merge - may be better to drop a half later)
    // this means as group grows, can only improve in average weight
    // note: since moving to next person unless balanced, positions always integral if not balanced
    // algo:
    // - pq q = {p} for each person p sorted by f
    // - pop top of q
    // - move until balanced or blocked by another group
    // - if joins another group, add f({p, ...rest of stack}) into q and remove stack from q
    // - never stops alone unless seesaw balanced
    // - repeat popping until seesaw balanced
    // O(nlgn)

    int n; cin >> n;
    ll bal = 0;
    vector<pair<int,int>> a(n);

    for (auto &[x, w] : a) {
        cin >> x >> w;
        bal -= (ll)x * w;
    }

    // make left side of seesaw heavier
    if (bal < 0) {
        for (auto &[x, w] : a) x = -x;
        bal = -bal;
        reverse(a.begin(), a.end());
    }

    struct Group {
        ll x; // position
        ll w;
        ll n;
        int id;
        bool active;
        inline double aw() const {
            return (double)w / n;
        }
        inline string str() const {
            return "(" + to_string(x) + "," + to_string(w) + "," + to_string(n) + ")";
        }
    };
    vector<Group> groups(n);
    vector<int> g(n);
    iota(g.begin(), g.end(), 0);

    // to make things easier, store using sets with <sort index, group index> since number of groups can only decrease
    set<pair<double,int>> ws; // sorted by avg weight
    set<pair<ll,int>> ps; // sorted by position
    auto rem = [&](int id) {
        assert(id >= 0 && id < n);
        Group &g = groups[id];
        assert(g.active);
        g.active = false;
        auto itWs = ws.find(make_pair(-g.aw(), id));
        assert(itWs != ws.end());
        ws.erase(itWs);
        auto itPs = ps.find(make_pair(g.x, id));
        assert(itPs != ps.end());
        ps.erase(itPs);
    };
    auto add = [&](int id) {
        assert(id >= 0 && id < n);
        Group &g = groups[id];
        assert(!g.active);
        g.active = true;
        size_t s = ws.size() + 1;
        ws.emplace(-g.aw(), id);
        ps.emplace(g.x, id);
        assert(ws.size() == s);
        assert(ps.size() == s);
    };

    
    for (int i = 0; i < n; ++i) {
        groups[i].x = a[i].first;
        groups[i].w = a[i].second;
        groups[i].n = 1;
        groups[i].active = false;
        add(i);
    }

    double res = 0;
    while (bal > 0) {
        assert(!ws.empty());
        assert(ws.size() == ps.size());

        // SANITY CHECKS
        // check balance
        #if DB
        ll tb1 = 0, tb2 = 0;
        ll m = 0;
        for (int i = 0; i < n; ++i) {
            tb2 -= groups[g[i]].x * a[i].second;
            m += groups[g[i]].x - a[i].first;
            if (!groups[i].active) continue;

            tb1 -= groups[i].x * groups[i].w;
        }
        pause();
        cout << m << " " << res << endl;
        assert(m == (ll)round(res));
        assert(tb1 == bal);
        assert(tb2 == bal);
        pause();

        // ensure ordering valid
        for (int i = 0; i < n; ++i) cout << groups[g[i]].x << " ";
        cout << endl;
        for (int i = 0; i < n-1; ++i) {
            assert(groups[g[i]].x <= groups[g[i+1]].x);
        }
        #endif

        // get group with highest weight
        int currId = ws.begin()->second;
        Group &curr = groups[currId];
        rem(currId);
        #if DB
        cout << bal << " " << res << " " << curr.str() << endl;
        #endif
        
        // find next group to right
        auto it = ps.upper_bound(make_pair(curr.x, -1));
        ll nx = it == ps.end() ? 0 : it->first;
        ll d = nx - curr.x;
        if (it == ps.end() || d * curr.w >= bal) { // d < 10^8, w < 10^10, d * w < 10^18 < 2^60, should not overflow but cannot use INT_MAX in place of d
            // move until balanced
            // bal = curr.w * dd
            // dd = bal / curr.w
            // res += dd * curr.n
            double dd = (double)bal / curr.w;
            #if DB
            cout << "MOVE " << curr.x << " to " << ((double)curr.x + dd) << endl;
            #endif
            res += dd * curr.n;
            bal = 0;
            break;
        }

        // move to next group
        int nextId = it->second;
        assert(nextId >= 0 && nextId < n);
        Group &next = groups[nextId];
        res += d * curr.n;
        #if DB
        cout << "MOVE " << curr.x << " to " << next.x << endl;
        cout << "bal: " << bal << " -> ";
        #endif
        bal -= d * curr.w;
        curr.x = next.x;
        if (curr.aw() < next.aw()) continue; // if curr avg weight <= next avg weight, only keep next

        // merge groups
        #if DB
        cout << "MERGE " << next.x << endl;
        #endif
        rem(nextId);
        next.n += curr.n;
        next.w += curr.w;
        curr.n = 0;

        #if DB
        for (int i = 0; i < n; ++i) if (g[i] == currId) g[i] = nextId;
        #endif
        add(nextId);
    }
    
    cout << res << endl;
}
