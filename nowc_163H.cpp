#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;
#define lid id << 1
#define rid id << 1 | 1
const int mx = 5e4+5;
const int mod = 2018;
bool cir[mod];
int a[mx];

void init(){
	for (int i = 0; i < mod; i++){
		int tmp = i;
		for (int j = 0; j < 6; j++) tmp = tmp*tmp % mod;
		if (tmp == i) cir[i] = 1;
	}
}

struct tree{
	int l, r, lazy;
	LL sum[6];
	bool cir;
}tree[mx<<2];

void push_ok(int id){
	if (cir[tree[id].sum[0]]){
		tree[id].cir = 1;
		for (int i = 1; i < 6; i++)
			tree[id].sum[i] = tree[id].sum[i-1]*tree[id].sum[i-1]%mod;
	}
}

void push_down(int id){
	if (tree[id].lazy){
		LL tmp[6];
		for (int i = 0; i < 6; i++) tmp[i] = tree[id].sum[(i+tree[id].lazy)%6];
		memcpy(tree[id].sum, tmp, sizeof tmp);
		if (tree[id].l != tree[id].r){
			tree[lid].lazy += tree[id].lazy;
			tree[rid].lazy += tree[id].lazy;
		}
		tree[id].lazy = 0;
	}
}

void push_up(int id){
	push_down(lid);
	push_down(rid);
	tree[id].sum[0] = tree[lid].sum[0] + tree[rid].sum[0];
	if (tree[lid].cir && tree[rid].cir){
		tree[id].cir = 1;
		for (int i = 1; i < 6; i++)
			tree[id].sum[i] = tree[lid].sum[i] + tree[rid].sum[i];
	}
}

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].cir = 0;
	tree[id].lazy = 0;
	for (int i = 0; i < 6; i++) tree[id].sum[i] = 0;
	if (l == r){
		tree[id].sum[0] = a[l];
		push_ok(id);
		return;
	}
	int mid = (l+r)>>1;
	build(l, mid, lid);
	build(mid+1, r, rid);
	push_up(id);
}

void upd(int l, int r, int id){
	if (tree[id].l >= l && tree[id].r <= r){
		if (tree[id].cir){
			tree[id].lazy++;
			return;
		}
		if (tree[id].l == tree[id].r){
			tree[id].sum[0] = tree[id].sum[0]*tree[id].sum[0] % mod;
			push_ok(id);
			return;
		}
	}
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) upd(l, r, lid);
	else if (mid < l) upd(l, r, rid);
	else upd(l, mid, lid), upd(mid+1, r, rid);
	push_up(id);
}

LL query(int l, int r, int id){
	push_down(id);
	if (tree[id].l == l && tree[id].r == r) return tree[id].sum[0];
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) return query(l, r, lid);
	if (mid < l) return query(l, r, rid);
	return query(l, mid, lid) + query(mid+1, r, rid);
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	init();
	int t, kase = 0, n, q;
	scanf("%d", &t);
	while (t--) {
		printf("Case #%d:\n", ++kase);
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		build(1, n, 1);
		scanf("%d", &q);
		char s[2];
		int l, r;
		while (q--){
			scanf("%s%d%d", s, &l, &r);
			if (s[0] == 'Q')
				printf("%lld\n", query(l, r, 1));
			else upd(l, r, 1);
		}
	}
	return 0;
}