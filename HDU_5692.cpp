#pragma comment(linker, "/STACK:1024000000,1024000000")
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

const int N = 1e5+7;
int head[N], a[N];
int tot, cnt;
struct edge{
	int v, nxt;
}e[N*2];
struct tree{
	int l, r;
	LL mx, lazy;	
}tree[N<<2];

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].lazy = tree[id].mx = 0;
	if (l == r) return;
	int mid = (l+r)/2;
	build(l, mid, lid);
	build(mid+1, r, rid);
}

int L[N], R[N];

void push_down(int id){
	if (tree[id].lazy && tree[id].l != tree[id].r){
		LL x = tree[id].lazy;
		tree[lid].lazy += x;
		tree[rid].lazy += x;
		tree[lid].mx += x;
		tree[rid].mx += x;
		tree[id].lazy = 0;
	}
}

void push_up(int id){
	tree[id].mx = max(tree[lid].mx, tree[rid].mx);
}

void upd(int l, int r, int id, LL x){
	push_down(id);
	if (tree[id].l == l && tree[id].r == r){
		tree[id].lazy += x;
		tree[id].mx += x;
		return;
	}
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) upd(l, r, lid, x);
	else if (mid < l) upd(l, r, rid, x);
	else upd(l, mid, lid, x), upd(mid+1, r, rid, x);
	push_up(id);
}

void dfs(int u, int fa){
	L[u] = ++cnt;
	for (int i = head[u]; ~i; i = e[i].nxt){
		int v = e[i].v;
		if (v == fa) continue;
		dfs(v, u);
	}
	R[u] = cnt;
	upd(L[u], R[u], 1, a[u]);
}

LL query(int l, int r, int id){
	push_down(id);
	if (tree[id].l == l && tree[id].r == r) return tree[id].mx;
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) return query(l, r, lid);
	else if (mid < l) return query(l, r, rid);
	return max(query(l, mid, lid), query(mid+1, r, rid));
}

void add(int u, int v){
	e[tot].v = v;
	e[tot].nxt = head[u];
	head[u] = tot++;
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int t, n, q, kase = 0;
	scanf("%d", &t);
	while (t--){
		scanf("%d%d", &n, &q);
		printf("Case #%d:\n", ++kase);
		tot = cnt = 0;
		for (int i = 1; i <= n; i++) head[i] = -1;
		for (int i = 1; i < n; i++){
			int u, v;
			scanf("%d%d", &u, &v);
			u++, v++;
			add(u, v); add(v, u);
		}
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		build(1, n, 1);
		dfs(1, -1);
		while (q--){
			int op, x, y;
			scanf("%d%d", &op, &x);
			x++;
			if (op == 1){
				LL ans = query(L[x], R[x], 1);
				printf("%lld\n", ans);
			}
			else {
				scanf("%d", &y);
				upd(L[x], R[x], 1, y-a[x]);
				a[x] = y;
			}
		}
	}
	return 0;
}