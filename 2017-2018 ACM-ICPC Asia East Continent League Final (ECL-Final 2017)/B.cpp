//
// Created by calabash_boy on 18-5-24.
//
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<double,int> P;
int t,n,m;
double a[MAXN];
priority_queue<P> pque;
int cnt[MAXN];
int main()
{
    scanf("%d",&t);
    int kase=0;
    while(t--)
    {
        kase++;
        scanf("%d%d",&n,&m);
        double s=0,ans=0;
        for(int i=0;i<n;i++) scanf("%lf",&a[i]),s+=a[i];
        for(int i=0;i<n;i++) cnt[i]=1;
        s=s/(double)m;
        for(int i=0;i<n;i++) ans+=(a[i]-s)*(a[i]-s);
        while(pque.size()) pque.pop();
        for(int i=0;i<n;i++)
        {
            double now=cnt[i]*(a[i]/cnt[i]-s)*(a[i]/cnt[i]-s);
            double nxt=(cnt[i]+1)*(a[i]/(cnt[i]+1)-s)*(a[i]/(cnt[i]+1)-s);
            double inc=now-nxt;
            pque.push(P(inc,i));
        }
        for(int i=0;i<m-n;i++)
        {
            P p=pque.top();
            pque.pop();
            ans-=p.F;
            cnt[p.S]++;
            int x=p.S;
            double now=cnt[x]*(a[x]/cnt[x]-s)*(a[x]/cnt[x]-s);
            double nxt=(cnt[x]+1)*(a[x]/(cnt[x]+1)-s)*(a[x]/(cnt[x]+1)-s);
            double inc=now-nxt;
            pque.push(P(inc,x));
        }
        printf("Case #%d: %.12f\n",kase,ans/m);
    }
    return 0;
}
