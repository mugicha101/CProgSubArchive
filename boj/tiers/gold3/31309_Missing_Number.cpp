/*
Gold 3
31309 - Missing Number
meta: {"problemId": 31309, "titleKo": "Missing Number", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Missing Number", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 20, "level": 13, "votedUserCount": 2, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.9500000476837158, "official": true, "tags": [{"key": "bruteforcing", "isMeta": false, "bojTagId": 125, "problemCount": 2803, "displayNames": [{"language": "ko", "name": "브루트포스 알고리즘", "short": "브루트포스 알고리즘"}, {"language": "en", "name": "bruteforcing", "short": "bruteforce"}, {"language": "ja", "name": "全探索", "short": "全探索"}], "aliases": [{"alias": "완전탐색"}, {"alias": "완전 탐색"}, {"alias": "브루트포스"}, {"alias": "bruteforce"}, {"alias": "brute force"}, {"alias": "완탐"}]}, {"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;
typedef long double ld;

int match(string& s, int i, int v) {
    int vdigs[5];
    int vi = 0;
    while (v) {
        vdigs[vi++] = v % 10;
        v /= 10;
    }
    int len = vi;
    reverse(vdigs, vdigs + vi);
    if (i + vi > s.size())
        return 0;
    while (--vi >= 0) {
        if (s[i + vi] != vdigs[vi])
            return 0;
    }
    return len;
}

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(false);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    int tc;
    cin >> tc;
    string s;
    getline(cin, s);
    while (tc--) {
        getline(cin, s);
        for (char& c : s)
            c -= '0';

        // try all as
        int a = 0;
        set<int> out;
        for (int ia = 0; ia < 5; ++ia) {
            a = a * 10 + s[ia];
            int v = a;
            int i = 0;
            int eaten = -1;
            while (i != s.size()) {
                if (v >= 100000) {
                    eaten = -2;
                    break;
                }
                int mr = match(s, i, v);
                i += mr;
                if (mr == 0) {
                    if (eaten != -1) {
                        eaten = -2;
                        break;
                    }
                    eaten = v;
                }
                ++v;
            }
            if (eaten == -2) // ate more than 1
                continue;
            if (eaten == -1) { // ate a or b
                if (a-1 >= 1 && a-1 < 100000)
                    out.insert(a-1);
                if (v >= 1 && v < 100000)
                    out.insert(v);
            } else // ate eaten
                out.insert(eaten);
        }
        cout << out.size() << endl;
        for (int x : out)
            cout << x << " ";
        cout << "\n";
    }
}
