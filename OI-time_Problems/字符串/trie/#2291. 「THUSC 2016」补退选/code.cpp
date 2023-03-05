#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
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
typedef pair<int, int> pii;
#define fi first
#define se second
const int MAXN = 6e6 + 5;
const int MAXL = 62;
const int INF = 0x3f3f3f3f;
int n, ch[MAXN][11], tot, _q, lans;
char tmp[MAXN];
struct qry {
	char s[MAXL];
	int tim, a, b, c;
}q[MAXN];
vector<pii> rec[MAXN];
vector<int> bra[MAXN];
void ins(char *s, int num, int val) {
	int n = strlen(s);
	int p = 1;
	for(int i = 0; i < n; i++) {
		int c = s[i] - 'a';
		if(!ch[p][c]) ch[p][c] = ++tot;
		p = ch[p][c];
		rec[p].push_back(pii((rec[p].empty() ? 0 : rec[p].back().fi) + val, num));
	}
}

int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		int k = read();
		if(k == 1 || k == 2) {
			scanf("%s", tmp);
			ins(tmp, i, k == 1 ? 1 : -1);
		} else {
			++_q;
			scanf("%s", q[_q].s);
			q[_q].tim = i; q[_q].a = read(), q[_q].b = read(), q[_q].c = read();
		}
	}
	for(int i = 1; i <= tot; i++) {
		int mv = 0;
		for(vector<pii>::iterator p = rec[i].begin(); p != rec[i].end(); ++p) mv = max(mv, p->fi);
		bra[i].resize(mv+1, INF);
		bra[i][0] = 0;
		for(vector<pii>::iterator p = rec[i].begin(); p != rec[i].end(); ++p) 
			bra[i][p->fi] = min(bra[i][p->fi], p->se);
	}
	for(int rq = 1; rq <= _q; rq++) {
		qry& now = q[rq]; int v = (1ll * now.a * (lans < 0 ? -lans : lans) + now.b) % now.c + 1;
		int p = 1, len = strlen(now.s);
		for(int i = 0; i < len; i++) {
			int v = now.s[i] - 'a';
			p = ch[p][v];
		}
		if(!p) {
			printf("-1\n"); lans = -1;
			continue;
		}
		if((int)bra[p].size()-1 < v) {
			printf("-1\n"); lans = -1;
			continue;
		}
		printf("%d\n", lans = (bra[p][v] >= now.tim ? -1 : bra[p][v]));
	}
	return 0;
}
