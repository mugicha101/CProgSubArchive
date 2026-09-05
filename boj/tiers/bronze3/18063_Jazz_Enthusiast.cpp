/*
Bronze 3
18063 - Jazz Enthusiast
meta: {"problemId": 18063, "titleKo": "Jazz Enthusiast", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Jazz Enthusiast", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 360, "level": 3, "votedUserCount": 35, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 1.4388999938964844, "official": true, "tags": [{"key": "math", "isMeta": false, "bojTagId": 124, "problemCount": 8082, "displayNames": [{"language": "ko", "name": "수학", "short": "수학"}, {"language": "en", "name": "mathematics", "short": "math"}, {"language": "ja", "name": "数学", "short": "数学"}], "aliases": []}, {"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "string", "isMeta": false, "bojTagId": 158, "problemCount": 2964, "displayNames": [{"language": "ko", "name": "문자열", "short": "문자열"}, {"language": "en", "name": "string", "short": "string"}, {"language": "ja", "name": "文字列", "short": "文字列"}], "aliases": [{"alias": "스트링"}]}, {"key": "arithmetic", "isMeta": false, "bojTagId": 121, "problemCount": 1374, "displayNames": [{"language": "ko", "name": "사칙연산", "short": "사칙연산"}, {"language": "en", "name": "arithmetic", "short": "arithmetic"}, {"language": "ja", "name": "算数", "short": "算数"}], "aliases": [{"alias": "덧셈"}, {"alias": "뺄셈"}, {"alias": "곱셈"}, {"alias": "나눗셈"}, {"alias": "더하기"}, {"alias": "빼기"}, {"alias": "곱하기"}, {"alias": "나누기"}]}], "metadata": {}}
*/

#include <bits/stdc++.h>
 
using namespace std;
 
/*
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const int MOD = 1000000007;
*/

int main(int argc, char **argv) {
    // env setup
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    // cout << fixed << setprecision(12);

    int n, c;
    cin >> n >> c;
    int sum = c;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        int x = (s[0]-'0') * 60 + (s[2]-'0') * 10 + (s[3]-'0');
        sum += x - c;
    }

    int secs = sum % 60;
    int mins = (sum / 60) % 60;
    int hours = sum / 3600;

    auto num = [&](int v) {
        string s = "00";
        s[0] += v / 10;
        s[1] += v % 10;
        return s;
    };
    cout << num(hours) << ":" << num(mins) << ":" << num(secs) << endl;

    return 0;
}