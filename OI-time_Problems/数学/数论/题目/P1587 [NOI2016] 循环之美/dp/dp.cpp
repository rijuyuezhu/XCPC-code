#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
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
	for(int i = 1; i <= 10000; i++) {
		system("data > data.in");
		system("bf < data.in > bf.out");
		system("code < data.in > code.out");
		if(system("fc bf.out code.out")) {
			printf("WA");
			system("pause");
			return 0;
		}
		printf("AC");
	}
	return 0;
}
