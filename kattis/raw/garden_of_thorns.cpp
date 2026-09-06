// 2024-02-18 00:47:55 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false
typedef long long ll;
typedef long double ld;

ld integral(ld a, ld b) {
	ld angleA = acos(a);
	ld angleB = acos(b);
	ld ya = sin(angleA);
	ld yb = sin(angleB);

	// area 1 (pizza slice)
	ld area1 = (angleA - angleB) * 0.5;

	// area 2 (bottom triangle)
	ld area2 = b * sqrt(1-b*b) * 0.5;
	
	// area 3 (left triangle)
	ld area3 = a * sqrt(1-a*a) * 0.5;
	
	return area1 + area2 - area3;
}

ld circOverlap(ld left, ld bottom, ld right, ld top) {
	ld hi, vi, area = 0.0;

	auto calc = [](ld w, ld h) {
		ld a = h < 1 ? cos(asin(h)) : 0;
		ld b = w < 1 ? w : 1.0;
		if (b <= a) return w * h;
		return integral(a, b) + a * h;
	};
	area += calc(right, top);
	area += calc(left, top);
	area += calc(right, bottom);
	area += calc(left, bottom);
	return area;
}

int main(int argc, char **argv) {
	// env setup
	ios_base::sync_with_stdio(false);
	cout << setprecision(12);
	#if INPUT
	freopen("./input.txt","r",stdin);
	#endif
	
	// input
	int n;
	ld r, w, h;
	cin >> n >> r >> w >> h;
	ld invR = 1.0 / r;
	w *= invR;
	h *= invR;
	ld invArea = 1.0 / (w * h);
	ld ev = 0.0;
	for (int i = 0; i < n; ++i) {
		ld x, y, v;
		cin >> x >> y >> v;
		x *= invR;
		y *= invR;
		ev += circOverlap(x, y, w-x, h-y) * invArea * v;
	}
	cout << ev << endl;
}
