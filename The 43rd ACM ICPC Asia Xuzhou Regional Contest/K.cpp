#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,a[MAXN];
int ss1,ee1,ss2,ee2;
P findans(bool dir1,bool dir2)
{
    set<int> v1,v2; v1.clear();v2.clear();
    int s1=ss1,s2=ss2,e1=ee1,e2=ee2;
    if(dir1)
    {
        while(s1!=e1)
        {
            v1.insert(s1);
            s1=s1%n+1;
        }
    }
    else
    {
        while(s1!=e1)
        {
            int to=s1-1;
            if(to<=0) to+=n;
            v1.insert(to);
            s1=to;
        }
    }
    if(dir2)
    {
        while(s2!=e2)
        {
            v2.insert(s2);
            s2=s2%n+1;
        }
    }
    else
    {
        while(s2!=e2)
        {
            int to=s2-1;
            if(to<=0) to+=n;
            v2.insert(to);
            s2=to;
        }
    }
    int res1=0,res2=0;
    for(auto v:v1) if(v2.count(v)) res1+=3*a[v]; else res1+=a[v];
    for(auto v:v2) if(v1.count(v)) res2+=3*a[v]; else res2+=a[v];
    return P(res1,res2);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        scanf("%d%d%d%d",&ss1,&ee1,&ss2,&ee2);
        P res1,res2,res3,res4;
        res1=findans(true,true);
        res2=findans(true,false);
        res3=findans(false,true);
        res4=findans(false,false);
        printf("%d %d\n",res1.F,res1.S);
        printf("%d %d\n",res2.F,res2.S);
        printf("%d %d\n",res3.F,res3.S);
        printf("%d %d\n",res4.F,res4.S);
        double p,q;
        if(res1.F-res2.F-res3.F+res4.F==0) p=0; else p=(double)(res4.F-res3.F)/(res1.F-res2.F-res3.F+res4.F);
        if(res1.S-res2.S-res3.S+res4.S==0) q=0; else q=(double)(res4.S-res2.S)/(res1.S-res2.S-res3.S+res4.S);
        double ans1,ans2;
        bool mixed=false;
        if(0<p&&p<1&&0<q&&q<1)
        {
            mixed=true;
            ans1=p*q*res1.F+p*(1-q)*res2.F+(1-p)*q*res3.F+(1-p)*(1-q)*res4.F;
            ans2=p*q*res1.S+p*(1-q)*res2.S+(1-p)*q*res3.S+(1-p)*(1-q)*res4.S;
        }
        else
        {
            ans1=INF;ans2=INF;
        }
        if(!mixed)
        {
            if(res1.F<=res2.F&&res1.S<=res2.S&&res1.F<=res3.F&&res1.S<=res3.S&&res1.F<=ans1&&res1.S<=ans2&&(res1.F<ans1||res1.S<ans2)) {ans1=res1.F; ans2=res1.S;}
            if(res2.F<=res1.F&&res2.S<=res1.S&&res2.F<=res4.F&&res2.S<=res4.S&&res2.F<=ans1&&res2.S<=ans2&&(res2.F<ans1||res2.S<ans2)) {ans1=res2.F; ans2=res2.S;}
            if(res3.F<=res1.F&&res3.S<=res1.S&&res3.F<=res4.F&&res3.S<=res3.S&&res3.F<=ans1&&res3.S<=ans2&&(res3.F<ans1||res3.S<ans2)) {ans1=res3.F; ans2=res3.S;}
            if(res4.F<=res2.F&&res4.S<=res2.S&&res4.F<=res3.F&&res4.S<=res3.S&&res4.F<=ans1&&res4.S<=ans2&&(res4.F<ans1||res4.S<ans2)) {ans1=res4.F; ans2=res4.S;}
        }
        printf("%.10lf %.10lf\n",ans1,ans2);
    }
    return 0;
}

