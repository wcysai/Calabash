// Created by calabash_boy on 18-6-4.
//SPOJ substring
// calc ans_i=长度=i的所有子串，出现次数最多的一种出现了多少次。
#include<bits/stdc++.h>
#define RIGHT
//RIGHT: parent树的dfs序上主席树，求每个点的Right集合
using namespace std;
const int maxn = 4e5+100;
char s[maxn];
int n;
char t[maxn];
long long ans = 0;
long long ans2 = 0;
struct Palindromic_AutoMaton{
    //basic
    int s[maxn],now;
    int nxt[maxn][26],fail[maxn],l[maxn],last,tot;
    // extension
    int num[maxn];/*节点代表的所有回文串出现次数*/
    void clear(){
        //1节点：奇数长度root 0节点：偶数长度root
        s[0]=l[1]=-1;
        fail[0] = tot = now =1;
        last = l[0]=0;
        memset(nxt[0],0,sizeof nxt[0]);
        memset(nxt[1],0,sizeof nxt[1]);
    }
    Palindromic_AutoMaton(){clear();}
    int newnode(int ll){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        fail[tot]=num[tot]=0;
        l[tot]=ll;
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
            int tt = newnode(l[cur]+2);
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
        ans2 -= tot - 1;
    }
    void init(char* ss){
        while (*ss){
            add(*ss-'a');ss++;
        }
    }
    void init(string str){
        for (int i=0;i<str.size();i++){
            add(str[i]-'a');
        }
    }
    long long query();
}pam;
long long Palindromic_AutoMaton::query(){
    long long ret =1;
    for (int i=2;i<=tot;i++){
        ret = max(ret,1LL*l[i]*num[i]);
    }
    return ret;
}
/*注意需要按l将节点基数排序来拓扑更新parent树*/
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    int flag[maxn*2];
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s-'a');s++;
        }
    }
    void build(){
        int temp = 1;
        for (int i=0;i<n;i++){
            temp = nxt[temp][s[i] - 'a'];
            int now = temp;
            while (now && (flag[now] & 2) == 0){
                flag[now] |= 2;
                now = fa[now];
            }
        }
        temp = 1;
        for (int i=0;i<n;i++){
            temp = nxt[temp][t[i] - 'a'];
            int now = temp;
            while (now && (flag[now] & 1) == 0){
                flag[now] |= 1;
                now = fa[now];
            }
        }
        for (int i=1;i<=cnt;i++){
            if (flag[i] == 3){
                ans2 += l[i] - l[fa[i]];
            }
            if (flag[i] & 1){
                ans += l[i] - l[fa[i]];
            }
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }

}sam;
int main(){
    scanf("%s",s);
    /* calc n must before sam.init()*/
    n = strlen(s);
    pam.init(s);
    pam.build();
    sam.init(s);
    for (int i=0;i<n;i++){
        t[i] = s[i];
    }
    reverse(t,t+n);
    sam.last = 1;
    sam.init(t);
    sam.build();
    cout<<ans - ans2/2<<endl;
    return 0;
}
// accad
