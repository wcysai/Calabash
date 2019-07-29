#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,k,a[MAXN],d[MAXN],c[MAXN],q[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    n=500; k=500;
    printf("%d %d\n",n,k);
    for(int i=1;i<=n;i++)
    {
        a[i]=wcy()%INF+1;
        c[i]=wcy()%INF+1;
        d[i]=(a[i]-1)/c[i]+1;
    }
    for(int i=1;i<=k;i++) q[i]=wcy()%20000+1;
    for(int i=1;i<=n;i++) printf("%d %d %d\n",a[i],d[i],c[i]);
    for(int i=1;i<=k;i++) printf("%d\n",q[i]);
    return 0;
}

