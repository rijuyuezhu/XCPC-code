/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-26 07:26:15
 * @Description: https://www.luogu.com.cn/problem/P3366
 * @Tag: 最小生成树，Kruskal
*/



#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 5e3+5;
const int MAXM = 2e5+5;
int N, M, tot, ans;
struct Edge {
   int u, v, w;
}e[MAXM];
bool cmp(const Edge& a, const Edge& b) {
   return a.w < b.w;
}
int upto[MAXN];
int getup(int x) {
   return x == upto[x] ? x : upto[x] = getup(upto[x]);
}
void Kruskal() {
   for(int i = 1; i <= N; i++) upto[i] = i;
   sort(e + 1, e + 1 + M, cmp);
   ans = tot = 0;
   for(int i = 1; i <= M && tot < N-1; i++) {
      int fu = getup(e[i].u), fv = getup(e[i].v);
      if(fu == fv) continue;
      tot++; ans += e[i].w;
      upto[fu] = fv;
   }
}
int main() {
   #ifndef ONLINE_JUDGE
   freopen("main.in", "r", stdin);
   #endif
   scanf("%d%d", &N, &M);
   for(int i = 1; i <= M; i++) {
      scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
   }
   Kruskal();
   if(tot < N-1) printf("orz\n");
   else printf("%d\n", ans);
   return 0;
}