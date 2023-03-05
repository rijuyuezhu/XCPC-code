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
char s1[MAXLEN];//文本串
int n1;
char s2[MAXLEN];//模式串
int n2;
int nxt[MAXLEN];
int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    n1 = strlen(s1 + 1), n2 = strlen(s2 + 1);
    int j = 0;
    nxt[1] = 0;
    for(int i = 2; i <= n2; i++) {//这里一定要从2开始，不然会出错
        if(j && s2[j + 1] != s2[i]) j = nxt[j];
        if(s2[j + 1] == s2[i]) j++;
        nxt[i] = j;
    }
    j = 0;
    for(int i = 1; i <= n1; i++) {
        if(j && s2[j + 1] != s1[i]) j = nxt[j];
        if(s2[j + 1] == s1[i]) j++;
        if(j == n2) {
            printf("%d\n", i - j + 1);
            j = nxt[j];
        }
    }
    for(int i = 1; i <= n2; i++) printf("%d ", nxt[i]);
    printf("\n");
    return 0;
}