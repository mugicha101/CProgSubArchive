/*
Platinum 3
27571 - Color Tubes
meta: {"problemId": 27571, "titleKo": "Color Tubes", "titles": [{"language": "en", "languageDisplayName": "en", "title": "Color Tubes", "isOriginal": true}], "isSolvable": true, "isPartial": false, "acceptedUserCount": 21, "level": 18, "votedUserCount": 4, "sprout": false, "givesNoRating": false, "isLevelLocked": false, "averageTries": 2.5237998962402344, "official": true, "tags": [{"key": "implementation", "isMeta": false, "bojTagId": 102, "problemCount": 6833, "displayNames": [{"language": "ko", "name": "구현", "short": "구현"}, {"language": "en", "name": "implementation", "short": "impl"}, {"language": "ja", "name": "実装", "short": "impl"}], "aliases": []}, {"key": "constructive", "isMeta": false, "bojTagId": 128, "problemCount": 1581, "displayNames": [{"language": "ko", "name": "해 구성하기", "short": "해 구성하기"}, {"language": "en", "name": "constructive", "short": "constructive"}, {"language": "ja", "name": "構成的", "short": "構成的"}], "aliases": [{"alias": "constructive"}, {"alias": "컨스트럭티브"}, {"alias": "구성적"}]}, {"key": "case_work", "isMeta": false, "bojTagId": 137, "problemCount": 1205, "displayNames": [{"language": "ko", "name": "많은 조건 분기", "short": "많은 조건 분기"}, {"language": "en", "name": "case work", "short": "case work"}, {"language": "ja", "name": "ケースワーク", "short": "ケースワーク"}], "aliases": [{"alias": "케이스"}, {"alias": "케이스워크"}, {"alias": "케이스 워크"}]}], "metadata": {}}
*/

#include <unordered_set>
#include <bits/stdc++.h>

typedef long long ll;
#define INPUT false

using namespace std;

#define endl "\n"

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    int n;
    cin >> n;
    vector<vector<int>> tubes(n+1);
    vector<vector<int>> topChains(n+1, vector<int>());
    vector<set<int>> sizeToTube(4);
    auto addBall = [&](int tube, int ball) {
        if (tubes[tube].size() == 3)
            throw exception();
        sizeToTube[tubes[tube].size()].erase(tube);
        topChains[tube].push_back(tubes[tube].empty() || tubes[tube].back() != ball? 1 : topChains[tube].back()+1);
        tubes[tube].push_back(ball);
        sizeToTube[tubes[tube].size()].insert(tube);
    };
    auto removeBall = [&](int tube) {
        sizeToTube[tubes[tube].size()].erase(tube);
        tubes[tube].pop_back();
        topChains[tube].pop_back();
        sizeToTube[tubes[tube].size()].insert(tube);
    };
    for (int i = 0; i <= n; ++i) {
        tubes[i].reserve(3);
        sizeToTube[0].insert(i);
        for (int j = 0; j < 3; ++j) {
            int ball;
            cin >> ball;
            if (ball)
                addBall(i, ball-1);
        }
    }
    
    vector<pair<int,int>> moves;
    auto doMove = [&](int src, int dst) {
            if (src == dst)
                return;
            // do move
            addBall(dst, tubes[src].back());
            removeBall(src);

            // undo move if reverse of last move
            if (!moves.empty() && moves.back().first == dst && moves.back().second == src)
                moves.pop_back();
            else
                moves.emplace_back(src, dst);
        // cout << "MOVE: " << src << "->" << dst << endl;
    };

    auto display = [&]() {
        for (int i = 0; i <= n; ++i) {
            cout << i << " -> ";
            for (int ball : tubes[i])
                cout << ball << " ";
            cout << endl;
        }
    };
    while (true) {
        // empty emptiest tube
        int bufferTube = 0;
        int s = 0;
        while (sizeToTube[s].empty())
            ++s;
        bufferTube = *sizeToTube[s].begin();
        for (int i = 0; i <= n; ++i) {
            if (tubes[i].size() < tubes[bufferTube].size())
                bufferTube = i;
        }
        int i = 0;
        while (!tubes[bufferTube].empty()) {
            while (i == bufferTube || tubes[i].size() == 3)
                ++i;
            doMove(bufferTube, i);
        }
        // cout << "smallest size: " << tubes[bufferTube].size() << endl;

        // move longest non-3 topchain into empty tube (if all tubes are 3-chains or 0-chains, end)
        int t = -1;
        vector<int> ones;
        for (int i = 0; i <= n; ++i) {
            if (topChains[i].empty() || topChains[i].back() == 3)
                continue;
            t = i;
            if (topChains[i].back() == 2)
                break;
            ones.push_back(i);
        }
        if (t == -1)
            break;

        // if longest topchain is 1, choose ball which does not have the other 2 at bottom
        if (topChains[t].back() == 1) {
            vector<int> bottomCount(n, 0);
            for (int i = 0; i <= n; ++i) {
                if (!tubes[i].empty())
                    ++bottomCount[tubes[i][0]];
            }
            t = -1;
            for (int o : ones) {
                if (bottomCount[o] == 2)
                    continue;
                t = o;
                break;
            }
            if (t == -1)
                throw exception();
        }
        for (int i = topChains[t].back(); i > 0; --i)
            doMove(t, bufferTube);
        int targetBall = tubes[bufferTube].back();
        // cout << "bt=" << bufferTube << " tb=" << targetBall << endl;
        // display();

        // move target balls out of tubes from top layer (guaranteed possible)
        for (int i = 0; tubes[bufferTube].size() < 3 && i <=n; ++i) {
            if (i == bufferTube || tubes[i].empty() || tubes[i].back() != targetBall)
                continue;
            doMove(i, bufferTube);
        }

        // move target balls out of tubes from middle layer (guaranteed possible, have at least 1 empty space to use)
        auto getEmptiestTube = [&]() {
            sizeToTube[tubes[bufferTube].size()].erase(bufferTube);
            int s = 0;
            while (s <= 3 && sizeToTube[s].empty())
                ++s;
            int t = *sizeToTube[s].begin();
            sizeToTube[tubes[bufferTube].size()].insert(bufferTube);
            return t;
        };
        for (int i = 0; tubes[bufferTube].size() < 3 && i <= n; ++i) {
            if (i == bufferTube || tubes[i].size() <= 1)
                continue;
            if (tubes[i][tubes[i].size()-2] != targetBall)
                continue;
            int t = getEmptiestTube();
            doMove(i, t);
            doMove(i, bufferTube);
        }

        // move target balls out of tubes from bottom layer (only possible if only 0 or 1 in bottom layer (handled in above step))
        for (int i = 0; tubes[bufferTube].size() < 3 && i <= n; ++i) {
            if (i == bufferTube || tubes[i].size() <= 2)
                continue;
            if (tubes[i][0] != targetBall)
                continue;
            int t = getEmptiestTube();
            doMove(i, t);
            t = getEmptiestTube();
            doMove(i, t);
            doMove(i, bufferTube);
        }
    }
    // display();
    if ((int)moves.size() > n * 20)
        throw exception();
    for (int i = 0; i <= n; ++i) {
        if (!topChains[i].empty() && topChains[i].back() != 3)
            throw exception();
    }
    cout << (int)moves.size() << endl;
    for (auto& m : moves)
        cout << m.first+1 << " " << m.second+1 << endl;
}