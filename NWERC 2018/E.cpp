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

struct Scanner {
    char buf[1 << 20], *ptr = buf;
    
    Scanner() { scanf("%s", buf); }

    char peek() { return *ptr; }
    char get() { return *(ptr++); }
    
    int getint() {
        int ret = 0;
        while (isdigit(peek())) ret = ret * 10 + get() - '0';
        return ret;
    }
     
    list<int> List(bool unord) {
        list<int> ret;
        get();  // '['
        while (true) {
            ret.push_back(getint());
            if (get() == ']') return ret;
        }
    }

    list<int> Concat(bool unord) {
        while (isalpha(peek())) get();
        get();  // '('
        list<int> l1 = Expr(unord);
        get();  // ','
        list<int> l2 = Expr(unord);
        get();  // ')'
        l1.splice(l1.end(), l2);
        return l1;
    }

    list<int> Shuffle(bool unord) {
        while (isalpha(peek())) get();
        get();  // '('
        list<int> ret = Expr(1);
        get();  // ')'
        if (!unord) {
            ret.sort();
            if (ret.front() != ret.back()) {
                ret.push_front(-1);
                ret.push_back(-2);
            }
        }
        return ret;
    }

    list<int> Sorted(bool unord) {
        while (isalpha(peek())) get();
        get();  // '('
        list<int> ret = Expr(1);
        get();  // ')'
        if (!unord) ret.sort();
        return ret;
    }

    list<int> Expr(bool unord) {
        switch (peek()) {
        case '[' : return List(unord);
        case 'c' : return Concat(unord);
        case 's' : get();
            return (peek() == 'o') ? Sorted(unord) : 
                Shuffle(unord);
        }
    }

} scanner1, scanner2;

int main() {
    puts(
        (scanner1.Expr(0) == scanner2.Expr(0)) ?
        "equal" : "not equal"
        );
    return 0;
}
