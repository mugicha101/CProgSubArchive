/*
Platinum 5
1517 - 버블 소트
meta: {"problemId": 1517, "titleKo": "버블 소트", "titles": [{"language": "ko", "languageDisplayName": "ko", "title": "버블 소트", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 8588, "level": 16, "votedUserCount": 444, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 3.127000093460083, "official": true, "tags": [{"key": "data_structures", "isMeta": false, "bojTagId": 175, "problemCount": 5114, "displayNames": [{"language": "ko", "name": "자료 구조", "short": "자료 구조"}, {"language": "en", "name": "data structures", "short": "ds"}, {"language": "ja", "name": "データ構造", "short": "ds"}], "aliases": [{"alias": "자료구조"}, {"alias": "자구"}]}, {"key": "sorting", "isMeta": false, "bojTagId": 97, "problemCount": 2427, "displayNames": [{"language": "ko", "name": "정렬", "short": "정렬"}, {"language": "en", "name": "sorting", "short": "sorting"}, {"language": "ja", "name": "ソート", "short": "ソート"}], "aliases": []}, {"key": "segtree", "isMeta": false, "bojTagId": 65, "problemCount": 1714, "displayNames": [{"language": "ko", "name": "세그먼트 트리", "short": "세그먼트 트리"}, {"language": "en", "name": "segment tree", "short": "segtree"}, {"language": "ja", "name": "セグメント木", "short": "セグ木"}], "aliases": [{"alias": "구간트리"}, {"alias": "세그트리"}, {"alias": "fenwick"}, {"alias": "펜윅"}]}, {"key": "divide_and_conquer", "isMeta": false, "bojTagId": 24, "problemCount": 509, "displayNames": [{"language": "ko", "name": "분할 정복", "short": "분할 정복"}, {"language": "en", "name": "divide and conquer", "short": "d&c"}, {"language": "ja", "name": "分割統治法", "short": "分割統治法"}], "aliases": [{"alias": "dnc"}]}], "metadata": {}}
*/

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

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

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
// #define endl "\n"

int temp[500000];

ll inv(vector<int> &vals, int begin, int end) {
    int size = end - begin;

    // base cases
    if (size == 1) return 0;
    else if (size == 2) {
        if (vals[begin] > vals[begin+1]) {
            swap(vals[begin], vals[begin+1]);
            return 1;
        } else {
            return 0;
        }
    }

    // merge
    int mid = (begin + end) >> 1;
    ll count = inv(vals, begin, mid) + inv(vals, mid, end);
    int l = begin, r = mid;
    for (int i = 0; i < size; ++i) {
        if (r != end && (l == mid || vals[l] > vals[r])) {
            temp[i] = vals[r++];
        } else {
            count += r - mid;
            temp[i] = vals[l++];
        }
    }
    for (int i = 0; i < size; ++i) {
        vals[begin + i] = temp[i];
    }
    return count;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n; cin >> n;
    vector<int> vals(n); vcin(vals);

    // count inversions
    cout << inv(vals, 0, vals.size());
}
