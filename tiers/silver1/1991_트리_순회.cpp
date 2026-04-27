/*
Silver 1
1991 - 트리 순회
meta: {"problemId": 1991, "titleKo": "트리 순회", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "트리 순회", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 40492, "level": 10, "votedUserCount": 187, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.479200005531311, "official": true, "tags": [{"key": "trees", "isMeta": false, "bojTagId": 120, "problemCount": 1920, "displayNames": [{"language": "ko", "name": "트리", "short": "트리"}, {"language": "en", "name": "tree", "short": "tree"}, {"language": "ja", "name": "木", "short": "木"}], "aliases": [{"alias": "trees"}]}, {"key": "recursion", "isMeta": false, "bojTagId": 62, "problemCount": 311, "displayNames": [{"language": "ko", "name": "재귀", "short": "재귀"}, {"language": "en", "name": "recursion", "short": "recursion"}, {"language": "ja", "name": "再帰", "short": "再帰"}], "aliases": []}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

using namespace std;

using ll = long long;
const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())

void dfs(vector<pair<char,char>> &nodes, char curr, string &preorder, string &inorder, string &postorder) {
    pair<char,char> desc = nodes[curr - 'A'];
    preorder += curr;
    if (desc.first != '.') dfs(nodes, desc.first, preorder, inorder, postorder);
    inorder += curr;
    if (desc.second != '.') dfs(nodes, desc.second, preorder, inorder, postorder);
    postorder += curr;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<pair<char,char>> nodes(n);

    for (int i = 0; i < n; ++i) {
        char curr; cin >> curr;
        auto &[l, r] = nodes[curr - 'A'];
        cin >> l >> r;
    }

    string preorder;
    string inorder;
    string postorder;
    dfs(nodes, 'A', preorder, inorder, postorder);

    cout << preorder << "\n" << inorder << "\n" << postorder << endl;
}
