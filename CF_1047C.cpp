#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
#define uLL unsigned long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 1e5+7;
const int mxv = 1e7+5e6;
bool vis[mxv+7];
int minprime[mxv+7], cnt[mxv+7];
int prime[mx*10], a[mx], tot = 0;

void init(int n){
    vis[1] = 1;
    for (int i = 2; i <= n; i++){
        if (!vis[i]) {
            minprime[i] = i;
            prime[++tot] = i;
        }
        for (int j = 1; j <= tot && 1ll*i*prime[j] <= n; j++){
            vis[i*prime[j]] = 1;
            minprime[1ll*i*prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
}

int main(){
    init(mxv);
    int n;
    scanf("%d", &n);
    int gcd = 0;
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        gcd = __gcd(gcd, a[i]);
    }
    for (int i = 1; i <= n; i++) a[i] /= gcd;
    for (int i = 1; i <= n; i++){
        if (!vis[a[i]] || a[i] == 1){
            cnt[a[i]]++;
            continue;
        }
        while (a[i] > 1){
            int t = minprime[a[i]];
            cnt[t]++;
            while (a[i] % t == 0 && a[i] != 1) a[i] /= t;
        }
    }
    int ans = 0;
    for (int i = 2; i <= mxv; i++) ans = max(ans, cnt[i]);
    if (!ans) printf("-1\n");
    else printf("%d\n", n-ans);
    return 0;
}