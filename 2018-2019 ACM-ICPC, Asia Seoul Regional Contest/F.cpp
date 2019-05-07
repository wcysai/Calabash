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

int ptr = 0;
char buf[1024];

bool isop(char ch) {
    return ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '%';
}

void expr_strict() {
    if (isalpha(buf[ptr])) {
        ptr++;
    } else {
        if (buf[ptr++] != '(') throw 0;
        expr_strict();
        if (!isop(buf[ptr++])) throw 0;
        expr_strict();
        if (buf[ptr++] != ')') throw 0;
    }
}

bool test_expr_strict() {
    ptr = 0;
    try {
        expr_strict();
        return buf[ptr] == 0;
    } catch (...) {
        return false;
    }
}

void expr_loose() {
    if (isalpha(buf[ptr])) {
        ptr++;
    } else {
        if (buf[ptr++] != '(') throw 0;
        expr_loose();
        while (isop(buf[ptr])) {
            ptr++;
            expr_loose();
        }
        if (buf[ptr++] != ')') throw 0;
    }
}

bool test_expr_loose() {
    ptr = 0;
    try {
        expr_loose();
        return buf[ptr] == 0;
    } catch (...) {
        return false;
    }
}

int main() {
    string cur; getline(cin, cur); cur = '(' + cur + ')';
    for (char ch : cur) if (ch != ' ') buf[ptr++] = ch;
    if (strlen(buf) == 3 and buf[0] == '(' and isalpha(buf[1]) and buf[2] == ')') {
        puts("proper");
        return 0;
    }
    if (test_expr_strict()) {
        puts("proper");
    } else if (test_expr_loose()) {
        puts("improper");
    } else {
        puts("error");
    }
    return 0;
}
