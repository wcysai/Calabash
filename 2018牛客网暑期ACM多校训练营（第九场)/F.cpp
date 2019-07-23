#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=(a);i<(n);++i)
int ch[1<<18][26], fail[1<<18], val[1<<18];
int sz, rt;
int newnode() {
    memset(ch[sz], -1, sizeof(ch[sz])), val[sz] = 0;
    return sz++;
}
struct KMP{
    static const int maxn = 1e5+100;
    int nxt[maxn];
    int len;
    void clear(){
        len =0;
        nxt[0] = nxt[1] =0;
    }
    /* 1-bas */
    /* 注意在ss结尾添加‘\0’ */
    void init(char* ss){
        len = strlen(ss+1);
        for (int i=2;i<=len;i++){
            nxt[i] = nxt[i-1];
            while (nxt[i]&&ss[i]!=ss[nxt[i]+1]) nxt[i] = nxt[nxt[i]];
            nxt[i]+=(ss[i]==ss[nxt[i]+1]);
        }
    }
    void debug(){
        for (int i=0;i<=len;i++){
            printf("[debug] nxt[%d]=%d\n",i,nxt[i]);
//            Debug(nxt[i]);
        }
    }
    /* 循环周期 形如 acaca 中 ac 是一个合法周期 */
    vector<int> periodic(){
        vector<int> ret;
        int now = len;
        while (now){
            now = nxt[now];
            ret.push_back(len-now);
        }
        return ret;
    }
    /* 循环节 形如 acac 中ac、acac是循环节，aca不是*/
    vector<int> periodic_loop(){
        vector<int>ret ;
        for (int x :periodic()){
            if (len%x==0){
                ret.push_back(x);
            }
        }
        return ret;
    }
    int min_periodic_loop(){
        return periodic_loop()[0];
    }
}kmper;
#define idx(x) ((x)-'a')
void insert(const char* s, int id) {
    int u = 0, n = strlen(s);
    for (int i = 0; i < n; i++) {
        int c = idx(s[i]);
        if (ch[u][c] == -1) ch[u][c] = newnode();
        u = ch[u][c];
    }
    val[u] |= 1 << id;
}
void get_fail() {
    queue<int> q;
    fail[rt] = rt;
    for (int c = 0; c < 26; c++) {
        if (~ch[rt][c])
            fail[ch[rt][c]] = rt, q.push(ch[rt][c]);
        else
            ch[rt][c] = rt;
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        val[u] |= val[fail[u]];
        for (int c = 0; c < 26; c++) {
            if (~ch[u][c])
                fail[ch[u][c]] = ch[fail[u]][c], q.push(ch[u][c]);
            else
                ch[u][c] = ch[fail[u]][c];
        }
    }
}
int d[1<<18];
vector<int> G[1<<18];
void solve(const char* op) {
    rep(u,0,sz)
        rep(c,0,26)
            if (~ch[u][c])
                G[ch[u][c]].push_back(u);
    memset(d, -1, sizeof(d));
    queue<int> q;
    rep(i,0,sz)
        if (val[i]) q.push(i), d[i] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto& v : G[u]) {
            if (~d[v]) continue;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    stack<int> s;
    int u = rt;
    s.push(u);
    printf("%d\n", d[u]);
    for (int i = 0; op[i]; i++) {
        if (op[i] == '-') {
            s.pop();
            if (!s.empty())
                u = s.top();
            else
                s.push(0);
            printf("%d\n", d[u]);
        } else {
            u = ch[u][op[i] - 'a'];
            s.push(u);
            printf("%d\n", d[u]);
        }
    }
}
int n;
string s;
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    cin>>n;
    sz = 0, rt = newnode();
    for (int i = 0; i < n; i++) {
        cin >> s;
        insert(s.c_str(), i);
    }
    get_fail();
    cin >> s;
    solve(s.c_str());
    return 0;
}
