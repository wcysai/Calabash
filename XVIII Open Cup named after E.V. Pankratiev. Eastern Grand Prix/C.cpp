//
// Created by calabash on 10/31/18.
//
/* bad*/
#include <bits/stdc++.h>
using namespace std;
const int maxn =105;
typedef long long ll;
ll f[4][4][26][26][26][26];
char s[4][maxn];
int len[4];
ll sumf[maxn][26][26];
void updatef(int I,int J,vector<pair<int,int> > & nums){
    for (int i=1;i<nums.size();i++){
        int x = nums[i].first;
        int y = nums[i].second;
        for (int xx =0;xx<26;xx++)for (int yy=0;yy<26;yy++){
            f[I][J][xx][yy][x][y] += sumf[i-1][xx][yy];
            sumf[i][xx][yy] = sumf[i-1][xx][yy];
        }
        sumf[i][x][y] ++;
        if(i!=1)f[I][J][nums[i-1].first][nums[i-1].second][x][y] --;
    }
}
int main(){
    for (int i=0;i<4;i++){
        scanf("%s",&s[i][0]);
        len[i] = strlen(&s[i][0]);
    }
    for (int i=0;i<4;i++)for (int j=0;j<4;j++){
        if (i <= j)continue;
        int ltop = len[i];
        int lbot = len[j];
        for (int k=0;k<ltop;k++){
            vector<pair<int,int> > nums(1,{-1,-1});
            int l = k;
            int r = min(ltop,lbot+ k);
            for (int o=l;o<r;o++){
                int c1= s[i][o];
                int c2 = s[j][o-k];
                nums.push_back({c1-'a',c2 - 'a'});
            }
            updatef(i,j,nums);
        }
        for (int k=1;k<lbot;k++){
            vector<pair<int,int> > nums(1,{-1,-1});
            int l = 0;
            int r = min(ltop,lbot-k);
            for (int o=l;o<r;o++){
                int c1 = s[i][o];
                int c2 = s[j][o+k];
                nums.push_back({c1-'a',c2 - 'a'});
            }
            updatef(i,j,nums);
        }
    }
    ll ans =0;
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (i == j)continue;
            for (int k=0;k<4;k++){
                if (k == i || k == j)continue;
                int l = 1 + 2 + 3  - i - j - k;
                for (int x = 0;x < 26;x++)for (int y=0;y<26;y++)for(int xx=0;xx<26;xx++)for(int yy=0;yy<26;yy++){
                    ans += 1ll * max(f[i][j][xx][yy][x][y],f[j][i][yy][xx][y][x]) * max(f[k][l][x][xx][y][yy],f[l][k][xx][x][yy][y]);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
/*
aaa
axa
aya
aza

aaaa
abba
baab
bbbb

 */
