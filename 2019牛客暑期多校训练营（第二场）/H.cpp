#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 1005
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int a[MAXN][MAXM];
int h[MAXN];
int L[MAXN],R[MAXN];
int st[MAXN];
int mx=0,mx2=0;
map<pair<P,int>,int> mp;
string str;
void update(int val)
{
    if(val>mx)
    {
        mx2=mx;
        mx=val;
    }
    else if(val>mx2) mx2=val;
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(h,0,sizeof(h));
    for(int i=1;i<=n;i++)
    {
        cin>>str;
        for(int j=1;j<=m;j++)
            a[i][j]=(int)(str[j-1]-'0');
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++) h[j]=(!a[i][j]?0:h[j]+1);
        int t=0;
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
        mp.clear();
        for(int j=1;j<=m;j++)
        {
            if(mp.count(make_pair(P(L[j],R[j]),h[j]))) continue;
            mp[make_pair(P(L[j],R[j]),h[j])]=1;
            if(!h[j]) continue;
            int len=R[j]-L[j]-1;
            update(len*h[j]);
            if(len>1) update((len-1)*h[j]);
            if(h[j]>1) update(len*(h[j]-1));
        }
    }
    printf("%d\n",mx2);
    return 0;
}
