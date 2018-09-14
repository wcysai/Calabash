//
// Created by sy-chen on 18-5-20.
//
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int dir[MAXN],p;
int main()
{
    int lb=0,rb=0,upper=0,lower=0,x=0,y=0,d=1;//1: right 2:left 3:up 4:down
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d%d",&p,&dir[i]);
    for(int i=0;i<n;i++)
    {
        //printf("%d %d\n",x,y);
        if(d==1)
        {
            printf("%d ",rb+1-x);
            x=rb+1;
            rb++;
        }
        else if(d==2)
        {
            printf("%d ",x-lb+1);
            x=lb-1;
            lb--;
        }
        else if(d==3)
        {
            printf("%d ",upper+1-y);
            y=upper+1;
            upper++;
        }
        else
        {
            printf("%d ",y-lower+1);
            y=lower-1;
            lower--;
        }
        if(dir[i]==1)
        {
            if(d==1) d=3;
            else if(d==2) d=4;
            else if(d==3) d=2;
            else d=1;
        }
        else
        {
            if(d==1) d=4;
            else if(d==2) d=3;
            else if(d==3) d=1;
            else d=2;
        }
    }
    return 0;
}
