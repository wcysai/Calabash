#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,p[MAXN];
int cnt[MAXN];
map<int,int> mp;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    int maxi=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i]>maxi) maxi=p[i];
        mp[p[i]]++;
    }
    ll ans=1LL*mp[maxi]*maxi;
    for(int i=1;i<=n;i++)
    {
        if(!p[i]) continue;
        if(i!=1)
        {
            mp[p[i]]--; if(!mp[p[i]]) mp.erase(p[i]); mp[p[i]-1]++;
            mp[p[i-1]]--; if(!mp[p[i-1]]) mp.erase(p[i-1]); mp[p[i-1]+1]++;
            auto it=mp.end(); it--;
            ans=min(ans,1LL*it->F*it->S);
            mp[p[i]]++; mp[p[i]-1]--; if(!mp[p[i]-1]) mp.erase(p[i]-1);
            mp[p[i-1]]++; mp[p[i-1]+1]--; if(!mp[p[i-1]+1]) mp.erase(p[i-1]+1);
        }
        if(i!=n)
        {
            mp[p[i]]--; mp[p[i]-1]++; if(!mp[p[i]]) mp.erase(p[i]);
            mp[p[i+1]]--; mp[p[i+1]+1]++; if(!mp[p[i+1]]) mp.erase(p[i+1]);
            auto it=mp.end(); it--;
            ans=min(ans,1LL*it->F*it->S);
            mp[p[i]]++; mp[p[i]-1]--; if(!mp[p[i]-1]) mp.erase(p[i]-1);
            mp[p[i+1]]++; mp[p[i+1]+1]--; if(!mp[p[i+1]+1]) mp.erase(p[i+1]+1);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
