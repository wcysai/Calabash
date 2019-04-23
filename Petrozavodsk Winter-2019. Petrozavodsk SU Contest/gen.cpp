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
int n,k,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    int n=99999;
    k=wcy()%(2*n+1);
    printf("%d %d\n",n,k);
    for(int i=0;i<n;i++)
    {
        int x=wcy()%52;
        if(x<26) printf("%c",'A'+x); else printf("%c",'a'+(x-26));
    }
    puts("");
    return 0;
}

