#include <bits/stdc++.h>
#define N 50005
#define INF 1000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,i,id[N],root,cmp_d;
struct node{int d[2],l,r,Max[2],Min[2],val,sum,f;}t[N];
int a[N],x[N],y[N],X1,Y1,X2,Y2,k;
bool cmp(const node &a,const node &b) {return a.d[cmp_d]<b.d[cmp_d];}
void umax(int &a,int b) {if(a<b) a=b;}
void umin(int &a,int b) {if(a>b) a=b;}
void up(int x)
{
    if(t[x].l)
    {
        umax(t[x].Max[0],t[t[x].l].Max[0]);
        umin(t[x].Min[0],t[t[x].l].Min[0]);
        umax(t[x].Max[1],t[t[x].l].Max[1]);
        umin(t[x].Min[1],t[t[x].l].Min[1]);
    }
    if(t[x].r)
    {
        umax(t[x].Max[0],t[t[x].r].Max[0]);
        umin(t[x].Min[0],t[t[x].r].Min[0]);
        umax(t[x].Max[1],t[t[x].r].Max[1]);
        umin(t[x].Min[1],t[t[x].r].Min[1]);
    }
}
int build(int l,int r,int D,int f)
{
    int mid=(l+r)/2;
    cmp_d=D,std::nth_element(t+l+1,t+mid+1,t+r+1,cmp);
    id[t[mid].f]=mid;
    t[mid].f=f;
    t[mid].Max[0]=t[mid].Min[0]=t[mid].d[0];
    t[mid].Max[1]=t[mid].Min[1]=t[mid].d[1];
    t[mid].val=t[mid].sum=0;
    if(l!=mid) t[mid].l=build(l,mid-1,!D,mid); else t[mid].l=0;
    if(r!=mid) t[mid].r=build(mid+1,r,!D,mid); else t[mid].r=0;
    return up(mid),mid;
}
void change(int x,int p) {for(t[x=id[x]].val+=p;x;x=t[x].f) t[x].sum=max(t[x].sum,p);}
void ask(int x)
{
    if(t[x].Min[0]>X2||t[x].Max[0]<X1||t[x].Min[1]>Y2||t[x].Max[1]<Y1) return;
    if(t[x].Min[0]>=X1&&t[x].Max[0]<=X2&&t[x].Min[1]>=Y1&&t[x].Max[1]<=Y2)
    {
        k=max(k,t[x].sum);
        return;
    }
    if(t[x].d[0]>=X1&&t[x].d[0]<=X2&&t[x].d[1]>=Y1&&t[x].d[1]<=Y2) k=max(k,t[x].val);
    if(t[x].l) ask(t[x].l);
    if(t[x].r) ask(t[x].r);
}
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(n==0) break;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&x[i],&y[i],&a[i]);
            t[i].d[0]=x[i],t[i].d[1]=y[i],t[i].f=i;
        }
        root=build(1,n,0,0);
        for(int i=1;i<=n;i++) change(i,a[i]);
        //printf("%d %d %d %d\n",t[root].Min[0],t[root].Max[0],t[root].Min[1],t[root].Max[1]);
        int id=-1,ans=INF;
        for(int i=1;i<=n;i++)
        {
            if(a[i]>=ans) continue;
            k=0;X1=x[i]-a[i];Y1=y[i]-a[i];X2=x[i]+a[i];Y2=y[i]+a[i];
            ask(root);
            if(k==a[i])
            {
                ans=a[i];
                id=i;
            }
        }
        printf("%d %d\n",id,ans);
    }
    return 0;
}
