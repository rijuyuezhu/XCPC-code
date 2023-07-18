#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
char s[1005];
int n;
void work() {
    scanf("%s", s);
    n = strlen(s);
    for(int i = n-1; i >= 0; i--)
        if(s[i] != '*')
            printf("%c", s[i]);
    printf("\n");
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--)
        work();
    return 0;
}