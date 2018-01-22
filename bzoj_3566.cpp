#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 500005;
const double eps = 1e-6;
double f[N],g[N],h[N];
int first[N],next_[N*2],to[N*2],eg;
double p[N*2];
inline void addedge(int x,int y,int pp) {
	next_[++eg] = first[x];
	first[x] = eg;
	to[eg] = y;
	p[eg] = pp*1.0/100;
}
inline void add(int x,int y,int pp) {
	addedge(x,y,pp);
	addedge(y,x,pp);
}
int n;
void dfs1(int u,int fa,double pp) {
	for(int i = first[u] ; i ; i = next_[i]) {
		if(to[i]==fa) continue;
		dfs1(to[i],u,p[i]);
		f[u] *= h[to[i]];
	}
	h[u] = f[u]+(1.0-f[u])*(1-pp);
}
void dfs2(int u,int fa) {
	for(int i = first[u] ; i ; i = next_[i]) {
		if(to[i]==fa) continue;
		double t = g[u]*f[u]/h[to[i]];
		g[to[i]] = t+(1.0-t)*(1-p[i]);
		dfs2(to[i],u);
	}
}
int main() {
	scanf("%d",&n);
	for(int i = 1 ; i < n ; ++i) {
		int x,y,pp;
		scanf("%d%d%d",&x,&y,&pp);
		add(x,y,pp);
	}
	for(int i = 1 ; i <= n ; ++i) {
		int tmp;
		scanf("%d",&tmp);
		f[i] = 1.0-tmp*1.0/100.0;
	}
	dfs1(1,0,0);
	g[1] = 1;
	dfs2(1,0);
	double ans = 0;
	for(int i = 1 ; i <= n ; ++i) ans += 1-f[i]*g[i];
	printf("%.6lf\n",ans);
}
