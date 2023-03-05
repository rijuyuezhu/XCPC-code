//https://www.luogu.com.cn/problem/P4391
#include<cstdio>
#include<cstring>

typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXLEN = 1e6 + 5;
char s[MAXLEN];
int n;
int nxt[MAXLEN];
int main() {
    n = read();
    scanf("%s", s + 1);
    int j = 0;
    nxt[1] = 0;
    for(int i = 2; i <= n; i++) {
        if(j && s[j + 1] != s[i]) j = nxt[j];
        if(s[j + 1] == s[i]) j++;
        nxt[i] = j;
    }
    printf("%d\n", n - nxt[n]);
    return 0;
}