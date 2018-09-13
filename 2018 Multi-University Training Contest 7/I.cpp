#include <bits/stdc++.h>
using namespace std;
#define maxn 110010
#define N maxn
const int MAXBUF = 10000;
char buf[MAXBUF], *ps = buf, *pe = buf+1;
inline void rnext()
{
    if(++ps == pe)
        pe = (ps = buf)+fread(buf,sizeof(char),sizeof(buf)/sizeof(char),stdin);
}

template <class T>
inline bool in(T &ans)
{
    ans = 0;
    T f = 1;
    if(ps == pe) return false;//EOF
    do{
        rnext();
        if('-' == *ps) f = -1;
    }while(!isdigit(*ps) && ps != pe);
    if(ps == pe) return false;//EOF
    do
    {
        ans = (ans<<1)+(ans<<3)+*ps-48;
        rnext();
    }while(isdigit(*ps) && ps != pe);
    ans *= f;
    return true;
}
const int  MAXOUT=10000;
char bufout[MAXOUT], outtmp[50],*pout = bufout, *pend = bufout+MAXOUT;
inline void write()
{
    fwrite(bufout,sizeof(char),pout-bufout,stdout);
    pout = bufout;
}
inline void out_char(char c){ *(pout++) = c;if(pout == pend) write();}
inline void out_str(char *s)
{
    while(*s)
    {
        *(pout++) = *(s++);
        if(pout == pend) write();
    }
}
template <class T>
inline void out_int(T x) {
    if(!x)
    {
        out_char('0');
        return;
    }
    if(x < 0) x = -x,out_char('-');
    int len = 0;
    while(x)
    {
        outtmp[len++] = x%10+48;
        x /= 10;
    }
    outtmp[len] = 0;
    for(int i = 0, j = len-1; i < j; i++,j--) swap(outtmp[i],outtmp[j]);
    out_str(outtmp);
}
//inline void in(int& ret){
//    ret =0;
//    char ch = getchar();
//    while (ch<'0'||ch>'9')ch = getchar();
//    while (ch>='0'&& ch<='9')ret = ret*10+ch-'0',ch = getchar();
//}
using namespace std;
struct node{
    int ch[2],fa,rev,Size;
}tree[maxn];
int sta[maxn],n,m;
inline bool isroot(int x) {
    return tree[tree[x].fa].ch[0]!=x&&tree[tree[x].fa].ch[1]!=x;
}
inline void pushup(int x) {
    tree[x].Size=tree[tree[x].ch[0]].Size+tree[tree[x].ch[1]].Size+1;
}
inline void pushdown(int x) {
    if(tree[x].rev) {
        tree[tree[x].ch[0]].rev^=1;
        tree[tree[x].ch[1]].rev^=1;
        swap(tree[x].ch[0],tree[x].ch[1]);
        tree[x].rev=0;
    }
}
inline void rot(int x) {
    int y=tree[x].fa,z=tree[y].fa;
    bool l=(tree[y].ch[0]==x ? 0 :1 );
    bool r=l^1;
    if(isroot(y)==0){
        if(tree[z].ch[0]==y) tree[z].ch[0]=x;
        else tree[z].ch[1]=x;
    }
    tree[x].fa=z;tree[y].fa=x;
    tree[tree[x].ch[r]].fa=y;
    tree[y].ch[l]=tree[x].ch[r];
    tree[x].ch[r]=y;
    pushup(y);pushup(x);
}
inline void splay(int x) {
    int y,z;
    int top=0;sta[++top]=x;
    for(int i=x;isroot(i)==0;i=tree[i].fa) sta[++top]=tree[i].fa;
    for(int i=top;i>=1;i--) pushdown(sta[i]);
    while(isroot(x)==0) {
        y=tree[x].fa;z=tree[y].fa;
        if(isroot(y)==0) {
            if((tree[y].ch[0]==x)^(tree[z].ch[0]==y)) rot(x);
            else rot(y);
        }
        rot(x);
    }
}
inline void access(int x) {
    int y=0;
    while(x) {
        splay(x);
        tree[x].ch[1]=y;
        pushup(x);
        y=x;
        x=tree[x].fa;
    }
}
inline void make_root(int x) {
    access(x);
    splay(x);
    tree[x].rev^=1;
}
inline void link(int x,int y) {
    make_root(x);
    tree[x].fa=y;
}
inline void cut(int x,int y) {
    make_root(x);
    access(y);
    splay(y);
    tree[x].fa=tree[y].ch[0]=0;
}
inline int query(int x) {
    access(x);splay(x);
    return tree[tree[x].ch[0]].Size;
}
int dep[N];
int first[N],des[N*2],nxtt[N*2],tot;
int nowfa[N];
int st[N][20];
inline void addEdge(int x,int y){
    tot ++;
    des[tot] = y;
    nxtt[tot] = first[x];
    first[x] = tot;
}
void dfs(int u,int fa){
    st[u][0] = fa;
    for (int i=1;i<17 && st[u][i-1];i++){
        st[u][i] = st[st[u][i-1]][i-1];
    }
    dep[u] = dep[fa]+1;
    for (int t = first[u];t;t=nxtt[t]){
        int v = des[t];
        if (v == fa)continue;
        dfs(v,u);
    }
}
int calc_anc(int u,int dept){
    if (dep[u]<dept){
        return n+1;
    }
    for (int i=0;i<17 && u ;i++){
        if (dept&(1<<i)){
            u = st[u][i];
        }
    }
    if (u == 0){
        u = n+1;
    }
    return u;
}
void solve(){
    in(n);
    for(int i=1;i<=n+1;i++) {
        tree[i].fa=tree[i].ch[0]=tree[i].ch[1]=0;
        tree[i].Size=1;
        first[i] = 0;
    }
    tot =0;
    dep[n+1] = 0;
    dep[0] = 0;
    for (int i=2;i<=n;i++){
        int fa;
        in(fa);
        addEdge(fa,i);
        addEdge(i,fa);
    }
    dfs(1,0);
    for (int i=1;i<=n;i++){
        int k;
        in(k);
        nowfa[i] = calc_anc(i,k);
        link(i,nowfa[i]);
    }

    tree[n+1].Size=1;
    in(m);
    while(m--) {
        int op;
        in(op);
        if(op==1) {
            int x;
            in(x);
            make_root(n+1);
//            printf("%d\n",query(x));
            out_int(query(x));
            out_char('\n');
        }
        else {
            int x,val;
            in(x);
            in(val);
            cut(x,nowfa[x]);
            nowfa[x]=calc_anc(x,val);
            link(x,nowfa[x]);
        }
    }
}
int main()
{
    int Case;
    in(Case);
    while (Case --){
        solve();
    }
    write();
    return 0;

}
