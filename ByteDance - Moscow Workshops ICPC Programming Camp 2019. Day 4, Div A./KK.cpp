#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define lc t[x].ch[0]
#define rc t[x].ch[1]
#define pa t[x].fa
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN],root,tot;
struct node
{
    int ch[2];
    int fa;
    int rev,add; 
    int sz,w,maxi,mini;
    ll sum;
}t[MAXN];
inline int get(int x) {return t[pa].ch[1]==x;}
inline void pushup(int x)
{
    t[x].sum=t[x].maxi=t[x].mini=t[x].w;
    t[x].sz=1;
    if(lc) 
    {
        t[x].maxi=max(t[x].maxi,t[lc].maxi);
        t[x].mini=min(t[x].mini,t[lc].mini);
        t[x].sum+=t[lc].sum;
        t[x].sz+=t[lc].sz;
    }
    if(rc) 
    {
        t[x].maxi=max(t[x].maxi,t[rc].maxi);
        t[x].mini=min(t[x].mini,t[rc].mini);
        t[x].sum+=t[rc].sum;
        t[x].sz+=t[rc].sz;
    }
}
inline void rever(int x)
{
    t[x].rev^=1;
    swap(lc,rc);
}
inline void add(int x,int v)
{
    t[x].sum+=1LL*t[x].sz*v;
    t[x].maxi+=v;
    t[x].mini+=v;
    t[x].add+=v;
    t[x].w+=v;
}
inline void pushdown(int x)
{
    if(t[x].rev)
    {
        if(lc) rever(lc);
        if(rc) rever(rc);
        t[x].rev=0;
    }
    if(t[x].add)
    {
        if(lc) add(lc,t[x].add);
        if(rc) add(rc,t[x].add);
        t[x].add=0;
    }
}
inline void rotate(int x)
{
    int old=pa,oldf=t[old].fa,whichx=get(x);
    t[old].ch[whichx]=t[x].ch[whichx^1]; t[t[old].ch[whichx]].fa=old;
    t[x].ch[whichx^1]=old; t[old].fa=x;
    pa=oldf;
    if(oldf) t[oldf].ch[t[oldf].ch[1]==old]=x;
    pushup(old); pushup(x);
}
inline void splay(int x,int goal=0)
{
    for(int f;(f=t[x].fa)!=goal;rotate(x))
        if(t[f].fa!=goal) rotate((get(x)==get(f))?f:x);
    if(goal==0) root=x;
}
inline int findx(int x,int k)
{
    while(x)
    {
        pushdown(x);
        int cnt=t[lc].sz+1;
        if(k==cnt) return x;
        if(k>cnt) x=rc,k-=cnt;
        else x=lc;
    }
}
void build(int &x,int l,int r,int fa)
{
    if(l>r) return;
    int mid=(l+r)/2;
    x=++tot; pa=fa;
    t[x].w=a[mid];if(mid>=1&&mid<=n) t[x].sz=1; 
    build(lc,l,mid-1,x);build(rc,mid+1,r,x);
    pushup(x);
}
void debug()
{
    for(int i=1;i<=n+2;i++)
    {
        printf("%d %d %d %d %d %lld %d %d %d\n",i,t[i].fa,t[i].ch[0],t[i].ch[1],t[i].sz,t[i].sum,t[i].maxi,t[i].mini,t[i].add);
    }
}
int adjust(int l,int r)
{
    int x=findx(root,l-1);
    int y=findx(root,r+1);
    splay(x);splay(y,root);
    return t[y].ch[0];
}
char str[10];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    build(root,0,n+1,0);
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int l,r;
        scanf("%s",str);
        scanf("%d%d",&l,&r);l++;r++;
        int pos=adjust(l,r);
        if(str[0]=='c')
        {
            int v;
            scanf("%d",&v);
            add(pos,v);pushup(t[pos].fa);pushup(t[t[pos].fa].fa);
        }
        else if(str[0]=='r') 
        {
            rever(pos);
            pushup(t[pos].fa);pushup(t[t[pos].fa].fa);
        }
        else
        {
            printf("%lld %d %d\n",t[pos].sum,t[pos].mini,t[pos].maxi);
        }
    }
    return 0;
}

