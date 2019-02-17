#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

int phi(int n){
	int ans = n;
	for (int i = 2; i*i <= n; i++){
		if (n % i == 0) ans = ans / i * (i-1);
		while(n % i == 0) n /= i;
		if (n == 1) break;
	}
	if (n > 1) ans = ans / n * (n-1);
	return ans;
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int n;
	while (scanf("%d", &n) == 1){
		printf("%d\n", phi(n-1));
	}
	return 0;
}