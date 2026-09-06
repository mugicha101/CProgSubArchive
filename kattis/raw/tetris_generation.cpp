// 2023-02-09 21:11:16 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;

int valid(string& seq) {
	// try all 7 start bag states
	auto pieceId = [](char c) {
		switch (c) {
			case 'J':
				return 0;
			case 'L':
				return 1;
			case 'S':
				return 2;
			case 'Z':
				return 3;
			case 'I':
				return 4;
			case 'O':
				return 5;
			case 'T':
				return 6;
			default:
				return -1;
		}
	};
	for (char& c : seq)
		c = pieceId(c);
	int n = seq.size();
	vector<vector<bool>> inBag(7, vector<bool>(7, false));
	vector<bool> valid(7, true);
	int k = 0;
	int validCount = 7;
	for (int i = 0; validCount > 0 && i < n; ++i) {
		if (valid[k]) {
			for (int j = 0; j < 7; ++j)
				inBag[k][j] = false;
		}
		for (int j = 0; j < 7; ++j) {
			if (!valid[j])
				continue;
			if (inBag[j][seq[i]]) {
				valid[j] = false;
				--validCount;
			} else
				inBag[j][seq[i]] = true;
		}
		k = k == 6? 0 : k + 1;
	}
	return (int)(validCount > 0);
}

int main(int argc, char **argv) {
    // test case input
    ios_base::sync_with_stdio(false);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif
    
    // input
    int testCases;
    cin >> testCases;
    cin.ignore(100,'\n');
    string seq;
    for (; testCases > 0; --testCases) {
		getline(cin, seq);
		// printf("%s\n", seq.c_str());
		printf("%d\n", valid(seq));
	}
}
