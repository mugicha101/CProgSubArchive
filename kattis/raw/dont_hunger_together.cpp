// 2024-02-18 00:48:33 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(false);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    int n, k;
    cin >> n >> k;
    vector<ll> food(n);
    vector<ll> rot(n+1);
    for (int i = 0; i < n; ++i) {
        ll f, e;
        cin >> f >> e;
        food[i] += f;
        rot[e] += f;
    }
    rot.pop_back();
    ld upper = INFINITY;
    ld a = 0;
    for (int i = 0; i < n; ++i) {
        a += food[i] - rot[i];
        upper = min(upper, a);
    }
    ld lower = 0;
    ld prec = 5e-10;
    bool lower_zero = true;
    while (abs(upper - lower) > prec) {
        ld x = lower * 0.5 + upper * 0.5;
        ld eaten = 0; // eaten without rot
        ld stock = 0;
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            if (rot[i] > eaten) {
                stock -= rot[i] - eaten;
                eaten = 0;
            } else {
                eaten -= rot[i];
            }
            stock += food[i] - x;
            eaten += x;
            if (stock < 0) {
                valid = false;
                break;
            }
        }
        if (valid) {
            lower_zero = false;
            lower = x;
        } else {
            upper = x;
        }
    }
    cout << setprecision(10);
    cout << (lower_zero ? -1 : (double)(lower / k)) << endl;
    return 0;
}
