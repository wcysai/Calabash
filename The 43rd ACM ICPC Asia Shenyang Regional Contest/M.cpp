#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int T,n,m;
vector<int> pos[MAXN],neg[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void add(vector<int> &a,int x)
{
    for(int i=1000;i>=x;i--) dec(a[i],a[i-x]);
}
void dec(vector<int> &a,int x)
{
    for(int i=x;i<=1000;i++) add(a[i],a[i-x]);
}
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        printf("Case #%d:\n",t);
        scanf("%d%d",&n,&m);
        pos[0].clear(); neg[0].clear();
        pos[0].resize(1001),neg[0].resize(1001);
        pos[0][0]=neg[0][0]=1;
        for(int i=1;i<=n;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            pos[i]=pos[i-1]; add(pos[i],(a+1)*b); dec(pos[i],b);
            neg[i]=neg[i-1]; dec(neg[i],(a+1)*b); add(neg[i],b);
        }
        int lastans=0;
        for(int i=0;i<m;i++)
        {
            int l,r,c;
            scanf("%d%d%d",&l,&r,&c);
            int tmpl=(l+lastans)%n+1,tmpr=(r+lastans)%n+1;
            if(tmpl>tmpr) swap(tmpl,tmpr);
            l=tmpl; r=tmpr;
            lastans=0;
            int sum=0;
            for(int i=0;i<=c;i++)
            {
                add(sum,pos[r][i]);
                add(lastans,1LL*sum*neg[l-1][c-i]%MOD);
            }
            printf("%d\n",lastans);
        }
    }
    return 0;
}
