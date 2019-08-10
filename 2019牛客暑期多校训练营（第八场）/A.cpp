#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int a[MAXN][MAXN];
int h[MAXN];
int rightmost[MAXN][MAXN];
int L[MAXN],R[MAXN];
int t,st[MAXN];
string str;
set<P> us;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        cin>>str;
        for(int j=1;j<=m;j++) a[i][j]=(int)str[j-1]-'0';
    }
    for(int i=1;i<=n;i++)
        for(int j=m;j>=1;j--)
        {
            if(!a[i][j]) rightmost[i][j]=-1;
            else rightmost[i][j]=max(j,rightmost[i][j+1]);
        }
    int ans=0;
    memset(h,0,sizeof(h));
    for(int i=1;i<=n;i++)
    {
        us.clear();
        for(int j=1;j<=m;j++)
        {
            if(a[i][j]==1) h[j]++; else h[j]=0;
        }
        t=0;
        for(int j=1;j<=m;j++)
        {
            while(t>0&&h[st[t-1]]>=h[j]) t--;
            L[j]=t==0?0:st[t-1];
            st[t++]=j;
        }
        t=0;
        for(int j=m;j>=1;j--)
        {
            while(t>0&&h[st[t-1]]>=h[j]) t--;
            R[j]=t==0?m+1:st[t-1];
            st[t++]=j;
        }
        for(int j=1;j<=m;j++)
        {
            if(!h[j]) continue;
            if(i<n&&rightmost[i+1][L[j]+1]>=R[j]-1) continue;
            us.insert(P(L[j],R[j]));
        }
        ans+=(int)us.size();
    }
    printf("%d\n",ans);
    return 0;
}
