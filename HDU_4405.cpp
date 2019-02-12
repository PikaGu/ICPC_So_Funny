#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int mx = 1e5+7;
int vis[mx];
double dp[mx];

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int n, m;
	while (scanf("%d%d", &n, &m) == 2 && n) {
		memset(dp, 0, sizeof dp);
	    for (int i = 1; i <= m; i++){
	    	int a, b;
	    	scanf("%d%d", &a, &b);
	    	vis[a] = b;
	    }
	    for (int i = n-1; i >= 0; i--){
	    	if (vis[i]) {
	    		dp[i] = dp[vis[i]];
	    		vis[i] = 0;
	    		continue;
	    	}
	    	for (int j = 1; j <= 6; j++) dp[i] += dp[i+j];
	    	dp[i] = dp[i]/6+1;
	    }
	    printf("%.4f\n", dp[0]);
	}
	return 0;
}