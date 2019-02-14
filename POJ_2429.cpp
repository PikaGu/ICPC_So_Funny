#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

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
	LL res = 1;
	x %= mod;
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

const int S = 20;
bool Miller_Rabin(LL n){
	if (n == 2) return 1;
	if (n < 2 || n % 2 == 0) return 0;
	LL x = n-1, t = 0;
	while (x % 2 == 0) x >>= 1ll, t++;
	if (t < 1 || x % 2 == 0) return 1;
	for (int i = 0; i < S; i++){
		LL a = rand()%(n-1)+1;
		if (check(a, n, x, t)) return 0;
	}
	return 1;
}

LL gcd(LL a, LL b){
	if (!a) return 1;
	if (a < 0) a = -a;
	while (b){
		LL t = a % b;
		a = b;
		b = t;
	}
	return a;
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

vector<LL> fac, f;
void findfac(LL n){
	if (n == 1) return;
	if (Miller_Rabin(n)){
		fac.push_back(n);
		return;
	}
	LL p = n;
	while (p >= n) p = Pollard_rho(p, rand()%(n-1)+1);
	findfac(p), findfac(n/p);
}

LL dfs(int cnt, LL res, LL m){
	if (res > m) return 0;
	if (cnt == (int)f.size() || res == m) return res;
	LL a = dfs(cnt+1, res, m);
	if (res * f[cnt] > m) return a;
	LL b = dfs(cnt+1, res*f[cnt], m);
	return max(a, b);
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	LL a, b, g, l;
	while (scanf("%lld%lld", &g, &l) == 2){
		f.clear(), fac.clear();
		l /= g;
		findfac(l);
		LL tmp = l;
		for (int i = 0; i < (int)fac.size(); i++){
			LL res = 1;
			while (tmp % fac[i] == 0)
				res *= fac[i], tmp /= fac[i];
			if (res != 1) f.push_back(res);
		}
		a = dfs(0, 1, sqrt(l));
		b = l/a;
		printf("%lld %lld\n", a*g, b*g);
	}
	return 0;
}