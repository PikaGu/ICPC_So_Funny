#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<set>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int mx = 1e5+7;

struct edge{
	int v, nxt, w;
	edge(int v=0, int nxt=0, int w=0): v(v), nxt(nxt), w(w){}
}e[mx*2];
int head[mx], ans[mx];
int q[mx], c[mx];
int tot = 0, cnt = 0;
multiset<int> s;
vector<int> id[mx];

void add(int u, int v, int w){
	e[tot].v = v;
	e[tot].w = w;
	e[tot].nxt = head[u];
	head[u] = tot++;
}

void dfs(int u, int fa, int w){
	s.insert(w);
	if (u != 1  && id[u].size()){
		for (int i = 0; i < id[u].size(); i++){
			multiset<int>::iterator it = s.upper_bound(c[id[u][i]]);
			--it;
			ans[id[u][i]] = *it;
		}
	}
	for (int i = head[u]; ~i; i = e[i].nxt){
		int v = e[i].v;
		if (v == fa) continue;
		dfs(v, u, e[i].w);
	}
	s.erase(s.find(w));
}

int main(){
    freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
    int t, n, m;
    scanf("%d", &t);
    while (t--){
    	scanf("%d", &n);
    	tot = cnt = 0;
    	s.clear();
    	for (int i = 1; i <= n; i++){
    		head[i] = -1;
    		id[i].clear();
    	}
    	for (int i = 1; i < n; i++){
    		int u, v, w;
    		scanf("%d%d%d", &u, &v, &w);
    		add(u, v, w);
    		add(v, u, w);
    	}
    	scanf("%d", &m);
    	for (int i = 1; i <= m; i++) {
    		scanf("%d%d", &q[i], &c[i]);
    		id[q[i]].push_back(i);
    	}
    	dfs(1, -1, -1);
    	for (int i = 1; i <= m; i++){
    		if (q[i] == 1){
    			printf("-1\n");
    			continue;
    		}
    		printf("%d\n", ans[i]);
    	}
    }
    return 0;
}