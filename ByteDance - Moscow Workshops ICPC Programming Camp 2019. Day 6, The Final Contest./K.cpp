#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

int n, pos[1 << 20];
char str[1 << 20];
string ans;
char last_but_one = 0;

void push_char(char ch) {
    if (ch != ans.back()) last_but_one = ans.back();
    ans.push_back(ch);
}

void work(char *lptr) {
    string cur;  
    char until = ans.back(); 
    assert(until != last_but_one);
    if (until < last_but_one) until++;
    for (char ch = 'a'; ch < until; ch++) {
        for (char *ptr = lptr; *ptr; ptr++) {
            if (*ptr == ch) cur.push_back(ch), lptr = ptr + 1;
        }
    }
//    cout << cur << endl;
    reverse(range(cur));
    for (char ch : cur) push_char(ch);
}

int main() {
    scanf("%s", str); scanf("%d", &n);
    Rep (i, n) scanf("%d", pos + i), pos[i]--;
    push_char(str[pos[n]]); str[pos[n]] = 0;
    for (int i = n - 1; i > 0; i--) {
        work(str + pos[i] + 1);        
        push_char(str[pos[i]]); str[pos[i]] = 0;
    }
    work(str);
    reverse(range(ans)); 
//    assert(ans.back() == 0); ans.pop_back();
    cout << ans << endl;
    return 0;
}
