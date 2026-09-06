// 2025-11-08 21:58:27 
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

#define endl "\n"

struct Racer {
    long long time;
    long long speed;
    long long id;

    Racer() : time(0), speed(0), id(0) {}
    Racer(long long time, long long speed, long long id) : time(time), speed(speed), id(id) {}

    bool operator < (const Racer& other) const {
        if (time == other.time) return speed < other.speed;
        else return time < other.time;
    }
};

long long n, m, k;
long long e, c;

vector<vector<long long>> adj_list;
vector<set<Racer>> racers;
unordered_set<int> checkpoints;
vector<long long> results;

void dfs(long long node, long long parent, long long last_checkpoint, long long depth) {
    bool is_checkpoint = checkpoints.count(node);

    for (long long& neighbor : adj_list[node]) {
        if (neighbor == parent) continue;
        if (is_checkpoint) dfs(neighbor, node, node, 1);
        else dfs(neighbor, node, last_checkpoint, depth + 1);
    }

    if (node == e) {
        for (auto& racer : racers[e]) results[racer.id] = racer.time;
    } else if (last_checkpoint == e) {
        for (auto& racer : racers[node]) {
            long long racer_id = racer.id;
            long long racer_speed = racer.speed;
            
            long long racer_time = racer.time;
            racer_time += depth * racer_speed;

            racers[e].emplace(racer_time, racer.speed, racer.id);
        }
    } else {
        for (auto& racer : racers[node]) {
            long long racer_id = racer.id;
            long long racer_speed = racer.speed;
            
            long long racer_time = racer.time;
            racer_time += depth * racer_speed;

            Racer new_racer = Racer(racer_time, racer_speed, racer_id);

            if (racers[last_checkpoint].size() < k) racers[last_checkpoint].insert(new_racer);
            else {
                Racer last_racer = *prev(racers[last_checkpoint].end());

                if (new_racer < last_racer) {
                    racers[last_checkpoint].erase(prev(racers[last_checkpoint].end()));
                    racers[last_checkpoint].insert(new_racer);
                    results[last_racer.id] = -1;
                } else results[racer.id] = -1;
            }
        }
    }
}

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cout << fixed << setprecision(12);

    cin >> n >> m >> k;
    adj_list.resize(n + 1);

    for (int i = 1; i < n; i++) {
        long long a, b;
        cin >> a >> b;

        adj_list[a].emplace_back(b);
        adj_list[b].emplace_back(a);
    }

    racers.resize(n + 1);
    results.resize(m + 1);

    for (int i = 1; i <= m; i++) {
        long long p, t;
        cin >> p >> t;

        racers[p].emplace(0, t, i);
    }

    cin >> e;
    cin >> c;

    for (int i = 1; i <= c; i++) {
        long long checkpoint;
        cin >> checkpoint;
        checkpoints.emplace(checkpoint);
    }

    checkpoints.emplace(e);
    dfs(e, 0, 0, 0);

    for (int i = 1; i <= m; i++) {
        cout << results[i] << "\n";
    }

    return 0;
}
