// 2023-03-03 03:38:05 
#include <unordered_set>
#include <bits/stdc++.h>

typedef long long ll;
#define INPUT false

using namespace std;

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(0);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    int n;
    cin >> n;
    vector<vector<int>> output;
    int x;
    while (n--) {
        cin >> x;
        // binary search for output to append to
        int l = 0; // max in bounds
        int r = output.size(); // min in bounds
        while (l < r) {
            int m = ((l + r) >> 1);
            if (output[m].back() >= x)
                l = m+1;
            else
                r = m;
        }
        if (l == output.size())
            output.push_back(vector<int>(1,x));
        else
            output[l].push_back(x);
    }
    cout << output.size() << endl;
    for (int i = 0; i < output.size(); ++i) {
        for (int x : output[i])
            cout << x << " ";
        cout << endl;
    }
}
