#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mod = 1e9+7;
const int mx = 1e6+7;
LL inv[mx], fac[mx];
int a, b;

void init(int m){
    fac[0] = 1;
    for (int i = 1; i <= m; i++) fac[i] = fac[i-1]*i%mod;
    inv[1] = 1;
    for (int i = 2; i <= m; i++) inv[i] = mod-(mod/i)*inv[mod%i]%mod;
    inv[0] = 1;
    for (int i = 1; i <= m; i++) inv[i] = inv[i]*inv[i-1]%mod;
}

LL C(int n, int m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}

bool check(int k){
    while (k){
        if (k % 10 != a && k % 10 != b) return 0;
        k /= 10;
    }
    return 1;
}

int main(){
    int n;
    scanf("%d%d%d", &a, &b, &n);
    init(n);
    LL ans = 0;
    for (int i = 0; i <= n; i++){
        int k = i*a+(n-i)*b;
        if (!check(k)) continue;
        ans = (ans + C(n, min(i, n-i)))%mod;
    }
    printf("%lld\n", ans);
    return 0;
}