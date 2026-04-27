/*
Gold 3
31525 - Streets Behind
meta: {"problemId": 31525, "titleKo": "Streets Behind", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Streets Behind", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 14, "level": 13, "votedUserCount": 3, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.857100009918213, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}], "metadata": {}}
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    int tc;
    cin >> tc;
    while (tc--) {
        ll ser, cas, a, b;
        cin >> ser >> cas >> a >> b;

        if (b * ser < a * ser + a) {
            cout << -1 << endl;
            continue;
        }

        int steps = 0;
        while (cas > 0) {
            auto calcK = [&](ll ser) {
                return (ll)floor((ld)(ser * (b - a)) / (ld)a);
            };
            ll k = calcK(ser);
            // bsearch for new k
            ll r = (cas + k - 1) / k;
            ll l = 1;
            while (l != r) {
                ll m = (l + r) >> 1;
                ll newSer = ser + k * m;
                ll newK = calcK(newSer);
                if (newK == k)
                    l = m+1;
                else
                    r = m;
            }
            steps += l;
            cas -= k * l;
            ser += k * l;
        }
        cout << steps << "\n";
    }
}
