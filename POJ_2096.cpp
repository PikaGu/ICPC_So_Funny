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

const int mx = 1010;
double dp[mx][mx];

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int n, s;
	scanf("%d%d", &n, &s);
	int ns = n*s;
	dp[n][s] = 0;
	for (int i = n; i >= 0; i--){
		for (int j = s; j >= 0; j--){
			if (i == n && j == s) continue;
			double k = ns;
			k += (n-i)*j*dp[i+1][j];
			k += i*(s-j)*dp[i][j+1];
			k += (n-i)*(s-j)*dp[i+1][j+1];
			dp[i][j] = 1.0*k / (ns - i*j);
		}
	}
	printf("%.4f\n", dp[0][0]);
	return 0;
}