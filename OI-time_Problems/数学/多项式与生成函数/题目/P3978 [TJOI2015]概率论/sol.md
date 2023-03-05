设 $f_n$ 为 $n$ 个点的二叉树数量， $g_n$ 为 $n$ 个点的二叉树的叶子总数量，而 $F,G$ 分别是这两个序列的 OGF。

对于 $f$，我们有

$$
f_n=\sum_{i=0}^{n-1}f_if_{n-i-1}，f_0=1
$$

就是 Catalan 数，故 $F(x)=\dfrac{1-\sqrt {1-4x}}{2x}$。

而对于 $g$ 我们有

$$
\begin{aligned}
    g_n=&\sum_{i=0}^{n-1}(g_if_{n-i-1}+f_ig_{n-i-1})
    \\=&2\sum_{i=0}^{n-1}(g_if_{n-i-1})
    \\& (n \ge 2)
\end{aligned}
$$

稍加生成函数推导，我们可以得到

$$
G(x)=x+2xG(x)F(x)
$$

化简，并将 $F(x)$ 代入得

$$
G(x)=\dfrac{x}{\sqrt {1-4x}}
$$

暴力广义二项式定理展开：

$$
\begin{aligned}
    G(x)=&x\sum_{k=0}^{\infin}\binom{-1/2}{k}(-4x)^k
    \\
    g_n=&\binom{-1/2}{n-1}(-4)^{n-1}
    \\=&\dfrac{(-1/2)^{\underline{n-1}}(-1)^{n-1}2^{2(n-1)}}{(n-1)!}
    \\=&\dfrac{(2n-3)!!2^{n-1}}{(n-1)!}
    \\=&\dfrac{(2n-2)!}{(n-1)!(n-1)!}
    \\=&\binom{2n-2}{n-1}
\end{aligned}
$$

故期望为

$$
\begin{aligned}
    \dfrac{g_n}{f_n}=\dfrac{n(n+1)}{2(2n-1)}
\end{aligned}
$$