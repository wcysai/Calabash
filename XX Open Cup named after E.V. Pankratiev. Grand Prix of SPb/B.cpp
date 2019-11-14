#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t;
string str;
int a[105],pos;
int main()
{
    cin>>str;
    scanf("%d",&t);
    while(t--)
    {
        int x=0;
        for(int i=0;i<64;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]) x^=i;
        }
        if(str=="Mia")
        {
            scanf("%d",&pos);
            pos--;
            a[x^pos]^=1;
            for(int i=0;i<64;i++)
            {
                printf("%d ",a[i]);
                if(i%8==7) {printf("\n"); fflush(stdout);}
            }
            printf("---\n");
            fflush(stdout);
        }
        else
        {
            cin>>str;
            printf("%d\n",x+1);
            fflush(stdout);
        }
    }
    return 0;
}
