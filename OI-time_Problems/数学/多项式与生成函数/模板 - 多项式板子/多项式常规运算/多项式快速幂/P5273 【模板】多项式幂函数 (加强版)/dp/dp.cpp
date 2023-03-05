#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
int main() {
	for(int i = 1; i < 10000; i++) {
		system("data > data.in");
		system("code < data.in > code.out");
		system("code2 < data.in > code2.out");
		if(system("fc code.out code2.out")) {
			printf("WA\n");
			system("pause");
			return 0;
		}
	}

	return 0;
}
