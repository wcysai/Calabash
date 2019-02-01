#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,row[MAXN],col[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        bool f=true;
        int s1=0,s2=0;
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&row[i]);
            if(row[i]==0) f=false;
            s1+=row[i];
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&col[i]);
            if(col[i]==0) f=false;
            s2+=col[i];
        }
        if(s1!=s2) f=false;
        if(s1<2*n-1||(n>=2&&s1>4*n-4)) f=false;
        if(!f)
        {
            puts("0");
            continue;
        }
        int lastl=1,lastr=1,ans=0;
        for(int i=1;i<=n;i++)
        {
            int l=lastl,r=lastr;
            while(col[l]==1&&l<n) l++;
            if(l>=lastr)
            {
                r=lastl+row[i]-1;
                if(l>r) {f=false; break;}
                if(r>n) {f=false; break;}
                for(int j=lastl;j<=r;j++) col[j]--;
                if(l!=r) ans++;
                lastl=l;lastr=r;
            }
            else
            {
                int rem=row[i]-(l-lastl+1);
                if(rem<1) {f=false; break;}
                r=lastr+rem-1;
                if(r>n) {f=false; break;}
                for(int j=lastl;j<=l;j++) col[j]--;
                for(int j=lastr;j<=r;j++) col[j]--;
                lastl=l;lastr=r;
            }
        }
        for(int i=1;i<=n;i++) if(col[i]) f=false;
        if(!f) {puts("0"); continue;}
        ans=pow_mod(2,ans); printf("%d\n",ans);
    }
    return 0;
}

