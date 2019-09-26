#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN];
int fl[MAXN],gl[MAXN],fr[MAXN],gr[MAXN],toleft[MAXN],toright[MAXN];
int get_ans(int l,int r)
{
    if(l>r) return -1;
    if(toleft[r]<=l) return -1;
    if(toleft[r-1]<=l||toright[l+1]>=r) return 1;
    if(toleft[r-1]<=l+1) return -1;
    if(toleft[r-2]<=l)
    {
        int x;
        if(toleft[r-1]<toleft[r])
        {
            x=toleft[r-1];
            if((x-l)&1) return -1; else return 1;
        }
        else
        {
             x=toleft[r];
            if((x-l)&1) return 1; else return -1;
        }
    }
    if(toright[l+2]>=r)
    {
        int x;
        if(toright[l+1]>toright[l])
        {
            x=toright[l+1];
            if((r-x)&1) return -1; else return 1;
        }
        else
        {
            x=toright[l];
            if((r-x)&1) return 1; else return -1;
        }
    }
    return 0;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    fl[1]=gl[1]=1;
    for(int i=2;i<=n;i++)
    {
        fl[i]=(a[i]>=a[i-1]?fl[i-1]:i);
        gl[i]=(a[i]<=a[i-1]?gl[i-1]:i);
        toleft[i]=min(fl[i],gl[i]);
    }
    fr[n]=gr[n]=n;
    for(int i=n-1;i>=1;i--)
    {
        fr[i]=(a[i]>=a[i+1]?fr[i+1]:i);
        gr[i]=(a[i]<=a[i+1]?gr[i+1]:i);
        toright[i]=max(fr[i],gr[i]);
    }

    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        int lb=-1,rb=(r-l)/2+2;
        while(rb-lb>1)
        {
            int mid=(lb+rb)/2;
            if(!get_ans(l+mid,r-mid)) lb=mid; else rb=mid;
        }
        if(get_ans(l+lb+1,r-lb-1)==1) puts("Alice"); else puts("Bob");
    }
    return 0;
}
