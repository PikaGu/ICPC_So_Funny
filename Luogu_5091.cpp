#include <bits/stdc++.h>
#include <unordered_map>
#define LL long long
#define uLL unsigned long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 2e7+7;
char b[mx];

int euler(int n){
    int ans = n;
    for (int i = 2; i*i <= n; i++){
        if (n % i == 0) ans = ans / i * (i-1);
        while (n % i == 0) n /= i;
        if (n == 1) break;
    }
    if (n > 1) ans = ans / n * (n-1);
    return ans;
}

LL qpow(LL x, LL n, LL mod){
    LL ans = 1;
    while (n){
        if (n & 1) ans = ans*x%mod;
        x = x*x%mod;
        n >>= 1;
    }
    return ans;
}

int main(){
    int a, m;
    scanf("%d%d", &a, &m);
    int phi = euler(m);
    scanf("%s", b);
    int len = strlen(b);
    LL ans = 0;
    bool ok = 0;
    for (int i = 0; i < len; i++){
        ans = ans * 10 + b[i]-'0';
        if (ans >= phi){
            ans %= phi;
            ok = 1;
        }
    }
    if (ok) ans += phi;
    ans = qpow(a, ans, m);
    printf("%lld\n", ans);
    return 0;
}