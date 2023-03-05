//https://www.luogu.com.cn/problem/P1095
#include<cstdio>
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXT = 300005;
int M, S, T;
int f[MAXT];

int main() {
    M = read(), S = read(), T = read();
    for(int i = 1; i <= T; i++) {
       if(M >= 10) {
          M -= 10;
          f[i] = f[i - 1] + 60;
       } else {
          M += 4;
          f[i] = f[i - 1];
       }
    }
    for(int i = 1; i <= T; i++) {
       if(f[i - 1] + 17 > f[i]) f[i] = f[i - 1] + 17;
       if(f[i] >= S) {
          printf("Yes\n%d\n", i);
          return 0;
       }
    }
    printf("No\n%d\n", f[T]);
    return 0;
}