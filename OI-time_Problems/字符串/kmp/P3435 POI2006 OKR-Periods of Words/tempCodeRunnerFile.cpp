#include<cstdio>
#include<cstring>

typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXK = 1e6 + 5;
char s[MAXK];
int k;
int nxt[MAXK];
ll ans;
int main() {
    k = read();
    scanf("%s", s + 1);
    int j = 0; nxt[1] = 0;
    for(int i = 2; i <= k; i++) {
        if(j && s[j + 1] != s[i]) j = nxt[j];
        if(s[j + 1] == s[i]) j++;
        nxt[i] = j;
    }
    for(int i = 2; i <= k; i++) {
        int j = i;
        while(nxt[j]) j = nxt[j];
        if(nxt[i]) nxt[i] = j;
        /*
        类似于一种路径压缩的思想，很像并查集
        这样做以后就把nxt[i]表达1~i（前缀等于后缀的）的最长前/后缀的长度
        变为满足条件的最短前/后缀长度
        */
       ans += i - j;
    }
    printf("%lld", ans);
    return 0;
}