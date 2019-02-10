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

const int mx = 1e5+7;

struct tree{
	int l, r, col;
	LL sum, lazy;
}tree[mx<<2];

void push_up(int id){
	tree[id].sum = tree[lid].sum + tree[rid].sum;
	if (tree[lid].col == tree[rid].col) tree[id].col = tree[lid].col;
	else tree[id].col = 0;
}

void push_down(int id){
	if (tree[id].lazy){
		LL x = tree[id].lazy;
		tree[lid].lazy += x;
		tree[rid].lazy += x;
		tree[lid].sum += x*(tree[lid].r-tree[lid].l+1);
		tree[rid].sum += x*(tree[rid].r-tree[rid].l+1);
		tree[id].lazy = 0;
	}
	if (tree[id].col){
		tree[lid].col = tree[rid].col = tree[id].col;
		tree[id].col = 0;
	}
}

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].lazy = 0;
	if (l == r){
		tree[id].sum = 0;
		tree[id].col = l;
		return;
	}
	int mid = (l+r)>>1;
	build(l, mid, lid);
	build(mid+1, r, rid);
	push_up(id);
}

void upd(int l, int r, int id, int x){
	if (tree[id].l >= l && tree[id].r <= r && tree[id].col){
		tree[id].lazy += abs(tree[id].col-x);
		tree[id].sum += (LL)abs(tree[id].col-x)*(tree[id].r-tree[id].l+1);
		tree[id].col = x;
		return;
	}
	push_down(id);
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) upd(l, r, lid, x);
	else if (mid < l) upd(l, r, rid, x);
	else upd(l, mid, lid, x), upd(mid+1, r, rid, x);
	push_up(id);
}

LL query(int l, int r, int id){
	if (tree[id].l == l && tree[id].r == r) return tree[id].sum;
	push_down(id);
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) return query(l, r, lid);
	if (mid < l) return query(l, r, rid);
	return query(l, mid, lid) + query(mid+1, r, rid);
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	build(1, n, 1);
	while (m--){
		int op, l, r, x;
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1){
			scanf("%d", &x);
			upd(l, r, 1, x);
		}
		else {
			printf("%lld\n", query(l, r, 1));
		}
	}
	return 0;
}