#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int mod = 100003;
const int N = 100003;
int a[N];
int n,k,cnt;
long long JC;
long long x,y;
void gcd_(int a,int b) {
	if(b==0) {
		x = 1;
		y = 0;
		return;
	}
	gcd_(b,a%b);
	long long t = x;
	x = y;
	y = t-a/b*y;
}
long long g[N];
void solve() {
	long long ans = 1;
	g[n] = 1;
	for(int i = n-1 ; i >= k+1 ; --i) {
		gcd_(i,mod);
		x = (x+mod)%mod;
		ans = ((n-i)*ans+n)*x%mod;
		g[i] = ans;
	}
	ans = (ans+k)%mod;
	for(int i = k+2 ; i <= cnt ; ++i) {
		ans = (ans+g[i])%mod;
	}
	ans *= JC;
	ans %= mod;
	cout << ans << endl;
}
int main() {
	scanf("%d%d",&n,&k);
	JC = 1;
	for(int i = 2 ; i <= n ; ++i) JC = JC*i%mod;
	for(int i = 1 ; i <= n ; ++i) scanf("%d",&a[i]);
	for(int i = n ; i >= 1 ; --i) {
		if(!a[i]) continue;
		for(int j = 1 ; j * j <= i ; ++j) {
			if(i%j==0) {
				a[j] ^= 1;
				if(j*j!=i) a[i/j] ^= 1;
			}
		}
		cnt++;
	}
	if(cnt<=k) cout << JC*cnt%mod << endl;
	else solve();
}
