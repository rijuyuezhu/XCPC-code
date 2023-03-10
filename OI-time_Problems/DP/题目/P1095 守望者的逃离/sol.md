[P1095 守望者的逃离](https://www.luogu.com.cn/problem/P1095)

动态规划

我们发现，只有时间好记录状态

设f[i]表示在i秒末能够走的最远是多少。

我们发现，魔法和走路相比，如果能停下来等，能等到下一次施展魔法，怎么样也比走路划算。并且，我什么时候准备施展魔法是没有关系的，只与总次数有关。

所以我们先假设全用魔法，计算出一系列的f[i]。

然后我们再用走路的方式做一次更新。显然这样是对的.

>   其实你可以理解为分类讨论，该回蓝的时候其实还是在回蓝，只是针对当前时间来说如果跑步好的话我们就先跑步
>
>   也可以理解为一种尝试，我们看看如果这一秒换成跑步我们能不能逃出去，如果能逃出去岂不美滋滋，如果还是逃不出去，其实你会发现几秒之后dp值又被改回去了，因为闪现的速度是要大于跑步的
>
>   看起来是同时进行的，其实确实是同时进行的，只不过不是叠加式的，而是分成2种情况的同时进行
>
>   如果你模拟几下的话就会发现，如果魔法值够的话，跑步就永远不会覆盖闪现，只有魔法值不够的时候，才给了跑步可乘之机，那我们就看看这秒换成跑步到底能不能出去，如果还是出不去，你可以认为又换成回蓝了
>
>   简直就像你有一个plan A和plan B一样，你就是一个贪心的人，这两个计划是同步进行的，但你只取每一时刻的最大值

这是dalao的解答

```cpp
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
```

