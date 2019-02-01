#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f3f3f3f3f
#define lid id << 1
#define rid id << 1 | 1
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int mx = 1e5+7;
vector<int> G[mx];
int p[mx];
int n, m;
LL b[2*mx], a[mx];
LL ans, k;

struct tree{
	int l, r;
	LL sum;
}tree[mx<<4];

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].sum = 0;
	if (l == r) return;
	int mid = (l+r)>>1;
	build(l, mid, lid);
	build(mid+1, r, rid);
}

void upd(int pos, int v, int id){
	if (tree[id].l == pos && tree[id].r == pos){
		tree[id].sum += v;
		return;
	}
	int mid = (tree[id].l + tree[id].r) >> 1;
	if (pos <= mid) upd(pos, v, lid);
	else upd(pos, v, rid);
	tree[id].sum = tree[lid].sum + tree[rid].sum;
}

LL query(int l, int r, int id){
	if (tree[id].l == l && tree[id].r == r) return tree[id].sum;
	int mid = (tree[id].l + tree[id].r) >> 1;
	if (r <= mid) return query(l, r, lid);
	else if (mid < l) return query(l, r, rid);
	return query(l, mid, lid) + query(mid+1, r, rid);
}

void dfs(int u){
	int pos = lower_bound(b+1, b+m+1, a[u] ? k/a[u] : INF) - b;
	ans += query(1, pos, 1);
	pos = lower_bound(b+1, b+m+1, a[u]) - b;
	upd(pos, 1, 1);
	for (int i = 0; i < (int)G[u].size(); i++){
		int v = G[u][i];
		dfs(v);
	}
	upd(pos, -1, 1);
}

int main(){
    //freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--){
    	ans = 0;
    	scanf("%d%lld", &n, &k);
    	for (int i = 1; i <= n; i++) {
    		scanf("%lld", &a[i]);
    		b[i] = a[i];
    		b[i+n] = (a[i] ? k/a[i] : INF);
    		G[i].clear();
    		p[i] = -1;
    	}
    	sort(b+1, b+2*n+1);
    	m = unique(b+1, b+2*n+1)-(b+1);
    	build(1, m, 1);
    	for (int i = 1; i < n; i++){
    		int u, v;
    		scanf("%d%d", &u, &v);
    		p[v] = u;
    		G[u].push_back(v);
    	}
    	for (int i = 1; i <= n; i++){
    		if (p[i] == -1){
    			dfs(i);
    			break;
    		}
    	}
    	printf("%lld\n", ans);
    }
    return 0;
}