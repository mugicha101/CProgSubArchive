//  2024-01-24 22:04:51 
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
    pair<int,int> main_cycle[10];
    pair<int,int> machine_cycles[10];
    int machine_offsets[10];
    for (auto& x : main_cycle)
        cin >> x.first >> x.second;
    for (int machine = 0; machine < 10; ++machine) {
        auto& [cycle_length, work_time] = machine_cycles[machine];
        cin >> work_time >> cycle_length >> machine_offsets[machine];
        cycle_length += work_time;
    }
    int time = 0;
    for (int i = 0; i < 30; ++i) {
        int machine = i % 10;
        int free_time = time;
        int resume_time;
        auto [cycle_length, work_time] = machine_cycles[machine];
        int& offset = machine_offsets[machine];
        if (offset > time) resume_time = offset;
        else {
            int cycle_pos = (time - offset) % cycle_length;
            resume_time = time - cycle_pos + cycle_length; // next cycle start
            if (cycle_pos < work_time)
                free_time += work_time - cycle_pos;
        }
        time = free_time + main_cycle[machine].first;
        if (time > resume_time) offset = time;
        time += main_cycle[machine].second;
    }
    cout << time - main_cycle[9].second << endl;
}
