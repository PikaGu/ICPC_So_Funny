#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib> 
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int mx = 1000;
int sta[mx], num[mx];
LL dp[10][mx][mx];

int getnum(int n){
	int res = 0;
	while (n){
		res += n & 1;
		n >>= 1;
	}
	return res;
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int n, k;
	scanf("%d%d", &n, &k);
	int cnt = 0;
	for (int i = 0; i < (1<<n); i++){
		if (!(i & (i << 1))){
			sta[cnt] = i;
			num[cnt] = getnum(i);
			dp[1][num[cnt]][i] = 1;
			cnt++;
		}
	}
	for (int i = 2; i <= n; i++){
		for (int j = 0; j <= k; j++){
			for (int s = 0; s < cnt; s++){
				if (num[s] > j) continue;
				for (int p = 0; p < cnt; p++){
					if (sta[s] & sta[p]) continue;
					if ((sta[s] >> 1) & sta[p]) continue;
					if (sta[s] & (sta[p] >> 1)) continue;
					dp[i][j][sta[s]] += dp[i-1][j-num[s]][sta[p]];
				}
			}
		}
	}
	LL ans = 0;
	for (int i = 0; i < cnt; i++)
		ans += dp[n][k][sta[i]];
	printf("%lld\n", ans);
	return 0;
}