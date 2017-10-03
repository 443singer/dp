#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
const long long mod = 1000000007;
struct hp {
	long long sum,sqsum,cnt;
	hp() {cnt = -1 ; sqsum = 0 ; sum = 0;}
	hp(long long cnt,long long sum,long long sqsum):cnt(cnt),sum(sum),sqsum(sqsum){}
}dp[20][10][10];
long long l,r,p[30];
long long len,num[30];
hp dfs(int len,int re1,int re2,bool fp) {
	if(!len) return re1!=0 && re2!=0 ? hp(1,0,0) : hp(0,0,0);
	if((dp[len][re1][re2].cnt!=-1) && (!fp)) return dp[len][re1][re2];
	int fpmax = fp?num[len]:9;
	hp ans = hp(0,0,0);
	for(int i = 0 ; i <= fpmax ; ++i) {
		if(i==7) continue;
		hp next = dfs(len-1,(re1+i)%7,(re2*10+i)%7,fp&&i==fpmax);
		ans.cnt = (ans.cnt + next.cnt)%mod;
		ans.sum = ((ans.sum + i*p[len]*next.cnt%mod)%mod+next.sum)%mod;
		ans.sqsum = (ans.sqsum+next.cnt*(i*p[len]%mod*i*p[len]%mod))%mod;
		ans.sqsum = (ans.sqsum+next.sqsum)%mod;
		ans.sqsum = (ans.sqsum+2*i*p[len]%mod*next.sum%mod)%mod;
	}
	if(!fp) dp[len][re1][re2] = ans;
	return ans;
}
long long solve(long long haha) {
	len = 0;
	while(haha) {
		num[++len] = haha%10;
		haha /= 10;
	}
	hp a = dfs(len,0,0,true);
	return a.sqsum;
}
int main() {
	int T;
	scanf("%d",&T);
	p[1] = 1;
	for(int i = 2 ; i <= 20 ; ++i) p[i] = p[i-1]*10%mod;
	for(int i = 1 ; i <= T ; ++i) {
		scanf("%I64d%I64d",&l,&r);
		long long a = solve(r);
		a -= solve(l-1);
		a = (a%mod+mod)%mod;
		cout << a << endl;
	}
}
