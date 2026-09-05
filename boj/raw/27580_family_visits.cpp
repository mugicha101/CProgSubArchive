#include <unordered_set>
#include <bits/stdc++.h>

typedef long long ll;
#define INPUT false

using namespace std;

int handleVisit(vector<int>& mess, vector<int>& clean, vector<int>& prefixMess, vector<int>& prefixClean, int firstDay, int visitDay) {
    vector<int> heap; // possible remaining cleans
    int messSum = 0;
    for (int i = visitDay; i >= firstDay; --i) {
        messSum += mess[i];
        heap.push_back(clean[i]);
        push_heap(heap.begin(), heap.end());
        while (!heap.empty() && messSum > 0) {
            pop_heap(heap.begin(), heap.end());
            messSum -= heap.back();
            heap.pop_back();
        }
        if (messSum > 0) {
            return -1;
        }
    }
    return visitDay - firstDay + 1 - heap.size();
}

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    int days, visits;
    cin >> days >> visits;
    vector<int> clean(days);
    vector<int> mess(days);
    vector<int> prefixClean(1,0);
    vector<int> prefixMess(1,0);
    vector<int> visitDays(visits, 0);
    prefixClean.reserve(days + 1);
    prefixMess.reserve(days + 1);
    for (int i = 0; i < days; ++i) {
        cin >> mess[i] >> clean[i];
        prefixMess.push_back(prefixMess.back() + mess[i]);
        prefixClean.push_back(prefixClean.back() + clean[i]);
    }
    for (int i = 0; i < visits; ++i) {
        cin >> visitDays[i];
        --visitDays[i];
    }
    int totalCleans = 0;
    int firstDay = 0;
    for (int visitDay : visitDays) {
        int cleans = handleVisit(mess, clean, prefixMess, prefixClean, firstDay, visitDay);
        if (cleans == -1) {
            cout << -1 << "\n";
            return 0;
        }
        totalCleans += cleans;
        firstDay = visitDay + 1;
    }
    cout << totalCleans << "\n";
}