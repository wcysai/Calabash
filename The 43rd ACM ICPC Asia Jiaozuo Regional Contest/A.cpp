#include<bits/stdc++.h>
int T,cnt;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        int a,b,c,d;
        cnt=0;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(a) cnt++;
        if(b) cnt++;
        if(c) cnt++;
        if(d) cnt++;
        if(cnt==0) puts("Typically Otaku");
        else if(cnt==1) puts("Eye-opener");
        else if(cnt==2) puts("Young Traveller");
        else if(cnt==3) puts("Excellent Traveller");
        else puts("Contemporary Xu Xiake");
    }
    return 0;
}
