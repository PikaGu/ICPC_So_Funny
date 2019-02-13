#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib> 
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int S = 20;

LL qmul(LL x, LL n, LL mod){
    x %= mod, n %= mod;
    LL res = 0;
    while (n){
        if (n & 1){
            res += x;
            if (res >= mod) res -= mod;
        }
        x += x;
        if (x >= mod) x -= mod;
        n >>= 1;
    }
    return res%mod;
}

LL qpow(LL x, LL n, LL mod){
    x %= mod;
    LL res = 1;
    while (n){
        if (n & 1) res = qmul(res, x, mod);
        x = qmul(x, x, mod);
        n >>= 1;
    }
    return res%mod;
}

bool check(LL a, LL n, LL x, LL t){
    LL tmp = qpow(a, x, n);
    LL last = tmp;
    for (int i = 1; i <= t; i++){
        tmp = qmul(tmp, tmp, n);
        if (tmp == 1 && last != 1 && last != n-1) return 1;
        last = tmp;
    }
    return tmp != 1;
}

bool Miller_Rabin(LL n){
    if (n == 2) return 1;
    if (n < 2 || n % 2 == 0) return 0;
    LL x = n-1, t = 0;
    while (x % 2 == 0) x >>= 1, t++;
    for (int i = 0; i < S; i++){
        LL a = rand()%(n-1)+1;
        if (check(a, n, x, t)) return 0;
    }
    return 1;
}

LL gcd(LL a, LL b){
    if (!a) return 1;
    if (a < 0) a = -a;
    return b ? gcd(b, a%b) : a;
}

LL Pollard_rho(LL x, LL c){
    LL i = 1, k = 2;
    LL x0 = rand()%x;
    LL y = x0;
    while (1){
        i++;
        x0 = (qmul(x0, x0, x)+c)%x;
        LL d = gcd(y-x0, x);
        if (d != 1 && d != x) return d;
        if (y == x0) return x;
        if (i == k) y = x0, k += k;
    }
}

LL fac[100];
int tot = 0;
void findfac(LL n){
    if (Miller_Rabin(n)){
        fac[tot++] = n;
        return;
    }
    LL p = n;
    while (p >= n) p = Pollard_rho(p, rand()%(n-1)+1);
    findfac(p), findfac(n/p);
}

int main(){
    freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
    int t;
    LL n;
    scanf("%d", &t);
    while (t--){
        scanf("%lld", &n);
        if (Miller_Rabin(n)){
            printf("Prime\n");
            continue;
        }
        tot = 0;
        findfac(n);
        LL ans = fac[0];
        for (int i = 1; i < tot; i++)
            ans = min(ans, fac[i]);
        printf("%lld\n", ans);
    }
    return 0;
}