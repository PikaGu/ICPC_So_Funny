#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib> 
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int mx = 1010;
int phi[mx], prime[mx];
bool isp[mx];
int tot = 0;

void init(){
	for (int i = 2; i <= 1000; i++){
		if (!isp[i]) prime[tot++] = i, phi[i] = i-1;
		for (int j = 0; j < tot && prime[j]*i <= 1000; j++){
			isp[prime[j]*i] = 1;
			if (i % prime[j] == 0){
				phi[i*prime[j]] = phi[i] * prime[j];
				break;
			}
			phi[i*prime[j]] = phi[i] * (prime[j]-1);
		}
	}
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int t, n, kase = 0;
	scanf("%d", &t);
	init();
	while (t--){
		scanf("%d", &n);
		int sum = 0;
		for (int i = 2; i <= n; i++) sum += phi[i];
		printf("%d %d %d\n", ++kase, n, 3 + 2*sum);
	}
	return 0;
}