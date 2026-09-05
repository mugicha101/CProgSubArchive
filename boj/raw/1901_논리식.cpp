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

// truth table
struct TT {
    bool unary; // if unary, first operand always 0 so just set first row of table

    // 0 = false, 1 = unknown, 2 = true
    const uint8_t UK = 1;
    uint8_t r[3][3] = {};
    void set(bool f, bool t) {
        unary = true;
        r[0][0] = rep(f);
        r[0][1] = f ^ t ? UK : rep(f);
        r[0][2] = rep(t);
    }
    void set(bool ff, bool ft, bool tf, bool tt) {
        unary = false;
        r[0][0] = rep(ff);
        r[0][1] = ff ^ ft ? UK : rep(ff);
        r[0][2] = rep(ft);
        r[1][0] = ff ^ tf ? UK : rep(ff);
        r[1][1] = (ff == ft) && (ff == tf) && (ff == tt) ? rep(ff) : UK;
        r[1][2] = ft ^ tt ? UK : rep(tt);
        r[2][0] = rep(tf);
        r[2][1] = tf ^ tt ? UK : rep(tt);
        r[2][2] = rep(tt);
    }
    inline uint8_t eval(uint8_t a, uint8_t b) const {
        assert(!unary);
        return r[a][b];
    }
    inline uint8_t eval(uint8_t a) const {
        assert(unary);
        return r[0][a];
    }
};

enum struct TokenType {
    LPAREN, RPAREN, OP, VAR
};
struct Token {
    TokenType type;
    string val;

    Token(TokenType type, string val) : type(type), val(val) {}
};

unordered_map<string,int> opId;
vector<TT> ops;
uint8_t vars[256];
vector<Token> tokens;
size_t nextToken = 0;
TT &getOp() {
    return ops[opId[tokens[nextToken++].val]];
}
uint8_t evalExpr() {
    // int s = nextToken;
    if (tokens[nextToken].type == TokenType::LPAREN) {
        uint8_t res;
        ++nextToken;
        // either ( expr op expr ) or ( op expr )
        if (tokens[nextToken].type == TokenType::OP) {
            // ( op expr )
            TT &tt = getOp();
            assert(tt.unary);
            res = tt.eval(evalExpr());
        } else {
            // ( expr op expr )
            uint8_t a = evalExpr();
            TT &tt = getOp();
            assert(!tt.unary);
            uint8_t b = evalExpr();
            res = tt.eval(a, b);
        }
        assert(tokens[nextToken++].type == TokenType::RPAREN);
        // for (int i = s; i < (int)nextToken; ++i) {
        //     cout << tokens[i].val << " ";
        // }
        // cout << "= " << (int)res << "\n";
        return res;
    }

    // var
    assert(tokens[nextToken].type == TokenType::VAR);
    return vars[(int)tokens[nextToken++].val[0]];
}

int main() {
    // env setup
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(12);

    int tc = 0;
    while (true) {
        ++tc;
        int nu, nb; cin >> nu >> nb;
        if (nu == -1) break;

        // read operators
        ops.resize(nu + nb);
        for (int i = 0; i < nu; ++i) {
            string l; cin >> l;
            opId[l] = i;
            string f, t; cin >> f >> t;
            ops[i].set(f[0] == 't', t[0] == 't');
        }
        for (int i = nu; i < nu + nb; ++i) {
            string l; cin >> l;
            opId[l] = i;
            string ff, ft, tf, tt; cin >> ff >> ft >> tf >> tt;
            ops[i].set(ff[0] == 't', ft[0] == 't', tf[0] == 't', tt[0] == 't');
        }

        // read expression
        cin.ignore(100, '\n');
        string expr; getline(cin, expr);
        expr.push_back('\n');

        // read vars
        for (uint8_t &x : vars) x = 1;
        while (true) {
            string name; cin >> name;
            if (name[0] == '*') break;

            string val; cin >> val;
            vars[(int)name[0]] = rep(val[0] == 't');
        }

        // convert expression to tokens
        tokens.clear();
        for (int i = 0; i < (int)expr.size();) {
            if (expr[i] == ' ' || expr[i] == '\n') {
                ++i; continue;
            }
            if (expr[i] == '(') {
                tokens.emplace_back(TokenType::LPAREN, expr.substr(i, 1));
                ++i; continue;
            }
            if (expr[i] == ')') {
                tokens.emplace_back(TokenType::RPAREN, expr.substr(i, 1));
                ++i; continue;
            }
            if (expr[i] >= 'a' && expr[i] <= 'z') {
                tokens.emplace_back(TokenType::VAR, expr.substr(i, 1));
                ++i; continue;
            }
            if (expr[i] >= 'A' && expr[i] <= 'Z') {
                int len = 1;
                while (expr[i+len] >= 'A' && expr[i+len] <= 'Z') ++len;
                tokens.emplace_back(TokenType::OP, expr.substr(i, len));
                i += len; continue;
            }
            assert(false);
        }

        // evaluate expression
        nextToken = 0;
        uint8_t res = evalExpr();
        cout << "Case " << tc << ": " << (res == 0 ? "false" : res == 2 ? "true" : "unknown") << "\n";
    }
}
