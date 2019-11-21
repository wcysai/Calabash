#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
vector<P> v;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        v.push_back(P(a[i],i));
    }
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++)
    {
        if(v[i].S!=i+1)
        {
            int now=i;
            while(now+1<n&&v[now+1].F==v[i].F) now++;
            int l=i+1,r=v[now].S;
            //printf("%d %d\n",l,r);
            reverse(a+l,a+r+1);
            for(int j=2;j<=n;j++)
            {
                if(a[j]<a[j-1])
                {
                    puts("impossible");
                    return 0;
                }
            }
            printf("%d %d\n",l,r);
            return 0;
        }
    }
    printf("1 1\n");
    return 0;
}
