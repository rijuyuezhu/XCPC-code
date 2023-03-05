看到斐波那契数列的最小公倍数，我们应该第一时间想到这样一个性质：

$$
\gcd(f_n,f_m)=f_{\gcd(n,m)}
$$

如何把 $\operatorname{lcm}$ 转化为 $\gcd$？这里需要应用 min-max 容斥。

> min-max 容斥
>
> 给出集合 $S=\{1,2,\cdots, n\}$ 和元素 $a_1,a_2,\cdots, a_n$，有 $\max_{i\in S}a_i=\sum_{T\subset S}(-1)^{|T|+1}\min_{i\in T}a_i$ （反之亦然）

而 $\gcd$ 可以看成是质因子指数上的 min。即设 $a_i=p_1^{a_{1i}}p_2^{a_{2i}}\cdots=\prod_jp_j^{a_{ji}}$ 则

$$
\begin{aligned}
    \gcd_{i\in S}a_i=&\prod_{j}p_j^{\min_{i\in S}a_{ji}}
    \\=&
    \prod_jp_j^{\sum_{T\subset S}(-1)^{|T|+1}\max_{i\in T}a_{ji}}
    \\=&
    \prod_{T\subset S}\left(\prod_jp_j^{\max_{i\in T}a_{ji}}\right)^{(-1)^{|T|+1}}
    \\=&
    \prod_{T\subset S}(\operatorname{lcm}_{i\in T}a_i)^{(-1)^{|T|+1}}
\end{aligned}
$$

反之亦然。

回归正题，我们有

$$
\begin{aligned}
    &\operatorname{lcm}_{i\in S}f(k_i)
    \\=&
    \prod_{T\subset S}(\gcd_{i\in T}f(k_i))^{(-1)^{|T|+1}}
    \\=&
    \prod_{T\subset S}f(\gcd_{i\in T}k_i)^{(-1)^{|T|+1}}
\end{aligned}
$$

然后 $f(\gcd k_i)$ 的形式是莫反的常见套路，设函数 $g(n)$ 满足 $f(n)=\prod_{d|n}g(d)$。（注意为了化形这里用的是连乘）。
故原式化为

$$
\begin{aligned}
    &\prod_{T\subset S}\left[ \prod_{d|\gcd_{i\in T}k_i}g(d) \right]^{(-1)^{|T|+1}}
    \\=&
    \prod_{d}g(d)^{A(d)}
\end{aligned}
$$

其中

$$
    A(d)=\sum_{T\subset S}[d|\gcd_{i\in T}k_i](-1)^{|T|+1}
$$

所以要计算指数，只要看有几个 $k_i$ 有 $d$ 这个因子。假如有 $m$ 个：

- 若 $m=0$，$A(d)=0$；
- 若 $m\ne 0$，贡献为 $A(d)=\sum_{i=1}^m\binom{m}{i}(-1)^{m+1}=1$。

所以只要枚举倍数计数即可。

题外话：如何计算 $g(n)$ 呢？由于

$$
f(n)=\prod_{d|n}g(d)
$$

类似于莫反的容斥，易得

$$
g(d)=\prod_{d|n}f(d)^{\mu(n/d)}
$$

同样可以枚举倍数算出。时间复杂度为 $O(n\log n)$。其中 $n$ 为值域。