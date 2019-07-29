#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
P a[MAXN];
int s[MAXN],s1[MAXN],s2[MAXN];
int ans1,ans2;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
    for(int i=1;i<=n;i++) {s[a[i].x]++; s[a[i].y]--;}
    for(int i=1;i<=100000;i++)
    {
        s[i]+=s[i-1];
        ans2=max(ans2,s[i]);
    }
    for(int i=1;i<=n;i++)
    {
        s1[a[i].x]++;
        s2[a[i].y-1]++;
    }
    for(int i=1;i<=100000;i++) s2[i]+=s2[i-1];
    for(int i=100000;i>=1;i--) s1[i]+=s1[i+1];
    for(int i=1;i<=n;i++)
    {
        int cur=n-s2[a[i].x-1]-s1[a[i].y];
        ans1=max(ans1,cur);
    }
    printf("%d %d\n",ans1,ans2);
    return 0;
}
