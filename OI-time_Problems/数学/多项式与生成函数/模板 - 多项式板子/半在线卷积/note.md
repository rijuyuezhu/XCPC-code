<https://www.luogu.com.cn/blog/command-block/ban-zai-xian-juan-ji-xiao-ji>

# 半在线卷积

一个式子是卷积的形式，但是两边的项是相关的（比如要由前面的项推出后面的项）

## 类型1
[P4721 【模板】分治 FFT](https://www.luogu.com.cn/problem/P4721)

给出 $F(x)=\sum_{i\ge 0}f_ix^i$，求多项式 $G(x)=\sum_{i\ge 0}g_ix^i$ 满足

$$
\begin{gathered}
    g_0=1
    \\
    g_n=\sum_{i=1}^ng_{n-i}f_i
\end{gathered}
$$

我们发现，这题的贡献方式是：$g_i\to g_j(i<j)$，如果我们求得了 $g_i$，把它贡献到 $g_j$，这种问题很像 CDQ 分治：计算左区间；算左区间对右区间的贡献；计算右区间。时间复杂度 $O(n\log^2n)$。

还有比如计算 $G(x)=\exp F(x)$，除了可以用牛迭外，我们还可以如下计算：两边求导，得

$$
\begin{gathered}
    G'(x)=F'(x)\exp F'(x)=F'(x)G(x)
    \\
    [x^{n-1}]G'(x)=[x^{n-1}]F'(x)G(x)
    \\
    n\cdot g_n=\sum_{i=0}^{n-1}(i+1)f_{i+1}g_{n-1-i}
\end{gathered}
$$

于是我们得到了递推式：$g_n=\frac{1}{n}\sum_{i=1}^nif_ig_{n-i}$。用分治 FFT 即可 $O(n\log^2n)$ 求出。

## 类型2

比如 command_block 的博客里这道题：

已知

$$
\begin{gathered}
    g_0=0
    \\
    g_n=\sum_{i=1}^{n-1}f_ig_{n-i}
    \\
    f_n=\oplus_{i=1}^ng_i
\end{gathered}
$$
也就是 $f,g$ 要相互推导，$f_n$ 需要通过 $g$ 的 $[0,n]$ 项推出。

在类型 1 中，我们的推导方式是：

$$
g[l,m)*f[0,r-l)\to g[m,r)
$$

这个式子，当 $r-l-1<l$ 即 $r < 2l$ 时是正确 的，根据每层分治的区间选取的特性（每层区间应该类似于 $[0,x),[x,2x),\cdots$），当且仅当 $l=0$ 时该式不成立。我们分两种方式转移：

- 当 $l=0$，我们只能计算

$$
g[0,m)*f[0,m)\to g[m,r)
$$

我们发现 

$$
g[0,m)*f[m,r-l)\to g[m,r)
$$

的贡献漏去了。但是 $g_{m+1}$ 是正确的。

- 当 $l>0$，我们先和 类型1 一样

$$
g[l,m)*f[0,r-l)\to g[m,r)
$$

然而我们还要补充一句

$$
f[l,m)*g[0,r-l)\to g[m,r)
$$

这是在补充 $l=0$ 时的贡献。容易发现这样就可以贡献完全。