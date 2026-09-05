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

inline uint8_t rep(bool b) {
    return (uint8_t)b << 1;
}

// S := E1 E1 END
// E1 := E2 (OR E2)*
// E2 := E3 (XOR E3)*
// E3 := E4 (AND E4)*
// E4 := NOT* E5
// E5 := V | LP E1 RP

string expr;
size_t i;
struct V {
    int id = -1;
    void parse() {
        id = expr[i++] - (int)'a';
    }
    bool eval(bitset<26> x) const {
        assert(id >= 0 && id < 26);
        return x[id];
    }
};
struct E1;
struct E5 {
    E1 *e = nullptr;
    V *v = nullptr;
    ~E5();
    void parse();
    bool eval(bitset<26> x) const;
};
struct E4 {
    bool f = false;
    E5 *a = nullptr;

    ~E4() { delete a; }

    void parse() {
        while (expr[i] == '~') {
            f = !f;
            ++i;
        }
        a = new E5();
        a->parse();
    }

    bool eval(bitset<26> x) const {
        assert(a);
        return f ^ a->eval(x);
    }
};
struct E3 {
    vector<E4 *> e;

    ~E3() {
        for (E4 *t : e) delete t;
    }

    void parse() {
        e.push_back(new E4());
        e.back()->parse();
        while (expr[i] == '&') {
            ++i;
            e.push_back(new E4());
            e.back()->parse();
        }
    }

    bool eval(bitset<26> x) const {
        for (E4 *t : e) if (!t->eval(x)) return false;
        return true;
    }
};
struct E2 {
    vector<E3 *> e;

    ~E2() {
        for (E3 *t : e) delete t;
    }

    void parse() {
        e.push_back(new E3());
        e.back()->parse();
        while (expr[i] == '^') {
            ++i;
            e.push_back(new E3());
            e.back()->parse();
        }
    }

    bool eval(bitset<26> x) const {
        bool res = false;
        for (E3 *t : e) res = res ^ t->eval(x);
        return res;
    }
};
struct E1 {
    vector<E2 *> e;

    ~E1() {
        for (E2 *t : e) delete t;
    }

    void parse() {
        e.push_back(new E2());
        e.back()->parse();
        while (expr[i] == '|') {
            ++i;
            e.push_back(new E2());
            e.back()->parse();
        }
    }

    bool eval(bitset<26> x) const {
        for (E2 *t : e) if (t->eval(x)) return true;
        return false;
    }
};
void E5::parse() {
    if (expr[i] == '(') {
        ++i;
        e = new E1();
        e->parse();
        assert(expr[i++] == ')');
    } else {
        v = new V();
        v->parse();
    }
}
bool E5::eval(bitset<26> x) const {
    assert((bool)e ^ (bool)v);
    return e ? e->eval(x) : v->eval(x);
}
E5::~E5() {
    if (e) delete e;
    if (v) delete v;
}
struct S {
    E1 *a = nullptr, *b = nullptr;
    vector<int> vars;

    ~S() {
        delete a; delete b;
    }

    void parse() {
        // find which vars are used (at most 10)
        bitset<26> used;
        for (char c : expr) if (c >= 'a' && c <= 'z') used[c-'a'] = true;
        for (int c = 0; c < 26; ++c) if (used[c]) vars.push_back(c);
        a = new E1();
        b = new E1();
        a->parse();
        b->parse();
        assert(expr[i] == ';');
    }

    bool same() const {
        uint32_t cap = 1 << vars.size();
        for (uint32_t v = 0; v < cap; ++v) {
            bitset<26> x;
            for (int j = 0; j < (int)vars.size(); ++j) {
                x[vars[j]] = (v >> j) & 1;
            }
            if (a->eval(x) != b->eval(x)) return false;
        }
        return true;
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int n; cin >> n;
    cin.ignore(100, '\n');
    for (int ds = 0; ds < n; ++ds) {
        getline(cin, expr);
        int j = 0;
        for (int i = 0; i < (int)expr.size(); ++i) {
            if (expr[i] == ' ') continue;
            expr[j++] = expr[i];
        }
        expr.resize(j);
        expr += ';';
        i = 0;
        S s;
        s.parse();
        cout << "Data set " << (ds+1) << ": " << (s.same() ? "Equivalent" : "Different") << "\n";
    }
}
