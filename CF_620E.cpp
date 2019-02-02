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

const int mx = 4e5+5;
vector<int> G[mx];
int cnt = 0, n;
struct tree{
	int l, r, lazy;
	LL sum;
}tree[mx<<2];
int L[mx], R[mx], c[mx];

void push_down(int id){
	if (tree[id].lazy != 0){
		LL x = tree[id].lazy;
		tree[lid].lazy = tree[rid].lazy = x;
		tree[lid].sum = tree[rid].sum = 1LL << x;
		tree[id].lazy = 0;
	}
}

void push_up(int id){
	tree[id].sum = tree[lid].sum | tree[rid].sum;
}

void upd(int l, int r, int id, int x){
	if (tree[id].l == l && tree[id].r == r){
		tree[id].lazy = x;
		tree[id].sum = 1LL << x;
		return;
	}
	push_down(id);
	int mid = (tree[id].l + tree[id].r) >> 1;
	if (r <= mid) upd(l, r, lid, x);
	else if (mid < l) upd(l, r, rid, x);
	else upd(l, mid, lid, x), upd(mid+1, r, rid, x);
	push_up(id);
}

LL query(int l, int r, int id){
	if (tree[id].l == l && tree[id].r == r) return tree[id].sum;
	push_down(id);
	int mid = (tree[id].l + tree[id].r) >> 1;
	if (r <= mid) return query(l, r, lid);
	else if (mid < l) return query(l, r, rid);
	return query(l, mid, lid) | query(mid+1, r, rid);
}

void dfs(int u, int fa){
	L[u] = ++cnt;
	upd(cnt, n, 1, c[u]);
	for (int i = 0; i < (int)G[u].size(); i++){
		int v = G[u][i];
		if (v == fa) continue;
		dfs(v, u);
	}
	R[u] = cnt;
}

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].lazy = 0;
	tree[id].sum = 0;
	if (l == r) return;
	int mid = (l+r)>>1;
	build(l, mid, lid);
	build(mid+1, r, rid);
}

int main(){
    freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
    int q, u, v;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", &c[i]);
    for (int i = 1; i < n; i++){
    	scanf("%d%d", &u, &v);
    	G[u].push_back(v);
    	G[v].push_back(u);
    }
    build(1, n, 1);
    dfs(1, -1);
    while (q--){
    	int op, x, y;
    	scanf("%d%d", &op, &x);
    	if (op == 1){
    		scanf("%d", &y);
    		upd(L[x], R[x], 1, y);
    	}
    	else {
    		LL num = query(L[x], R[x], 1);
    		int ans = 0;
    		while (num){
    			ans += num&1;
    			num >>= 1;
    		}
    		printf("%d\n", ans);
    	}
    }
    return 0;
}