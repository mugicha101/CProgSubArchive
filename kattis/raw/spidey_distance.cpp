// 2023-02-06 17:02:33 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;

ll gcd(ll a, ll b) {
	if (a < b)
		swap(a, b);
	while (b != 0) {
		ll r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main(int argc, char **argv) {
	// test case input
	// ios_base::sync_with_stdio(false);
	#if INPUT
	freopen("./input.txt","r",stdin);
	#endif
	
	// input
	int manRange, spiRange;
	cin >> manRange >> spiRange;
	ll man = min(manRange, spiRange);
	ll spi = spiRange;
	for (int c = 1; c <= spiRange; ++c) {
		int spiH = min((spiRange - c) << 1, ((spiRange << 1) - c) >> 1);
		spi += spiH;
		man += min(max(manRange - c, 0), spiH);
	}
	man <<= 2;
	spi <<= 2;
	++man;
	++spi;
	ll g = gcd(spi, man);
	man /= g;
	spi /= g;
	if (spi == 1)
		cout << "1\n";
	else
		cout << man << "/" << spi << "\n";
	return 0;
}
