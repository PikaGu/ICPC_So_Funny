#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
#define LL long long
#define lid id << 1
#define rid id << 1 | 1
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int mx = 5e5+10;
vector<int> G[mx];
int sum[mx], rk[mx], f[mx], top[mx], id[mx], son[mx];
struct tree{
	int l, r;
	int val;
}tree[mx<<2];

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].val = 0;
	if (l == r) return;
	int mid = (l+r)>>1;
	build(l, mid, lid);
	build(mid+1, r, rid);
}

void dfs(int u, int fa, int cnt){
	sum[u] = 1;
	rk[u] = cnt;
	f[u] = fa;
	for (int i = 0; i < (int)G[u].size(); i++){
		int v = G[u][i];
		if (v == fa) continue;
		dfs(v, u, cnt+1);
		sum[u] += sum[v];
		if (sum[v] > sum[son[u]]) son[u] = v;
	}
}

int cnt = 0;

void dfs2(int u, int t){
	top[u] = t;
	id[u] = ++cnt;
	if (!son[u]) return;
	dfs2(son[u], t);
	for (int i = 0; i < (int)G[u].size(); i++){
		int v = G[u][i];
		if (!id[v]) dfs2(v, v);
	}
}

void push_down(int id){
	if (tree[id].val != -1){
		tree[lid].val = tree[rid].val = tree[id].val;
		tree[id].val = -1;
	}
}

void upd(int l, int r, int id, int x){
	if (tree[id].l == l && tree[id].r == r){
		tree[id].val = x;
		return;
	}
	push_down(id);
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) upd(l, r, lid, x);
	else if (mid < l) upd(l, r, rid, x);
	else upd(l, mid, lid, x), upd(mid+1, r, rid, x);
	if (tree[lid].val == tree[rid].val && tree[lid].val != -1) 
		tree[id].val = tree[lid].val;
	else tree[id].val = -1;
}

bool query(int x, int id){
	if (tree[id].val != -1) return tree[id].val;
	push_down(id);
	int mid = (tree[id].l + tree[id].r)>>1;
	if (x <= mid) return query(x, lid);
	return query(x, rid);
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int n, q, u, v, op;
	scanf("%d", &n);
	for (int i = 1; i < n; i++){
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0, 1);
	dfs2(1, 1);
	build(1, n, 1);
	//for (int i = 1; i <= n; i++) debug(top[i]);
	scanf("%d", &q);
	while (q--){
		scanf("%d%d", &op, &v);
		if (op == 1){
			upd(id[v], id[v]+sum[v]-1, 1, 1);
		}
		else if (op == 2){
			while (top[v] != 1){
				upd(id[top[v]], id[v], 1, 0);
				v = f[top[v]];
			}
			upd(1, id[v], 1, 0);
		}
		else if (op == 3) {
			printf("%d\n", query(id[v], 1));
		}
	}
	return 0;
}