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
const int MAXL = 1e6 + 5;
int n;
char s[MAXL], t[MAXL];
int que[MAXL], hd, tl;
namespace AC_Automaton {
	int ch[MAXL][26], cnt, tot[MAXL], fail[MAXL];
	void ins(char s[]) {
		int l = strlen(s + 1), now = 0;
		for(int i = 1; i <= l; i++) {
			int v = s[i] - 'a';
			if(!ch[now][v]) ch[now][v] = ++cnt;
			now = ch[now][v];
		}
		tot[now]++;
	}
	void build() {
		hd = 1; tl = 0;
		for(int i = 0; i < 26; i++) 
			if(ch[0][i])
				fail[ch[0][i]] = 0, que[++tl] = ch[0][i];
		while(hd <= tl) {
			int u = que[hd++];
			for(int i = 0; i < 26; i++) 
				if(ch[u][i]) fail[ch[u][i]] = ch[fail[u]][i], que[++tl] = ch[u][i];
				else ch[u][i] = ch[fail[u]][i];
		}
	}
	int qry(char s[]) {
		int ans = 0, l = strlen(s + 1), now = 0;
		for(int i = 1; i <= l; i++) {
			now = ch[now][s[i] - 'a'];
			for(int j = now; j && ~tot[j]; j = fail[j]) ans += tot[j], tot[j] = -1;
		}
		return ans;
	}
}
using namespace AC_Automaton;
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		ins(s);
	}
	build();
	scanf("%s", t + 1);
	printf("%d\n", qry(t));
	
	return 0;
}
