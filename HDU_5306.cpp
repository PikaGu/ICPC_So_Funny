#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;
#define lid id << 1
#define rid id << 1 | 1

const int N = 1e6+7;
int a[N];
struct tree{
	int l, r, num;
	LL sum, mx, smx;
}tree[N<<2];

void push_up(int id){
	tree[id].sum = tree[lid].sum + tree[rid].sum;
	if (tree[lid].mx == tree[rid].mx){
		tree[id].mx = tree[lid].mx;
		tree[id].num = tree[lid].num + tree[rid].num;
		tree[id].smx = max(tree[lid].smx, tree[rid].smx);
	}
	else {
		tree[id].mx = max(tree[lid].mx, tree[rid].mx);
		tree[id].num = (tree[lid].mx > tree[rid].mx) ? tree[lid].num : tree[rid].num;
		tree[id].smx = max(min(tree[lid].mx, tree[rid].mx), max(tree[lid].smx, tree[rid].smx));
	}
}

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	if (l == r){
		tree[id].mx = tree[id].sum = a[l];
		tree[id].smx = -1;
		tree[id].num = 1;
		return;
	}
	int mid = (l+r)>>1;
	build(l, mid, lid);
	build(mid+1, r, rid);
	push_up(id);
}

void push_down(int id, int x){
	if (x >= tree[id].mx) return;
	tree[id].sum -= tree[id].num * (tree[id].mx-x);
	tree[id].mx = x;
}

void upd(int l, int r, int id, int x){
	if (tree[id].mx <= x) return;
	if (tree[id].l >= l && tree[id].r <= r && tree[id].smx < x){
		push_down(id, x);
		return;
	}
	push_down(lid, tree[id].mx);
	push_down(rid, tree[id].mx);
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) upd(l, r, lid, x);
	else if (mid < l) upd(l, r, rid, x);
	else upd(l, mid, lid, x), upd(mid+1, r, rid, x);
	push_up(id);
}

LL query(int l, int r, int id, bool f){
	if (tree[id].l == l && tree[id].r == r){
		if (f) return tree[id].sum;
		return tree[id].mx;
	}
	push_down(lid, tree[id].mx);
	push_down(rid, tree[id].mx);
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) return query(l, r, lid, f);
	if (mid < l) return query(l, r, rid, f);
	return f ? query(l, mid, lid, f) + query(mid+1, r, rid, f) : max(query(l, mid, lid, f), query(mid+1, r, rid, f));
}

int main(){
	//freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int t, n, q;
	scanf("%d", &t);
	while (t--){
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		build(1, n, 1);
		int op, l, r, x;
		while (q--){
			scanf("%d%d%d", &op, &l, &r);
			if (!op){
				scanf("%d", &x);
				upd(l, r, 1, x);
			}
			else if (op == 1) printf("%lld\n", query(l, r, 1, 0));
			else printf("%lld\n", query(l, r, 1, 1));
		}
	}
	return 0;
}