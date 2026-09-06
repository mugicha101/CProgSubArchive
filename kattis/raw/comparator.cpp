// 2025-05-09 20:06:46 

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
 
using namespace std;

const int MOD = 1000000007;
 
typedef unsigned int uint;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const ld ROT_HALF = 3.14159265358979323846L;
const ld ROT_FULL = ROT_HALF * 2.L;
const ld ROT_QUARTER = ROT_HALF * 0.5L;

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}
template <typename T,typename U>         
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

const ll INF = LLONG_MAX >> 2;

#define EPS 1e-7
#define all(x) x.begin(), x.end()
#define sz(x) ((int)x.size())
#define each(i, x) for (auto &i : x)
#define vcin(x) for (auto &_e : x) cin >> _e;
#define mp(a,b) make_pair(a,b)
// #define endl "\n"

struct Expr {
    virtual bool sim(bool x, bool y) const = 0;
    virtual ~Expr() {}
    virtual void dump(size_t indent = 0) const = 0;
    string indentStr(size_t indent) const {
        return string(indent, ' ');
    }
};

struct Binop : public Expr {
    Expr *lhs;
    Expr *rhs;
    Binop(Expr *lhs, Expr *rhs) : lhs(lhs), rhs(rhs) {}
    ~Binop() override {
        delete lhs;
        delete rhs;
    }
    void dump(size_t indent) const override {
        cout << indentStr(indent) << name() << endl;
        lhs->dump(indent + 1);
        rhs->dump(indent + 1);
    }
    virtual string name() const = 0;
};

struct X : public Expr {
    bool sim(bool x, bool) const override final {
        return x;
    }

    void dump(size_t indent) const override {
        cout << indentStr(indent) << "X" << endl;
    }
};

struct Y : public Expr {
    bool sim(bool, bool y) const override final {
        return y;
    }

    void dump(size_t indent) const override {
        cout << indentStr(indent) << "Y" << endl;
    }
};

struct Literal : public Expr {
    bool v;
    Literal(bool v) : v(v) {}
    bool sim(bool, bool) const override final {
        return v;
    }
    void dump(size_t indent) const override {
        cout << indentStr(indent) << "Literal(" << v << ")" << endl;
    }
};

struct Neg : public Expr {
    Expr *a;
    Neg(Expr *a) : a(a) {}
    ~Neg() {
        delete a;
    }
    bool sim(bool x, bool y) const override final {
        return !a->sim(x, y);
    }
    void dump(size_t indent) const override {
        cout << indentStr(indent) << "Neg" << endl;
        a->dump(indent + 1);
    }
};

struct Equals : public Binop {
    Equals(Expr *lhs, Expr *rhs) : Binop(lhs, rhs) {}
    bool sim(bool x, bool y) const override final {
        return lhs->sim(x, y) == rhs->sim(x, y);
    }
    string name() const override {
        return "Equals";
    }
};

struct And : public Binop {
    And(Expr *lhs, Expr *rhs) : Binop(lhs, rhs) {}
    bool sim(bool x, bool y) const override final {
        return lhs->sim(x, y) && rhs->sim(x, y);
    }
    string name() const override {
        return "And";
    }
};

struct Or : public Binop {
    Or(Expr *lhs, Expr *rhs) : Binop(lhs, rhs) {}
    bool sim(bool x, bool y) const override final {
        return lhs->sim(x, y) || rhs->sim(x, y);
    }
    string name() const override {
        return "Or";
    }
};

struct Xor : public Binop {
    Xor(Expr *lhs, Expr *rhs) : Binop(lhs, rhs) {}
    bool sim(bool x, bool y) const override final {
        return lhs->sim(x, y) ^ rhs->sim(x, y);
    }
    string name() const override {
        return "Xor";
    }
};

struct TruthTable {
    uint8_t v;
    TruthTable(uint8_t v = 0) : v(v) {}
    TruthTable(bool ff, bool ft, bool tf, bool tt) {
        v = (uint8_t)ff | ((uint8_t)ft << 1) | ((uint8_t)tf << 2) | ((uint8_t)tt << 3);
    }

    void update(bool a, bool b, bool r) {
        uint8_t m = 1 << (((uint8_t)b << 1) | (uint8_t)a);
        v = v ^ (v & m) ^ (r ? m : 0);
    }

    TruthTable operator&(TruthTable o) const {
        return TruthTable(v & o.v);
    }

    bool res(bool a, bool b) const {
        return (v >> (((uint8_t)b << 1) | (uint8_t)a)) & 1;
    }

    TruthTable operator~() const {
        return TruthTable(~v & 0b1111);
    }
};

struct FuncLine {
    uint8_t a;
    uint8_t b;
    bool r;
    TruthTable tt; // caches results of expr so only need to call expr->sim 4 times ever
    FuncLine(uint8_t a, uint8_t b, const Expr *expr, bool r) : a(a-1), b(b-1), r(r), tt(expr->sim(0, 0), expr->sim(1, 0), expr->sim(0, 1), expr->sim(1, 1)) {
        assert(a >= 1 && a <= 10);
        assert(b >= 1 && b <= 10);
    }

    // returns true iff expr returns true
    inline bool returns(uint16_t x, uint16_t y) const {
        return tt.res((x >> a) & 1u, (y >> b) & 1u);
    }
};

struct Func {
    vector<FuncLine *> lines;
    bool elseRet;
    Func(vector<FuncLine *> &&lines, bool elseRet) : lines(move(lines)), elseRet(elseRet) {}
    ~Func() {
        for (FuncLine *l : lines)
            delete l;
        lines.clear();
    }

    bool sim(uint16_t x, uint16_t y) const {
        for (const FuncLine *l : lines) {
            if (l->returns(x, y)) return l->r;
        }
        return elseRet;
    }
};

// GRAMMAR
// Func ::= Line* int "\n"
// Line ::= int int E0 int "\n"
// E0 ::= E1
// E0 ::= E0 "^" E1         Xor
// E1 ::= E2
// E1 ::= E1 "|" E2         Or
// E2 ::= E3
// E2 ::= E2 "&" E3         And
// E3 ::= E4
// E3 ::= E3 "=" E4         Equals
// E4 ::= E5
// E4 ::= "!" E4            Neg
// E5 ::= "(" E0 ")"
// E5 ::= "x" | "y" | "0" | "1"

// to parse Ei ::= Ei op E(i-1), just need to try E(i-1) then check for op
// Ei in the RHS is only for left associativity in the formal grammar

struct Parser {
    string s;
    size_t next = 0;

    Parser(string &s) : s(s) {
        skipWhitespace();
    }

    void skipWhitespace() {
        while (peek() == ' ') ++next;
    }

    char peek() const {
        return next < s.size() ? s[next] : ';';
    }

    bool digNext() const {
        char d = peek();
        return d >= '0' && d <= '9';
    }

    bool takeIf(char c) {
        if (peek() != c) return false;

        ++next;
        skipWhitespace();
        return true;
    }

    void take(char c) {
        assert(takeIf(c));
    }

    uint8_t visitInt() {
        assert(digNext());
        uint8_t v = 0;
        while (digNext()) {
            v = v * (uint8_t)10 + (uint8_t)(peek() - '0');
            ++next;
        }
        skipWhitespace();
        return v;
    }

    Func *visitFunc() {
        vector<FuncLine *> lines;
        bool elseRet = 0;
        while (true) {
            uint8_t a = visitInt();
            if (takeIf('\n')) {
                assert(a <= 1);
                elseRet = a;
                break;
            }
            uint8_t b = visitInt();
            Expr *expr = visitE0();
            bool r = peek() == '1';
            take(r ? '1' : '0');
            take('\n');
            FuncLine *line = new FuncLine(a, b, expr, r);
            
            /*
            TruthTable tt = line->tt;
            cout << "x[a] y[b]  res\n";
            cout << "  0    0    " << tt.res(0, 0) << "\n";
            cout << "  0    1    " << tt.res(0, 1) << "\n";
            cout << "  1    0    " << tt.res(1, 0) << "\n";
            cout << "  1    1    " << tt.res(1, 1) << "\n";
            expr->dump();
            */

            delete expr;

            // check if line is redundant
            // we can ignore lines x for which there exists a previous line p where:
            // - x.a, x.b = p.a, p.b
            // - x.tt & ~p.tt = 0 (there are no cases where p.tt returns false and x.tt returns true)
            // we know lines will be at most 1600 since that's the max number of non-redundant lines, thus only 1600 * 1600 <= 3 * 10^6 line comparisons
            bool redundant = false;
            for (size_t i = 0; !redundant && i < lines.size(); ++i) {
                FuncLine &x = *line;
                FuncLine &p = *lines[i];
                redundant = x.a == p.a && x.b == p.b && (x.tt & ~p.tt).v == 0;
            }
            if (!redundant) lines.push_back(line);
        }
        return new Func(move(lines), elseRet);
    }

    Expr *visitE0() {
        Expr *expr = visitE1();
        while (takeIf('^')) {
            Expr *rhs = visitE1();
            expr = new Xor(expr, rhs);
        }
        return expr;
    }

    Expr *visitE1() {
        Expr *expr = visitE2();
        while (takeIf('|')) {
            Expr *rhs = visitE2();
            expr = new Or(expr, rhs);
        }
        return expr;
    }

    Expr *visitE2() {
        Expr *expr = visitE3();
        while (takeIf('&')) {
            Expr *rhs = visitE3();
            expr = new And(expr, rhs);
        }
        return expr;
    }

    Expr *visitE3() {
        Expr *expr = visitE4();
        while (takeIf('=')) {
            Expr *rhs = visitE4();
            expr = new Equals(expr, rhs);
        }
        return expr;
    }

    Expr *visitE4() {
        bool neg = false;
        while (takeIf('!')) neg = !neg;
        Expr *expr = visitE5();
        return neg ? new Neg(expr) : expr;
    }

    Expr *visitE5() {
        if (takeIf('x')) {
            return new X();
        } else if (takeIf('y')) {
            return new Y();
        } else if (takeIf('(')) {
            Expr *nestedExpr = visitE0();
            take(')');
            return nestedExpr;
        } else if (takeIf('0')) {
            return new Literal(false);
        } else if (takeIf('1')) {
            return new Literal(true);
        }
        assert(false);
    }
};

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);
    
    int n; int k; cin >> n >> k;
    string s;
    cin.ignore(100, '\n');
    getline(cin, s, '_');

    // parse the function
    Parser parser(s);
    Func *func = parser.visitFunc();

    // naive: simulate all inputs
    // O(n2^(2k)) <= 2 * 10^5 * 2^20 ~= 2 * 10^11
    // need to use constraints to remove the n
    // each line is a truth table on x[a], y[b]
    // there are only k^2 <= 100 pairs of (a, b), and 16 possible truth tables for each line
    // thus we get only 1600 possible distinct lines
    // which reduces the complexity to O(16 * k^2 * 2^(2k)) <= 16 * 10 * 10 * 2^20 < 2 * 10^9
    uint16_t cap = 1u << k;
    uint32_t capSqd = 1u << (k * 2);
    uint32_t mask = (1u << k) - 1;
    bitset<1 << 20> rvCache; // rvCache[(x << k) | y] = func->sim(x, y)
    for (uint32_t input = 0; input < capSqd; ++input) {
        rvCache[input] = func->sim((uint16_t)(input >> k), (uint16_t)(input & mask));
    }
    auto f = [&](uint16_t x, uint16_t y) {
        return rvCache[((uint32_t)x << k) | (uint32_t)y];
    };
    
    // check for violations
    // O(2^(3k)) <= 2^30 ~=10^8
    uint32_t reflexiveViolations = 0;
    uint32_t symmetricViolations = 0;
    uint32_t transitiveViolations = 0;
    for (uint16_t x = 0; x < cap; ++x) {
        reflexiveViolations += f(x, x);
        for (uint16_t y = 0; y < cap; ++y) {
            symmetricViolations += f(x, y) && f(y, x);
            for (uint16_t z = 0; z < cap; ++z) {
                transitiveViolations += f(x, y) && f(y, z) && !f(x, z);
            }
        }
    }
    cout << reflexiveViolations << "\n" << symmetricViolations << "\n" << transitiveViolations << endl;
    delete func;
}
