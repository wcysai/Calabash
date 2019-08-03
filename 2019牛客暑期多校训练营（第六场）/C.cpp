#include<bits/stdc++.h>
using namespace std;
#define rep(i,st,ed) for (int i=st;i<=ed;++i)
#define drp(i,st,ed) for (int i=st;i<=ed;++i)
#define lb(x) (x&-x)
#define fi first
#define se second
typedef long long LL;
#define int long long
const int N=200000 + 200;
char str[N];
int m;
int n;
namespace Solve {

    struct PAM {
        int rec[N][27], fa[N], len[N], d[N], up[N], tot, last;
        int pos[N], size[N];
        std::vector<int> G[N];

        PAM() {
            clear();
            fa[0] = 1;
            len[1] = -1;
            tot = 1;
            last = 0;
        }
        void clear(int n = 0){
            memset(rec,0,sizeof rec);
            memset(fa,0,sizeof fa);
            memset(len,0,sizeof len);
            memset(d,0,sizeof d);
            memset(up,0,sizeof up);
            memset(pos,0,sizeof pos);
            memset(size,0,sizeof size);
            fa[0] = 1;
            len[1] = -1;
            tot = 1;
            last = 0;

        }
        void extend(int ch, int n) {
            int p = last;
            while (str[n - len[p] - 1] != str[n]) p = fa[p];
            if (!rec[p][ch]) {
                tot++;
                len[tot] = len[p] + 2;
                int k = fa[p];
                while (str[n] != str[n - len[k] - 1]) k = fa[k];
                fa[tot] = rec[k][ch];
                rec[p][ch] = tot;
                d[tot] = len[tot] - len[fa[tot]];
                up[tot] = (d[fa[tot]] == d[tot] ? up[fa[tot]] : tot);
            }
            last = rec[p][ch];
        }

        void build() {
            pos[0] = 0;
            for (int i=0;i<=tot;i++)G[i].clear();
            rep(i, 0, tot) if (i != 1) G[fa[i]].push_back(i);
        }

        void dfs(int x) {
            pos[x] = ++pos[0], size[x] = 1;
            for (int i = 0; i < G[x].size(); ++i) {
                int y = G[x][i];
                dfs(y), size[x] += size[y];
            }
        }
    } Pam;

    std::vector<pair<int, int> > Q[N];

    LL s[N], rec[N], Max[N << 2];



    void add(int x, int v) {
        for (; x <= n; x += lb(x)) s[x] += v;
    }

    LL get(int x) {
        LL res = 0;
        for (; x; x -= lb(x)) res += s[x];
        return res;
    }

    int query(int now, int tl, int tr, int l, int r) {
        if (tl >= l && tr <= r) return Max[now];
        int mid = (tl + tr) >> 1, qx = 0, qy = 0;
        if (l <= mid) qx = query(now << 1, tl, mid, l, r);
        if (mid + 1 <= r) qy = query(now << 1 | 1, mid + 1, tr, l, r);
        return std::max(qx, qy);
    }

    void modify(int now, int tl, int tr, int x, int v) {
        if (tl == tr) return (void) (Max[now] = v);
        int mid = (tl + tr) >> 1;
        if (x <= mid) modify(now << 1, tl, mid, x, v);
        else modify(now << 1 | 1, mid + 1, tr, x, v);
        Max[now] = std::max(Max[now << 1], Max[now << 1 | 1]);
    }
    int Main() {
        str[0] = 255;
        rep(i, 1, n) {
            Pam.extend(str[i] - 'a' + 1, i);
        }
        Pam.build();
        Pam.dfs(1);
        int now = 1;
        rep(i, 1, n) {
            while (str[i] != str[i - Pam.len[now] - 1]) now = Pam.fa[now];
            now = Pam.rec[now][str[i] - 'a' + 1];
            for (int x = now; x; x = Pam.fa[Pam.up[x]]) {
                int l = std::max(1ll, query(1, 1, Pam.pos[0], Pam.pos[x], Pam.pos[x] + Pam.size[x] - 1) - Pam.len[x] + 2);
                int r = i - Pam.len[Pam.up[x]] + 2;
                add(l, 1), add(r, -1);
            }
            modify(1, 1, Pam.pos[0], Pam.pos[now], i);
            for (int j = 0; j < Q[i].size(); ++j) {
                rec[Q[i][j].se] = get(Q[i][j].fi);
            }
        }
        LL ans = 0;
        rep(i, 1, m) ans += rec[i];
        printf("%lld\n", ans - m);
        return 0;
    }
    void main(vector<pair<int,int> > &Querys){
        for (int i=1;i<=n;i++)Q[i].clear();
        m = Querys.size();
        Pam.clear(n + 5);
        memset(s,0,sizeof s);
        memset(rec,0,sizeof rec);
        memset(Max,0,sizeof Max);
        int idx = 1;
        for (auto pr : Querys){
            Q[pr.second].push_back(make_pair(pr.first,idx));
            idx ++;
        }
        Main();
    }


}
namespace PAMM{
    const int maxn = 3e5+100;
    struct Palindromic_AutoMaton{
        //basic
        int s[maxn],now;
        int nxt[maxn][26],fail[maxn],l[maxn],last,tot;
        int ed[maxn];
        void clear(int n){
            memset(s,0,sizeof s);
            memset(nxt,0,sizeof nxt);
            memset(fail,0,sizeof fail);
            memset(l,0,sizeof l);
            last = tot = 0;
            memset(ed,0,sizeof ed);
            //1节点：奇数长度root 0节点：偶数长度root
            s[0]=l[1]=-1;
            fail[0] = tot = now =1;
            last = l[0]=0;
            ed[0] = ed[1] = 0;
            memset(nxt[0],0,sizeof nxt[0]);
            memset(nxt[1],0,sizeof nxt[1]);

        }
        Palindromic_AutoMaton(){clear(100000);}
        int newnode(int ll,int epp){
            tot++;
            ed[tot] = epp;
            memset(nxt[tot],0,sizeof nxt[tot]);
            fail[tot] =  0;
            l[tot]=ll;
            return tot;
        }
        int get_fail(int x){
            while (s[now-l[x]-2]!=s[now-1])x = fail[x];
            return x;
        }
        void add(int ch,int r){
            s[now++] = ch;
            int cur = get_fail(last);
            if(!nxt[cur][ch]){
                int tt = newnode(l[cur]+2,r);
                fail[tt] = nxt[get_fail(fail[cur])][ch];
                nxt[cur][ch] = tt;
            }
            last = nxt[cur][ch];
        }
        void init(char* ss){
            int len = 0;
            while (*ss){
                len ++;
                add(*ss-'a',len);ss++;
            }
        }
        vector<pair<int,int> > build(){
            vector<pair<int,int> > Q(0);
            for (int i = 2;i<=tot;i++){
                if (ed[i])
                Q.push_back(make_pair(ed[i] - l[i] + 1,ed[i]));
            }
            return Q;
        }
    }pam;
}
int T;
signed main(){
    scanf("%lld",&T);
    for (int i=1;i<=T;i++){
        printf("Case #%lld: ",i);
        n = m = 0;
        memset(str,0,sizeof str);
        scanf("%s",str+1);
        n = strlen(str+1);
        PAMM::pam.clear(n + 5);
        PAMM::pam.init(str+1);
        vector<pair<int,int> > Q = PAMM::pam.build();

        Solve::main(Q);
    }
    return 0;
}
