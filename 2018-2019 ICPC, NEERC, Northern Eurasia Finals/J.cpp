#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

set<string> keys;
vector<string> words;
map<string, string> renm;

bool possible(string str) {
    auto ptr = keys.lower_bound(str);
    if (ptr == keys.end()) return 0;
    if (ptr->length() < str.length()) return 0;
    return ptr->substr(0, str.length()) == str;
}

int isidchr(char ch) {
    return isalpha(ch) or ch == '_' or ch == '$';
}

vector<string> tokenize(string str, bool remap) {
    vector<string> ret;
    int ptr = 0;
    while (str[ptr] == ' ') ptr++;
    while (str[ptr]) {
        string cur; 
        int cptr = ptr, lptr;
        if (isdigit(str[ptr])) {
            while (isdigit(str[cptr])) {
                cur += str[cptr];
                cptr++;
            }
            lptr = cptr;
            while (str[cptr] and possible(cur)) {
                cur += str[cptr];
                cptr++;
                if (keys.count(cur)) lptr = cptr;
            }
            cur = string(str.begin() + ptr, str.begin() + lptr);
            ptr = lptr;
            ret.push_back(cur);
        } else if (isidchr(str[cptr])) {
            while (isidchr(str[cptr]) or isdigit(str[cptr])) {
                cur += str[cptr];
                cptr++;
            }
            lptr = cptr;
            while (str[cptr] and possible(cur)) { 
                cur += str[cptr];
                cptr++;
                if (keys.count(cur)) lptr = cptr;
            }
            cur = string(str.begin() + ptr, str.begin() + lptr);
            ptr = lptr;
            if (keys.count(cur)) {
                ret.push_back(cur);
            } else if (remap) {
                if (renm.find(cur) == renm.end()) {
                    renm[cur] = words.back();
                    words.pop_back();
                }
                ret.push_back(renm[cur]);
            } else ret.push_back(cur);
        } else {
            cptr = ptr; 
            while (str[cptr] and possible(cur)) { 
                cur += str[cptr];
                cptr++;
                if (keys.count(cur)) lptr = cptr;
            }
            cur = string(str.begin() + ptr, str.begin() + lptr);
            ptr = lptr;
            ret.push_back(cur);
        }
        if (cur == "") break;
        while (str[ptr] == ' ') ptr++;
    }
    return ret;
}

int main() {
    int n, m; cin >> n;
    rep (i, n) {
        string key; cin >> key;
        keys.insert(key);
    }
    for (char ch = 'a'; ch <= 'z'; ch++) { 
        string word(1, ch);
        if (keys.count(word) == 0) words.push_back(word);
    }
    for (char c1 = 'a'; c1 <= 'z'; c1++)
        for (char c2 = 'a'; c2 <= 'z'; c2++) {
            string word(1, c1); word += c2;
            if (keys.count(word) == 0) words.push_back(word);
        }
    for (char c1 = 'a'; c1 <= 'z'; c1++) 
        for (char c2 = 'a'; c2 <= 'z'; c2++) 
            for (char c3 = 'a'; c3 <= 'z'; c3++) {
                string word(1, c1); word += c2; word += c3;
                if (keys.count(word) == 0) words.push_back(word);
            }
    sort(range(words), [] (string a, string b) {
                    if (a.size() != b.size()) return a.size() > b.size();
                    return a > b;
            });
    cin >> m; cin.get();
    string buf;
    int cnt = 0;
    while (m--) {
        string cur; getline(cin, cur);
        cur.erase(find(range(cur), '#'), cur.end());
        vector<string> tokens = tokenize(cur, 1);
        for (string token : tokens) {
            if (tokenize(buf + token, 0).back() != token) {
                if (cnt) cout << ' ';
                cout << buf;
                cnt ++;
                buf = token;
            } else buf += token;
        }
    }
    if (buf != "") {
        if (cnt) cout << ' ';
        cout << buf << endl;
    }
    return 0;
}
