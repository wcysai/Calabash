//
// Created by calabash on 11/2/18.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,m,k;
void work_m(){
    LL nn = n-m;
    LL now = 1;
   // cout<<nn<<" "<<now<<endl;
    for (int i=0;i<m;i++){
        nn ++;
        now = (now + k -2)%nn +2;

      //  cout<<nn<<" "<<now<<endl;
    }
    cout<<now-1<<endl;
}
void work_k(){
    LL nn = n-m;
    LL now = 1;
    while (nn != n){
        LL cnt = max(0LL,min(n - nn,(nn-now-k+1) / k));
        now = now + k * cnt;
        nn += cnt;
       // cout<<cnt<<" "<<nn<<" "<<now<<endl;
        if (nn == n)break;
        nn ++;
        now = (now + k-2)% nn +2;

    }
    cout<<now-1<<endl;
}
int main(){
    int T;
    scanf("%d",&T);
    for (int Case = 1;Case <= T;Case ++){
        printf("Case #%d: ",Case);
        cin>>n>>m>>k;
        if ( k == 1){
            cout<<m<<endl;
            continue;
        }
        if (m < k){
            work_m();
        }else{
            work_k();
        }
    }
    return 0;
}
/*
 20
Case #1: 10 1 2
6
Case #2: 10 2 2
4
Case #3: 10 3 2
2
Case #4: 10 4 2
4
