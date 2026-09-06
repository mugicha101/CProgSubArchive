// 2024-01-23 05:35:21 
#include <bits/stdc++.h>

using namespace std;
#define INPUT false

typedef long long ll;
typedef long double ld;

#define ssort(x) sort(x.begin(), x.end())
#define flip(x) reverse(x.begin(), x.end())
#define iseq(x) iota(x.begin(), x.end(), 0)

#define forn(i,n) for (int i = 0; i < n; ++i)
#define rforn(i,n) for (int i = n-1; i >= 0; --i)
#define fora(a) for(auto x : a)
#define forr(a) for(auto& x : a)

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
#define len(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()
#define getx(a) a.first
#define gety(a) a.second
#define MOD 1000000007
#define INF 1e9
#define EPS 1e-15

bool prime(ll a) { if (a==1) return 0; ll cap = sqrt(a); for (int i=2;i<=cap;++i) if (a%i==0) return 0; return 1; }

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const { return hash<T1>{}(p.first) ^ hash<T2>{}(p.second); }
};

typedef vector<vector<int>> AdjList;

typedef pair<float,float> vec;
typedef pair<vec,vec> edge;

const vec zeroVec = make_pair(-1,0);

pair<vec,vec> triCalc(edge& base_edge, float& left, float& right) {
    auto& [p1, p2] = base_edge;
    float bx = p2.first - p1.first, by = p2.second - p1.second, base = sqrt(bx * bx + by * by);
    if (left + right <= base || abs(left - right) >= base) return make_pair(zeroVec, zeroVec);
    auto rotate = [](vec v, ld a) {
        float cosV = cos(a);
        float sinV = sin(a);
        return make_pair(cosV * v.first - sinV * v.second, sinV * v.first + cosV * v.second);
    };
    float px = (base * base + left * left - right * right) / (base * 2.0);
    float py = sqrt(left * left - px * px);
    if (py == 0) return make_pair(zeroVec, zeroVec);
    float rot = atan2(by, bx);
    vec q1 = rotate(make_pair(px, py), rot);
    vec q2 = rotate(make_pair(px, -py), rot);
    return make_pair(make_pair(p1.first + q1.first, p1.second + q1.second), make_pair(p1.first + q2.first, p1.second + q2.second));

    /*
    float invLeft = (float)1.0 / left, invBase = (float)1.0 / base, base_angle = atan2(by, bx), angle = acos((base * (float)0.5 * invLeft + left * (float)0.5 * invBase - right * right * (float)0.5 * invLeft * invBase));
    return make_pair(
        make_pair(base_edge.first.first + left * cos(angle + base_angle), base_edge.first.second + left * sin(angle + base_angle)),
        make_pair(base_edge.first.first + left * cos(-angle + base_angle), base_edge.first.second + left * sin(-angle + base_angle))
    );
    */
}

void dfs(vector<float>& nums, int visited, edge base_edge, float remaining, float& furthest) {
    int n = nums.size();
    float base_reach = max(base_edge.first.first, base_edge.second.first);
    // edge flipped_edge = make_pair(base_edge.second, base_edge.first);
    if (base_reach + remaining * 0.5 <= furthest) return;
    for (int i = 0; i < n; ++i) {
        if (visited & (1 << i)) continue;
        if (base_reach + remaining * 0.5 <= furthest) return;
        for (int j = i+1; j < n; ++j) {
            if (visited & (1 << j)) continue;
            if (base_reach + remaining * 0.5 <= furthest) return;
            float sum = nums[i] + nums[j];
            int m = visited | (1 << i) | (1 << j);
            auto calc = [&](float left, float right) {
                auto&& [a1, a2] = triCalc(base_edge, left, right);
                auto handle = [&](vec& apex) {
                    if (apex.first <= 0) return;
                    furthest = max(furthest, apex.first);
                    dfs(nums, m, make_pair(base_edge.first, apex), remaining - sum, furthest);
                    dfs(nums, m, make_pair(base_edge.second, apex), remaining - sum, furthest);
                };
                handle(a1);
                handle(a2);
            };
            calc(nums[i], nums[j]);
            calc(nums[j], nums[i]);
        }
    }
}

int main(int argc, char **argv) {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    #if INPUT
    freopen("./input.txt","r",stdin);
    #endif

    int n;
    cin >> n;
    vector<float> nums(n);
    float remaining = 0.0;
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
        remaining += nums[i];
    }
    sort(nums.begin(), nums.end());
    
    // brute force backtracking = 23224320 ~= 2*10^8 states, can run within 5 seconds runtime
    // keep track of previous triangle and add to it
    float furthest = 0.0;
    // first choose first triangle
    for (int base = 0; base < n; ++base) {
        edge base_edge = make_pair(make_pair(0, 0), make_pair(0, -nums[base]));
        dfs(nums, 1 << base, base_edge, remaining, furthest);
    }
    cout << furthest << endl;
}
