#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int mx = 1e6+7;
int a[mx], dp[1<<22];

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	memset(dp, -1, sizeof dp);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		dp[a[i]] = a[i];
	}
	int m = (1<<22)-1;
	for (int i = 0; i <= m; i++){
		if (dp[i] != -1) continue;
		for (int j = 0; j <= 22; j++){
			if (!(i & (1<<j))) continue;
			if (dp[i^(1<<j)] == -1) continue;
			dp[i] = dp[i^(1<<j)];
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", dp[m^a[i]]);
	return 0;
}