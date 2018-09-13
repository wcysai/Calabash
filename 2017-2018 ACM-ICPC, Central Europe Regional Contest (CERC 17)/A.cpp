//
// Created by calabash_boy on 18-5-22.
//
#include<bits/stdc++.h>
#define MP(x,y) make_pair(x,y)
using namespace std;
const int maxn = 150;
char s[maxn][20];
int dis[maxn];
int cnt[maxn];
int r,n,R;
int ltot,rtot;
pair<int,int> rk[5]={MP(4,6),MP(2,8),MP(0,10),MP(5,5),MP(1,9)};
void work(int id,int ch){
    //cout<<id<<endl;
    for (int i=0;i<5;i++){
        auto tmp = rk[i];
        if(s[id][tmp.first]=='-'||s[id][tmp.second]=='-'){
            cnt[id]--;
            if(s[id][tmp.first]=='-'&&s[id][tmp.second]=='-'){
                if(ltot<rtot){
                    if(i!=3)
                        rtot--;
                    s[id][tmp.second]=ch;
                }else{
                    if(i!=3)
                        ltot--;
                    s[id][tmp.first]=ch;
                }
            }else{
                if(s[id][tmp.first]=='-'){
                    if(i!=3)
                        ltot--;
                    s[id][tmp.first]=ch;
                }else{
                    if(i!=3)
                        rtot--;
                    s[id][tmp.second]=ch;
                }
            }
            return;
        }
    }
}
void work1(int ch){
    int id = 2;
    if(cnt[r/2+3]>cnt[2])id =r/2+3;
  //  cout<<id<<endl;
    work(id,ch);
}
void work2(int ch){
    int id=2;
    for (int i=2;i<=R;i++){
        if(i==1||i==r/2+2||i==R)continue;
        if(cnt[i]>cnt[id]){
            id = i;
        }else if (cnt[i]==cnt[id]&&dis[i]<dis[id]){
            id =i;
        }
    }
    work(id,ch);
}
int main(){
    cin>>r>>n;
    R = r+3;
    for (int i=1;i<=R;i++){
        scanf("%s",s+i);
        for (int j=0;j<11;j++) {
            if (s[i][j] == '-') {
                if (j < 5)ltot++;
                else if (j > 5)rtot++;
                cnt[i]++;
            }
        }
        if(i==1||i==R||i==r/2+2)continue;
        dis[i] = min(abs(i-1),min(abs(i-r/2-2),abs(i-R)));
    }
    for (int i=0;i<n;i++){
        if(cnt[2]||cnt[r/2+3]){
            work1(i+'a');
        }else{
            work2(i+'a');
        }
    }
    for (int i=1;i<=R;i++){
        printf("%s\n",s+i);
    }
    return 0;
}
