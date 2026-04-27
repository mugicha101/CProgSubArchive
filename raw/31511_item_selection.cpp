#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);

    int numItems, numPageItems, startPage, numPre, numWant;
    cin >> numItems >> numPageItems >> startPage >> numPre >> numWant;
    --startPage;
    int numPages = (numItems + numPageItems - 1) / numPageItems;

    vector<bool> presel(numItems);
    vector<bool> want(numItems);
    for (int i = 0; i < numPre; ++i) {
        int x; cin >> x; --x;
        presel[x] = true;
    }
    for (int i = 0; i < numWant; ++i) {
        int x; cin >> x; --x;
        want[x] = true;
    }

    int totalOps = 0;
    int firstPage = startPage;
    int lastPage = startPage;
    for (int pageNum = 0; pageNum < numPages; ++pageNum) {
        int start = pageNum * numPageItems;
        int end = min((pageNum + 1) * numPageItems, numItems);
        int numWanted = 0;
        int numDiff = 0;
        for (int i = start; i < end; ++i) {
            numDiff += presel[i] ^ want[i];
            numWanted += want[i];
        }
        int pageOps = min(numDiff, min(numWanted + 1, (end - start) - numWanted + 1));
        if (pageOps) {
            firstPage = min(firstPage, pageNum);
            lastPage = max(lastPage, pageNum);
        }
        totalOps += pageOps;
    }
    int leftDist = startPage - firstPage;
    int rightDist = lastPage - startPage;
    totalOps += min(leftDist * 2 + rightDist, rightDist * 2 + leftDist);
    cout << totalOps << "\n";
}
