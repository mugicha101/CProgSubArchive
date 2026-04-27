#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace std::chrono_literals;

// using namespace __gnu_pbds;
// template <class T>
// using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <class T>
// using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define MOD 1000000007

typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
pair<T,U> operator+(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
pair<T,U> operator-(const pair<T,U> & l,const pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) {
    os << "[";
    for (size_t i = 0; i < v.size(); ++i) { 
        os << v[i]; 
        if (i != v.size() - 1) 
            os << ", "; 
    }
    os << "]";
    return os;
}

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
#define pause() this_thread::sleep_for(10ms)

typedef complex<double> cnum;

// get nth root of unity to the pth power
cnum inline getW(int n, double p) {
    return pow(cnum{M_E, 0}, cnum{0, M_PI * 2.0 * p / n});
}

// precondition: n power of 2
vector<cnum> fftHelper(const vector<cnum>& xArr, cnum w, int offset, int spacing) {
    // setup
    int n = (int)xArr.size() >> spacing;
    int h = n >> 1;
    int d = 1 << spacing;

    // base case
    if (n == 1)
        return {xArr[offset]};

    // recurse
    vector<cnum> yEven = fftHelper(xArr, w * w, offset, spacing + 1);
    vector<cnum> yOdd = fftHelper(xArr, w * w, offset + d, spacing + 1);

    // merge
    vector<cnum> yArr(n);
    cnum wk = 1;
    for (int k = 0; k < h; ++k) {
        yArr[k] = yEven[k] + wk * yOdd[k];
        yArr[k + h] = yEven[k] - wk * yOdd[k];
        wk *= w;
    }
    return yArr;
}

// precondition: n power of 2
vector<cnum> fft(const vector<cnum>& xArr) {
    int n = (int)xArr.size();
    if (n ^ (n & (-n)))
        throw exception();
    return fftHelper(xArr, getW((int)xArr.size(), -1), 0, 0);
}

// precondition: n power of 2
vector<cnum> ifft(const vector<cnum>& yArr) {
    int n = (int)yArr.size();
    if (n ^ (n & (-n)))
        throw exception();
    vector<cnum> output = fftHelper(yArr, getW((int)yArr.size(), 1), 0, 0);
    cnum divN = cnum{1.0/yArr.size(), 0};
    for (cnum& y : output)
        y *= divN;
    return output;
}

// ensure arr length is power of 2 (not needed if fft package used)
void pad(vector<cnum>& arr) {
    int s = (int)arr.size();
    while (s ^ (s & (-s))) {
        arr.emplace_back(0,0);
        ++s;
    }
}

// multiplies polynomials represented by the coefficient arrays A and B
// returns a coefficient array
vector<cnum> multiplyPolynomials(vector<cnum> A, vector<cnum> B) {
    // pad length of A and B to account for larger output C
    size_t outputSize = A.size() + B.size();
    while (A.size() < outputSize)
        A.emplace_back(0);
    while (B.size() < outputSize)
        B.emplace_back(0);

    // apply dft (O(nlgn))
    pad(A);
    pad(B);
    vector<cnum> dftA = fft(A);
    vector<cnum> dftB = fft(B);

    // point-wise multiply to get dft of A * B (O(n))
    vector<cnum> dftC;
    dftC.reserve(dftA.size());
    for (int i = 0; i < (int)dftA.size(); ++i)
        dftC.push_back(dftA[i] * dftB[i]);

    // inverse dft
    vector<cnum> C = ifft(dftC);

    // trim until matches outputSize
    while (C.size() > outputSize)
        C.pop_back();
    return C;
}

// integer version
template<typename T>
vector<T> multiplyPolynomials(const vector<T> &A, const vector<T> &B) {
    vector<cnum> cA(A.size());
    vector<cnum> cB(B.size());
    for (int i = 0; i < (int)A.size(); ++i) cA[i] = (cnum)A[i];
    for (int i = 0; i < (int)A.size(); ++i) cB[i] = (cnum)B[i];
    vector<cnum> cC = multiplyPolynomials(cA, cB);
    vector<T> C(cC.size());
    for (int i = 0; i < (int)cC.size(); ++i) C[i] = (T)round(cC[i].real());
    return C;
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int tc; cin >> tc;
    vector<int> ns(tc); vcin(ns);

    // given odd n where 5 < n <= 10^6
    // find number of ways to express as sum of odd prime + even semiprime (prime * prime)
    // let P = set of all odd primes <= n
    // let S = set of all even semiprimes
    // let p(x) = sum(x^p for p in P) and s(x) = sum(x^s for s in S)
    // the coefficient of x^n in p(x) * s(x) is the number of ways to express p in P + s in S = n
    // O(nlgn) poly mult: iFFT(FFT(p) * FFT(s))

    // cache results up to max n
    ll N = *max_element(ns.begin(), ns.end());
    vector<int> prime(N+1,1);
    vector<int> sprime(N+1);
    vector<int> primes;

    // sieve to get primes
    prime[0] = 0;
    prime[1] = 0;
    for (int x = 2; x <= N; ++x) {
        if (!prime[x]) continue;
        primes.push_back(x);
        for (int y = x+x; y <= N; y += x) prime[y] = 0;
    }

    // multiply primes by itself to get S
    // this should run in time if cached even if O(n^2/ln^2(n))
    for (int i = 0; i < (int)primes.size(); ++i) {
        ll a = primes[i];
        ll r;
        for (int j = i; j < (int)primes.size() && (r = a * primes[j]) <= N; ++j) {
            sprime[r] = 1;
        }
    }
    
    // remove 2 from primes to get odd primes
    prime[2] = 0;
    
    // cartesian sum of P and S to get result
    vector<int> res = multiplyPolynomials(prime, sprime);
    res.resize(N+1,0);

    for (int n : ns) cout << res[n] << "\n";
}
