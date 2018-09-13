#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
const int HASH_CNT = 1;
typedef unsigned long long ULL;
ULL Seed_Pool[]={911,146527,19260817,29};
ULL Mod_Pool[]={29123,998244353,1000000009,986608921};
int n;
map<int,int>  ans[maxn];
map<int,int> cnt;
ULL bas[maxn];
struct Hash_1D{
    ULL Seed,Mod;
    //ULL bas[maxn];
    ULL sum[maxn*2];
    void init(char * sss,int n,int seedIndex,int modIndex){
        Seed = Seed_Pool[seedIndex];
        Mod = Mod_Pool[modIndex];
        //bas[0]=1;
        //for (int i=1;i<=n;i++){
        //    bas[i] = bas[i-1]*Seed%Mod;
        //}
        for (int i=1;i<=n;i++){
            sum[i] = (sum[i-1]*Seed+sss[i]-'a'+1);
        }
    }

    ULL getHash(int l,int r){
        return (sum[r]-sum[l-1]*bas[r-l+1]);
    }
}hasher1[HASH_CNT],hasher2[HASH_CNT];
char s[maxn],t[maxn];
char ss[maxn*2],tt[maxn];
int nxt[maxn];
int len;
int fa[maxn];
int find(int x){
    return fa[x] == x?x:fa[x] = find(fa[x]);
}
inline bool _is_same(int x){
    for (int i=0;i<HASH_CNT;i++){
        if (hasher1[i].getHash(x,x+n-1) != hasher2[i].getHash(1,n)){
            return false;
        }
    }
    return true;
}
void work(int st){
    int x = st;
    int now = 1;
    /*if (st == nxt[st]){
        puts("-1");
        exit(0);
    }*/
    while (nxt[x] != st){
        ss[now++] = s[x];
        x = nxt[x];
    }
    ss[now++] = s[x];
    for (int i=1;i<now;i++){
        ss[now+i-1] = ss[i];
    }
    n = (now-1);
    hasher1[0].init(ss,2*n,1,1);
    now =1;
    x = st;
    while (nxt[x] != st){
        tt [now++] = t[x];
        x = nxt[x];
    }
    tt[now++] = t[x];
    hasher2[0].init(tt,n,1,1);
    
    ss[2*n+1] = '\0';
    tt[n+1] = '\0';
    //cout<<ss+1<<endl<<tt+1<<endl;
    int now_cnt = cnt[n];
    cnt[n]++;
    bool succ = false;
    for (int i=1;i<=n;i++){
        if (_is_same(i)){
            int x = i-1;
            succ = true;
            if (ans[n][x] == now_cnt){
                ans[n][x] ++;
            }
        }
    }
    if (!succ){
        puts("-1");
        exit(0);
    }
}
int ans_cnt[maxn];
int label[maxn];
int main(){
    bas[0]=1;
    for (int i=1;i<=1000005;i++){
        bas[i] = bas[i-1]* Seed_Pool[1] ;
    }
    scanf("%s",s+1);
    scanf("%s",t+1);
    len = strlen(s+1);
    if (s[1]!=t[1] || s[len] != t[len]){
        puts("-1");
        return 0;
    }
    if (len == 2){
        puts("0");
        return 0;
    }
    int half_len = len/2;
    for (int i=1;i<=half_len;i++){
        fa[i] = i;
        fa[i+half_len]=i+half_len;
        nxt[i] = i*2-1;
        nxt[i+ half_len] = i*2;
//        nxt[i*2-1] = i;
//        nxt[i*2] = i+half_len;
    }
    for (int i=2;i<len;i++){
        int fi = find(i);
        int fj = find(nxt[i]);
        fa[fj] = fi;
    }


    for (int i=2;i<len;i++){
        if (i != find(i))continue;
        work(i);
    }
    int tot_cnt = 0;
    for (auto item : cnt){
        int now_len = item.first;
        int now_cnt = item.second;
        tot_cnt ++;
        for (auto item2: ans[now_len]){
            if (item2.second == now_cnt){
                int x = item2.first;
                for (int i=x;i <maxn;i+=now_len){
                    if (label[i] != tot_cnt){
                        label[i] = tot_cnt;
                        ans_cnt[i] ++;
                    }
                }
            }
        }
    }
    int res =-1;
    for (int i=0;i<maxn;i++){
        if (ans_cnt[i] == tot_cnt && tot_cnt ){
            printf("%d\n",i);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
/*
 * petrozavodsk
poztsvoedark
nxt[1]=1
nxt[2]=7
nxt[3]=2
nxt[4]=8
nxt[5]=3
nxt[6]=9
nxt[7]=4
nxt[8]=10
nxt[9]=5
nxt[10]=11
nxt[11]=6
nxt[12]=12
6
zootearvdszootearvds
vdszootear
7
 */
