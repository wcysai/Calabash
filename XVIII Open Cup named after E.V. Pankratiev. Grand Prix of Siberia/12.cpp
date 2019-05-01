#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+100;
typedef unsigned long long ULL;
const ULL Seed = 146527;
const ULL Mod = 998244353;
ULL base[maxn];
struct Hash{
    ULL sum[maxn];
    void init(char *s,int n){
        for (int i=1;i<=n;i++){
            sum[i] = sum[i-1] * Seed % Mod + s[i];
            sum[i] %= Mod;
        }
    }
    ULL get(int l,int r){
        return (sum[r] - sum[l-1] * base[r -l + 1] % Mod + Mod) % Mod;
    }
}hx,hy,hz;
char x[maxn],y[maxn],z[maxn];
int find_first(char *z,int lz,Hash&hz,char *x,int lx,Hash &hx){
    if (lx > lz)return -1;
    ULL hash_x = hx.get(1,lx);
    for (int i=lx;i<=lz;i++){
        ULL hash_z = hz.get(i- lx + 1,i);
        if (hash_z == hash_x)return i;
    }
    return -1;
}
int find_last(char *z,int lz,Hash&hz,char *x,int lx,Hash &hx){
    if (lx > lz)return -1;
    ULL hash_x = hx.get(1,lx);
    for (int i=lz;i>=lx;i--){
        ULL hash_z = hz.get(i-lx+1,i);
        if (hash_z == hash_x)return i - lx + 1;
    }

    return -1;
}
int main(){
    base[0] = 1;
    for (int i=1;i<maxn;i++){
        base[i] = base[i-1] * Seed % Mod;
    }
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%s%s%s",z+1,x+1,y+1);
        int lz = strlen(z+1);
        int lx = strlen(x+1);
        int ly = strlen(y+1);
        hx.init(x,lx);
        hy.init(y,ly);
        hz.init(z,lz);
        int first_x = find_first(z,lz,hz,x,lx,hx);
        int last_y = find_last(z,lz,hz,y,ly,hy);
        if (first_x != -1 && last_y != -1 && first_x < last_y){
            puts("YES");
            continue;
        }
        int first_y = find_first(z,lz,hz,y,ly,hy);
        int last_x = find_last(z,lz,hz,x,lx,hx);
        if (first_y != -1 && last_x != -1 && first_y < last_x){
            puts("YES");
            continue;
        }
        puts("NO");
    }
    return 0;
}
