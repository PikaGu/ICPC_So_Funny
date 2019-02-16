#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

string s[17];
int cost[17][17], n;
int dp[17][1<<16];
string ans;

void dfs(int u, int sta){
	if (!sta) return;
	int nxt = -1;
	string tmp;
	for (int i = 1; i <= n; i++){
		if (i == u) continue;
		if (!(sta & (1<<(i-1)))) continue;
		if (dp[u][sta] == dp[i][sta&~(1<<(u-1))]+cost[u][i]){
			string str = s[i].substr(s[u].length()-cost[u][i]);
			if (nxt == -1 || str < tmp){
				tmp = str;
				nxt = i;
			}
		}
	}
	ans += tmp;
	dfs(nxt, sta&~(1<<(u-1)));
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int t, kase = 0;
	ios::sync_with_stdio(false);
	cin >> t;
	while (t--){
		cout << "Scenario #" << ++kase << ":\n";
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> s[i];
		if (n == 1){
			cout << s[1] << "\n";
			continue;
		}
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (i == j) continue;
				if (s[i].find(s[j]) != string::npos) s[j] = s[i];
			}
			for (int j = 0; j < (1<<n); j++) dp[i][j] = INF;
		}
		sort(s+1, s+n+1);
		n = unique(s+1, s+n+1)-(s+1);
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				if (i == j) continue;
				cost[i][j] = INF;
				int len = min(s[i].length(), s[j].length());
				for (int k = 0; k <= len; k++){
					if (s[i].substr(s[i].length()-k) == s[j].substr(0, k))
						cost[i][j] = s[i].length()-k;
				}
			}
			dp[i][1<<(i-1)] = s[i].length();
		}
		for (int k = 0; k < (1<<n); k++){
			for (int i = 1; i <= n; i++){
				if (!(k & (1<<(i-1)))) continue;
				if (dp[i][k] == INF) continue;
				for (int j = 1; j <= n; j++){
					if (i == j) continue;
					if (k & (1<<(j-1))) continue;
					dp[j][k|(1<<(j-1))] = min(dp[j][k|(1<<(j-1))], dp[i][k]+cost[j][i]);
				}
			}
		}
		int sum = INF, id; 
		for (int i = 1; i <= n; i++){
			if (sum > dp[i][(1<<n)-1]){
				sum = dp[i][(1<<n)-1];
				id = i;
			}
		}
		ans = s[id];
		dfs(id, (1<<n)-1);
		cout << ans << "\n\n";
	}
	return 0;
}