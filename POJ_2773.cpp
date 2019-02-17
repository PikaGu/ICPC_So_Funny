#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector> 
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

vector<int> v;

int main(){
    freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
    int m, k;
    while (scanf("%d%d", &m, &k) == 2){
    	v.clear();
    	for (int i = 1; i <= m; i++){
    		if (__gcd(i, m) == 1) v.push_back(i);
    	}
    	LL ans;
    	if (k % v.size() == 0) ans = (k/v.size()-1)*m + v[v.size()-1];
    	else ans = k/v.size()*m + v[k%v.size()-1];
    	printf("%lld\n", ans);
    }
    return 0;
}