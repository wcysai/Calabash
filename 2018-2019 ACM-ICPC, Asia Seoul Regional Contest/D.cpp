#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int T;
string str;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        cin>>str;
        int sz=(int)str.size();
        string suf1=str.substr(sz-1),suf2=str.substr(sz-2);
        string pre1=str.substr(0,sz-1),pre2=str.substr(0,sz-2);
        if(suf1=="a") str=pre1+"as"; 
        else if(suf1=="i"||suf1=="y") str=pre1+"ios";
        else if(suf1=="l") str=pre1+"les";
        else if(suf1=="n") str=pre1+"anes";
        else if(suf2=="ne") str=pre2+"anes";
        else if(suf1=="o") str=pre1+"os";
        else if(suf1=="r") str=pre1+"res";
        else if(suf1=="t") str=pre1+"tas";
        else if(suf1=="u") str=pre1+"us";
        else if(suf1=="v") str=pre1+"ves";
        else if(suf1=="w") str=pre1+"was";
        else str=str+"us";
        cout<<str<<endl;
    }
    return 0;
}
