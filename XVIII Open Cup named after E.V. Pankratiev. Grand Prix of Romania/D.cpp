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

LL to_int(string str) {
    if (str.empty() || str[0] != '1') throw 0;
    LL ret = 0;
    for (char ch : str)
        ret = ret * 2 + (ch - '0');
    return ret;
}

string to_str(LL x) {
    if (x <= 0) throw 0;
    string str;
    while (x) {
        str.push_back((x & 1) + '0');
        x >>= 1;
    }
    reverse(range(str));
    return str;
}

ULL ans;
int len;
string str;

ULL get_position(LL v) {
    ULL cnt = 0;
    LL bit =  1;
    for (; bit < v; bit <<= 1) {
        cnt += bit / 2 * __builtin_ctzll(bit);
    }
    cnt += __builtin_ctzll(bit) * (v - bit / 2);
    return cnt ;
}

inline bool start_with(string str, string pre) {
    return str.substr(0, pre.size()) == pre;
}

inline bool end_with(string str, string suf) {
    return str.substr(str.size() - suf.size()) == suf;
}

bool consume_prefix(string pref, LL v) {
    if (pref.empty()) return true;
    while (--v > 0) {
        string str = to_str(v);
        if (pref.length() <= str.length()) {
            return end_with(str, pref);
        } else if (end_with(pref, str)){
            pref = pref.substr(0, pref.size() - str.size());
        } else return false;
    }
    return false;
}

bool consume_suffix(string suf, LL v) {
    if (suf.empty()) return true;
    while (++v) {
        string str = to_str(v);
        if (suf.length() <= str.length()) {
            return start_with(str, suf);
        } else if (start_with(suf, str)) {
            suf = suf.substr(str.length());
        } else {
            return false;
        }
    }
}

void try_mid() {
    for (int l = 0; l < len; l++) {
        if (str[l] == '0') continue;
        for (int r = l + 1; r <= len; r++) {
            string pre = str.substr(0, l), cur = str.substr(l, r - l), suf = str.substr(r);
            LL value = to_int(cur);
            if (consume_prefix(pre, value) && consume_suffix(suf, value)) {
                ans = min(ans, get_position(value) - pre.size());
            }
        }
    }
}

string concat(string left, string right) {
    for (int i = 0; i < left.size(); i++) {
        if (i + right.size() <= left.size()) continue;
        if (left.substr(i) == right.substr(0, left.size() - i)) return left.substr(0, i) + right;
    }
    return left + right;
}

string inc(string str) {
    for (auto it = str.rbegin(); it != str.rend(); it++) {
        if (*it == '1') {
            *it = '0';
        } else {
            *it = '1';
            break;
        }
    }
    return str;
}

void try_bipart() {
    for (int i = 1; i < len; i++) {
        if (str[i] == '0') continue;
        string lpart = str.substr(i), rpart = inc(str.substr(0, i));
        string res = concat(lpart, rpart);

        if (res.size() > 56) continue;
        LL num = to_int(res);
        ans = min(ans, get_position(num) - i);
        _debug("bipart %d, %s, %s, num=%lld, ans = %lld", i, lpart.c_str(), rpart.c_str(), num, ans);
    }
}

int main() {
    cin >> str;
    len = str.length();
    if (str[0] == '0') {
        ans = get_position(to_int("1" + str)) + 1;
    } else {
        ans = get_position(to_int(str));
    }
    _debug("%d", ans);
    try_mid();
    try_bipart();
    cout << ans + str.length() << endl;
    return 0;
}
