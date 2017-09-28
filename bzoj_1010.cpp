#include <cstdio>
#include <iostream>
using namespace std;
const int N = 50003;
int n,st[N],l,r;
long long L;
long long S,c[N],dp[N],x[N];
inline long long cy(int i) { return dp[i] + x[i]*x[i]+2*x[i]*L;}
inline long long cx(int i) { return 2*x[i];}
inline bool dot(long long x1,long long y1,long long x2,long long y2) { return x1*y2-x2*y1<=0;} 
int main() {
	cin >> n >> L;
	L++;
	for(int i = 1 ; i <= n ; ++i) {
		int tmp;
		scanf("%d",&tmp);
		S += tmp;
		x[i] = S + i;
	}
	for(int i = 1 ; i <= n ; ++i) {
		while(l<r && x[i]*(cx(st[l+1])-cx(st[l])) > cy(st[l+1]) - cy(st[l])) l++;
		int j = st[l];
		dp[i] = dp[j] + (x[i]-x[j]-L)*(x[i]-x[j]-L);
		while(l<r && dot(cx(st[r])-cx(st[r-1]),cy(st[r])-cy(st[r-1]),cx(i)-cx(st[r]),cy(i)-cy(st[r]))) r--;
	       st[++r] = i;
	}
	cout << dp[n] << endl;
}
