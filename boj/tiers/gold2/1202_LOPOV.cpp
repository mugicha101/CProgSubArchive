/*
Gold 2
1202 - LOPOV
meta: {"problemId": 1202, "titleKo": "보석 도둑", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "보석 도둑", "isOriginal": false}, {"language": "en", "languageDisplayName": "en", "title": "LOPOV", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 18597, "level": 14, "votedUserCount": 399, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 4.114299774169922, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "greedy", "isMeta": false, "bojTagId": 33, "problemCount": 3473, "displayNames": [{"language": "ko", "name": "그리디 알고리즘", "short": "그리디 알고리즘"}, {"language": "en", "name": "greedy", "short": "greedy"}, {"language": "ja", "name": "貪欲法", "short": "貪欲法"}], "aliases": [{"alias": "탐욕법"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "priority_queue", "isMeta": false, "bojTagId": 59, "problemCount": 575, "displayNames": [{"language": "ko", "name": "우선순위 큐", "short": "우선순위 큐"}, {"language": "en", "name": "priority queue", "short": "priority queue"}, {"language": "ja", "name": "優先度付きキュー", "short": "優先度付きキュー"}], "aliases": [{"alias": "heap"}, {"alias": "힙"}]}], "metadata": {}}
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

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // cout.tie(0); // comment out for baekjoon
    cout << fixed << setprecision(12);

    int n, k; cin >> n >> k;
    // greedily pick most valueable gem, place in smallest remaining bag it fits in
    vector<pair<ll,ll>> gems(n); // value, weight
    multiset<ll> bags;
    for (auto &[v, w] : gems) cin >> w >> v;
    while (k--) {
        int b; cin >> b;
        bags.insert(b);
    }
    sort(all(gems), greater<pair<ll,ll>>());

    ll val = 0;
    for (auto [v, w] : gems) {
        if (bags.empty()) break;

        // get smallest bag fitting gem
        auto it = bags.lower_bound(w);
        if (it == bags.end()) continue;

        val += v;
        bags.erase(it);
    }

    cout << val << endl;
}
