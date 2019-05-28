#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 1000 + 5;
vector<LL> ID;
vector<LL> a[maxn];
void dfs(int len,int low,LL hash){
    if (len == 6)return;
    for (int ch = low;ch <=26;ch++){
        LL nxt = hash * 30 + ch;
        ID.push_back(nxt);
        dfs(len + 1,ch + 1,nxt);
    }
}
LL get_hash(char * s,int len){
    LL ret = 0;
    for (int i=0;i<len;i++){
        ret = ret * 30 + s[i] - 'a' + 1;
    }
    return ret;
}
bool exist[2302300];
inline int get_id(LL val){
    return lower_bound(ID.begin(),ID.end(),val) - ID.begin();
}
int gao(int x,int y){
    int ret = 0;
    for (auto & s : a[x]){
        if (exist[s]){
            ret ++;
        }
    }
    return ret;
}
int Ans[maxn][maxn];
int main(){
    int n,m;
    scanf("%d",&n);
    dfs(0,1,0);
    cerr<<ID.size()<<endl;
    sort(ID.begin(),ID.end());
    ID.erase(unique(ID.begin(),ID.end()),ID.end());
    cerr<<ID.size()<<endl;
    for (int i=0;i<n;i++){
        int cnt;
        scanf("%d",&cnt);
        while (cnt--){
            static char temp[10];
            scanf("%s",temp);
            int len = strlen(temp);
            sort(temp,temp+ len);
            a[i].push_back(get_id(get_hash(temp,len)));
        }
    }
    scanf("%d",&m);
    for (int i=0;i<m;i++){
        int cnt;
        scanf("%d",&cnt);
        vector<LL> used(0);
        while (cnt--){
            static char tt[10];
            scanf("%s",tt);
            int len = strlen(tt);
            sort(tt,tt + len);
            for (int mask = 1;mask < (1<< len);mask ++){
                static char st[10];
                int l = 0;
                for (int j = 0;j < len;j ++){
                    if (mask & (1 << j)){
                        st[l++] = tt[j];
                    }
                }
                int id = get_id(get_hash(st,l));
                if (!exist[id]){
                    exist[id] = 1;
                    used.push_back(id);
                }
            }
        }
        for (int j=0;j<n;j++){
            Ans[j][i] = gao(j,i);
        }
        for (int x : used){
            exist[x] = 0;
        }
    }
    for (int i=0;i<n;i++){
        int ans = Ans[i][0];
        int ans_id = 0;
        for (int j=1;j<m;j++){
            int temp_ans = Ans[i][j];
            if (temp_ans > ans){
                ans = temp_ans;
                ans_id = j;
            }
        }
        printf("%d\n",ans_id+1);
    }
    return 0;

}
