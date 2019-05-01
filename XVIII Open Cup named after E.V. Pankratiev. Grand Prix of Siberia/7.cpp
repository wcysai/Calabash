#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;


inline bool isstar(string str) {
    return str.size() > 1 and str.rbegin()[1] == '*';
}

#define OP_LIT 0
#define OP_AND 1
#define OP_OR 2
#define OP_STAR 3

struct re {
    int type;
    string str;
    re *lhs, *rhs;
};

vector<re*> regs;

inline void create_literal(string str) {
    re* ret = new re; 
    ret->type = OP_LIT;
    ret->str = str;
    regs.push_back(ret);
}

inline void create_and(re* lhs, re* rhs) {
    if (lhs->str.size() + rhs->str.size() >= 14) return;
    if (lhs == rhs) return;
    if (lhs->type == OP_AND) return;    // associativity
    re* ret = new re; 
    ret->type = OP_AND;
    ret->str = "(" + lhs->str + rhs->str + ")";
    ret->lhs = lhs;
    ret->rhs = rhs;
    regs.push_back(ret);
}

inline void create_or(re* lhs, re* rhs) {
    if (lhs->str.size() + rhs->str.size() >= 13) return;
    if (lhs->type == OP_STAR || rhs->type == OP_STAR) return;
    if (lhs->type == OP_OR) return;     // associativity
    re* ret = new re; 
    ret->type = OP_OR;
    ret->str = "(" + lhs->str + "|" + rhs->str + ")";
    ret->lhs = lhs;
    ret->rhs = rhs;
    regs.push_back(ret);
}

inline void create_star(re* lhs) {
    if (lhs->str.size() >= 13) return;
    if (lhs->type == OP_STAR) return;   // idempotence
    re* ret = new re;
    ret->type = OP_STAR;
    ret->str = "(" + lhs->str + "*)";
    ret->lhs = lhs;
    regs.push_back(ret);
}

int nregs;
vector<string> regstrs;
vector<regex> reobj;

void prep() {
    create_literal("a");
    create_literal("g");
    create_literal("t");
    create_literal("c");
    size_t last = 0, cur = regs.size();
    while (last != regs.size()) {
        cur = regs.size();
        fprintf(stderr, "last = %lu, cur = %lu\n", last, cur);
        
        // Or Operator
        for (size_t i = 0; i < cur; i++) {
            if (regs[i]->str.size() >= 12) continue;
            for (int j = i + 1; j < cur; j++) {
                if (i < last and j < last) continue;
                create_or(regs[i], regs[j]);
            }
        }

        // And Operator
        for (size_t i = 0; i < cur; i++) {
            if (regs[i]->str.size() >= 13) continue;
            for (int j = 0; j < cur; j++) {
                if (i < last and j < last) continue;
                create_and(regs[i], regs[j]);
            }
        }

        // Kleen Closure
        for (size_t i = last; i < cur; i++)  create_star(regs[i]); 
        
        last = cur;
    }
    for (auto reg : regs) 
        regstrs.push_back(reg->str);
    regstrs.push_back("((a|(t|(c|g)))*)");
    sort(range(regstrs), [](const string &a, const string& b) -> bool {
        return a.size() < b.size();
    });
    nregs = regstrs.size();
    for (string s : regstrs) reobj.emplace_back(s, regex::optimize); 
}

int main() {
    prep();
    int T; scanf("%d", &T);
    while (T--) {
        int n;
        vector<string> str;
        cin >> n;
        set<char> schr;
        rep (i, n) {
            int len; cin >> len;
            string cur; if (len) cin >> cur;
            for (char ch : cur) schr.insert(ch);
            str.push_back(cur);
        }
        if (schr.empty()) {
            puts("(0*)");
            continue;
        }
        rep (i, nregs) {
            set<char> sreg;
            for (char ch : regstrs[i]) if (isalpha(ch)) sreg.insert(ch);
            if (sreg != schr) continue;
            for (string& s : str) 
                if (regex_match(s, reobj[i]) == false) goto fail;

            cout << regstrs[i] << endl;            
            break;
            
            fail:;
        }
    }
    return 0;
}
