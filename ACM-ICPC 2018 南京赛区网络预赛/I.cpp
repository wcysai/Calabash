//
// Created by calabash_boy on 18-6-4.
// BZOJ 3676
// calc max(len(t)*cnt(t)) t为s回文子串，cnt(t)=t出现次数
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6+100;
const int MOD = 1e9+7;
int bas[maxn];
struct Palindromic_AutoMaton{
    //basic
    int s[maxn],now;
    int nxt[maxn][10],fail[maxn],l[maxn],last,tot;
    int val[maxn],val2[maxn];
    int last_ch[maxn];
    // extension
    int num[maxn];/*节点代表的所有回文串出现次数*/
    bool used[maxn];
    void clear(){
        //1节点：奇数长度root 0节点：偶数长度root
        s[0]=l[1]=-1;
        fail[0] = tot = now =1;
        last = l[0]=0;
        val[0] = val2[0] = 0;
        val[1] = val2[1] = 0;
        memset(nxt[0],0,sizeof nxt[0]);
        memset(nxt[1],0,sizeof nxt[1]);
    }
    Palindromic_AutoMaton(){clear();}
    int newnode(int pre,int ll,int now){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        fail[tot]=num[tot]=0;
        l[tot]=ll;
        last_ch[tot] = now;
        if (ll&1){
            val[tot] = (10LL*val[pre]%MOD + last_ch[tot])%MOD;
            val2[tot] = (1LL*bas[l[tot]/2-1]*last_ch[tot]%MOD + val2[pre])%MOD;
        }else{
            val[tot] = (10LL*val[pre]%MOD + last_ch[tot])%MOD;
            val2[tot] = (1LL*bas[l[tot]/2-1]*last_ch[tot]%MOD + val2[pre])%MOD;
        }
        return tot;
    }
    int get_fail(int x){
        while (s[now-l[x]-2]!=s[now-1])x = fail[x];
        return x;
    }
    void add(int ch){
        s[now++] = ch;
        int cur = get_fail(last);
        if(!nxt[cur][ch]){
            int tt = newnode(cur,l[cur]+2,ch);
            fail[tt] = nxt[get_fail(fail[cur])][ch];
            nxt[cur][ch] = tt;
        }
        last = nxt[cur][ch];num[last]++;
    }
    void build(){
        //fail[i]<i，拓扑更新可以单调扫描。
        for (int i=tot;i>=2;i--){
            num[fail[i]]+=num[i];
        }
        num[0]=num[1]=0;
    }
    void init(char* ss){
        while (*ss){
            add(*ss-'0');
            ss++;
        }
    }
    void debug(){
        for (int i=0;i<=tot;i++){
            printf("%d l = %d val= %d\n",i,l[i],val[i]);
            for (int j=0;j<10;j++){
                if (nxt[i][j]){
                    printf("nxt[%d][%d]=%d\n",i,j,nxt[i][j]);
                }
            }
        }
    }
    void init(string str){
        for (int i=0;i<str.size();i++){
            add(str[i]-'0');
        }
    }
    long long query();
}pam;
long long Palindromic_AutoMaton::query(){
    long long ret =0;
    for (int i=2;i<=tot;i++){
        //cout<<i<<": "<<val[i]<<" "<<val2[i]<<" "<<l[i]<<" fa = "<<fail[i]<<endl;
        ret = (ret + 1LL*val2[i] * bas[(l[i]+1)/2]%MOD + val[i])%MOD;
    }
    return ret;
}
char s[maxn];
void init(){
    bas[0] = 1;
    for (int i=1;i<maxn;i++){
        bas[i] = 1LL*bas[i-1]* 10 %MOD;
    }
}
int main(){
    init();
    scanf("%s",s);
    pam.init(s);
//    pam.build(0);
    //pam.debug();
    printf("%lld\n",pam.query());
    return 0;
}
