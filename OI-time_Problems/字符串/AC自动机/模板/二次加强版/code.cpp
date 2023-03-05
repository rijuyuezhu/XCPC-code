#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 2e5 + 5;
const int MAXL = 2e5 + 5;
const int MAXT = 2e6 + 5;
int n, gt[MAXN];
char s[MAXL], t[MAXT];

int ch[MAXL][26], tot, fail[MAXL], val[MAXL];
int que[MAXL], hd, tl;
int head[MAXL], ver[MAXL], nxt[MAXL], cnt;//fail tree
void ins(char s[], int id) {
	int l = strlen(s + 1), now = 0;
	for(int i = 1; i <= l; i++) {
		int v = s[i] - 'a';
		if(!ch[now][v]) ch[now][v] = ++tot;
		now = ch[now][v];
	}
	gt[id] = now;
}
void addedge(int u, int v) {
	ver[++cnt] = v; nxt[cnt] = head[u]; head[u] = cnt;
}
void build() {
	hd = 1; tl = 0;
	for(int i = 0; i < 26; i++)
		if(ch[0][i]) fail[ch[0][i]] = 0, que[++tl] = ch[0][i];
	while(hd <= tl) {
		int u = que[hd++];
		for(int i = 0; i < 26; i++)
			if(ch[u][i]) fail[ch[u][i]] = ch[fail[u]][i], que[++tl] = ch[u][i];
			else ch[u][i] = ch[fail[u]][i];
	}
	for(int i = 1; i <= tot; i++) addedge(fail[i], i);
}
void qry(char t[]) {
	int l = strlen(t + 1), now = 0;
	for(int i = 1; i <= l; i++) {
		now = ch[now][t[i] - 'a'];
		val[now]++;
	}
}
void dfs(int u) {
	for(int i = head[u]; i; i = nxt[i]) {
		dfs(ver[i]);
		val[u] += val[ver[i]];
	}
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", s+1);
		ins(s, i);
	}
	build();
	scanf("%s", t+1);
	qry(t);
	dfs(0);
	for(int i = 1; i <= n; i++) printf("%d\n", val[gt[i]]);
	return 0;
}
