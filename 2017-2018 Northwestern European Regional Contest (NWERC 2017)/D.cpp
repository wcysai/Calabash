//
// Created by sy-chen on 18-5-31.
//

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
typedef long long LL;
map<string,int>idd;int iddcnt;
map<string,string> f;
int m,n;
int yesCnt[maxn],noCnt[maxn];
string a[30];
string ans[30];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a[i];
        if(!idd[a[i]]){
            idd[a[i]]=++iddcnt;
        }
    }
    cin>>m;
    for (int i=0;i<m;i++){
        string d,e,s;
        cin>>d>>e>>s;
        f[d]=e;
        if(!idd[d])idd[d]=++iddcnt;
//        if(!idd[e])idd[e]=++iddcnt;
        if(s[0]=='c'){
            //correct
            yesCnt[idd[d]]++;
        }else{
            //incorrect
            noCnt[idd[d]]++;
        }
    }
    LL yesAns=1;
    LL totAns=1;
    for (int i=0;i<n;i++){
        int id = idd[a[i]];
     //   cout<<id<<" "<<yesCnt[id]<<" "<<noCnt[id]<<endl;
        yesAns*=yesCnt[id];
        totAns*=(yesCnt[id]+noCnt[id]);
    }
    if(totAns==1){
        for (int i=0;i<n;i++){
            cout<<f[a[i]]<<" ";
        }
        if(yesAns==1){
            cout<<"\ncorrect\n";
        }else{
            cout<<"\nincorrect\n";
        }
    }else{
        cout<<yesAns<<" correct\n";
        cout<<totAns-yesAns<<" incorrect\n";
//        printf("%I64d correct\n",yesAns);
//        printf("%I64d incorrect\n",totAns-yesAns);
    }
    return 0;
}
/*
7
als mollen mollen mollen mollen mollen mollen
 4
 als when correct
 mollen moles correct
 mollen destroy correct
 mollen mills incorrect

 */
