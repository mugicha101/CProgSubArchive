/*
Gold 1
16411 - Illiteracy
meta: {"problemId": 16411, "titleKo": "Illiteracy", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Illiteracy", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 28, "level": 15, "votedUserCount": 7, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.892899990081787, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "graphs", "isMeta": false, "bojTagId": 7, "problemCount": 5085, "displayNames": [{"language": "ko", "name": "그래프 이론", "short": "그래프 이론"}, {"language": "en", "name": "graph theory", "short": "graph"}, {"language": "ja", "name": "グラフ理論", "short": "グラフ"}], "aliases": [{"alias": "그래프이론"}, {"alias": "그래프"}]}, {"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "graph_traversal", "isMeta": false, "bojTagId": 11, "problemCount": 2501, "displayNames": [{"language": "ko", "name": "그래프 탐색", "short": "그래프 탐색"}, {"language": "en", "name": "graph traversal", "short": "traversal"}, {"language": "ja", "name": "グラフの探索", "short": "横断"}], "aliases": [{"alias": "bfs"}, {"alias": "dfs"}]}, {"key": "bfs", "isMeta": false, "bojTagId": 126, "problemCount": 1227, "displayNames": [{"language": "ko", "name": "너비 우선 탐색", "short": "너비 우선 탐색"}, {"language": "en", "name": "breadth-first search", "short": "bfs"}, {"language": "ja", "name": "幅優先検索", "short": "bfs"}], "aliases": [{"alias": "breadthfirst"}, {"alias": "breadth first"}]}, {"key": "hash_set", "isMeta": false, "bojTagId": 136, "problemCount": 789, "displayNames": [{"language": "ko", "name": "해시를 사용한 집합과 맵", "short": "해시를 사용한 집합과 맵"}, {"language": "en", "name": "set / map by hashing", "short": "hashset"}, {"language": "ja", "name": "ハッシュ化によるセット・マップ", "short": "hashset"}], "aliases": [{"alias": "집합"}, {"alias": "맵"}, {"alias": "셋"}, {"alias": "딕셔너리"}, {"alias": "dictionary"}, {"alias": "map"}, {"alias": "set"}, {"alias": "해싱"}, {"alias": "hashing"}, {"alias": "dict"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000007
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
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

int hashs(string s) {
    int res = 0;
    for (int i = 0; i < 8; ++i) {
        res |= (s[i] - 'A') << (i*3);
    }
    return res;
}


inline char fetch(int h, int i) {
    return (h >> (i*3)) & 0b111;
}

void show(int h) {
    for (int i = 0; i < 8; ++i) cout << (char)('A'+fetch(h,i));
}

void rot(int &h, int i) {
    if (i < 0 || i >= 8) return;
    h += fetch(h, i) == 5 ? -(5 << (i*3)) : (1 << (i*3));
}

int op(int h, int i) {
    // show(h);
    // cout << " " << i;
    switch (fetch(h, i)) {
        case 0:
            rot(h, i-1);
            rot(h, i+1);
            break;
        case 1:
            if (i > 0 && i < 7) {
                int a = fetch(h, i-1);
                int b = fetch(h, i+1);
                h += ((a-b) << ((i+1)*3));
            }
            break;
        case 2:
            rot(h, 7-i);
            break;
        case 3:
            if (i < 4) {
                for (int j = 0; j < i; ++j) rot(h, j);
            } else {
                for (int j = i+1; j < 8; ++j) rot(h, j);
            }
            break;
        case 4:
            if (i > 0 && i < 7) {
                int d = min(i, 7-i);
                rot(h, i-d);
                rot(h, i+d);
            }
            break;
        case 5:
            if ((i+1) & 1) {
                rot(h, ((i+1) + 9) / 2 - 1);
            } else {
                rot(h, (i+1) / 2 - 1);
            }
            break;
    }
    // cout << " -> ";
    // show(h);
    // cout << endl;
    return h;
}

int main() {
    cin.tie()->sync_with_stdio(0);
    cout << fixed << setprecision(12);
    
    string s, t; cin >> s >> t;
    int sh = hashs(s), th = hashs(t);
    // show(sh);
    // show(th);
    queue<int> q;
    vector<bool> seen(8*8*8*8*8*8*8*8);
    seen[sh] = true;
    q.push(sh);
    int d = 0;

    while (!q.empty() && !seen[th]) {
        ++d;
        // cout << "d=" << d << endl;
        for (int qi = q.size(); qi > 0; --qi) {
            int curr = q.front();
            q.pop();
            for (int i = 0; i < 8; ++i) {
                int next = op(curr, i);
                if (seen[next]) continue;

                // cout << "add" << endl;
                seen[next] = true;
                q.push(next);
            }
        }
    }
    cout << (seen[th] ? d : -1) << "\n";
}
