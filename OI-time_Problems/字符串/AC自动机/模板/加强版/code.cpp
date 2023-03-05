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

const int MAXN = 11005;
const int MAXL = 1e6 + 5;
int que[MAXN], hd, tl, n;
int ans[155];
char s[155][75], t[MAXL];
namespace AC_Automaton {
	int ch[MAXN][26], fail[MAXN], cnt, num[MAXL];
	void insert(char s[], int id) {
		int l = strlen(s + 1), now = 0;
		for(int i = 1; i <= l; i++) {
			int v = s[i] - 'a';
			if(!ch[now][v]) ch[now][v] = ++cnt;
			now = ch[now][v];
		}
		num[now] = id;
	}
	void clear() {
		memset(ch, 0x00, sizeof ch); memset(fail, 0x00, sizeof fail); memset(num, 0x00, sizeof num);
		cnt = 0;
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
	}
	void query(char t[]) {
		int l = strlen(t + 1), now = 0;
		for(int i = 1; i <= l; i++) {
			int v = t[i] - 'a';
			now = ch[now][v];
			for(int j = now; j; j = fail[j]) ans[num[j]]++;
		}
	}

}
using namespace AC_Automaton;

bool work() {
	memset(ans, 0x00, sizeof ans); clear();
	n = read();
	if(!n) return 0;
	for(int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
		insert(s[i], i);
	}
	build();
	scanf("%s", t + 1);
	query(t);
	int mx = 1;
	for(int i = 2; i <= n; i++)
		if(ans[i] > ans[mx]) mx = i;
	printf("%d\n", ans[mx]);
	for(int i = 1; i <= n; i++)
		if(ans[i] == ans[mx])
			printf("%s\n", s[i] + 1);
	return 1;
}
int main() {
	while(work());
	return 0;
}
