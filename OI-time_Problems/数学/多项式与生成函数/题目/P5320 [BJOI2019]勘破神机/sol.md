我们先看看 $2\times n$ 的情况。

设 $f(n)$ 表示填充一块 $2\times n$ 的方案数，则有 $f(n)=f(n-1)+f(n-2),f(0)=f(1)=1$。

通项公式为

$$
f(n)=\dfrac{5+\sqrt 5}{10}\left(\dfrac{1+\sqrt 5}{2}\right)^n + \dfrac{5-\sqrt 5}{10}\left(\dfrac{1-\sqrt 5}{2}\right)^n
$$

不管怎样，简洁起见，设 $f(n)=Ax^n+By^n$。

则答案为

$$
\begin{aligned}
    &\dfrac{1}{r-l+1}\sum_{n=l}^r\binom{f(n)}{k}
    \\=&\dfrac{1}{r-l+1}\dfrac{1}{k!} \sum_{n=l}^r f^{\underline{k}}(n)
    \\=&\dfrac{1}{r-l+1}\dfrac{1}{k!} \sum_{n=l}^r \sum_{i=0}^k (-1)^{k-i}s(k,i) f^i(n)
    \\=&\dfrac{1}{r-l+1}\dfrac{1}{k!} \sum_{n=l}^r \sum_{i=0}^k (-1)^{k-i}s(k,i) (Ax^n+By^n)^i
    \\=&\dfrac{1}{r-l+1}\dfrac{1}{k!} \sum_{n=l}^r \sum_{i=0}^k (-1)^{k-i}s(k,i) \sum_{j=0}^i \binom{i}{j} A^jB^{i-j}(x^jy^{i-j})^n
    \\=&\dfrac{1}{r-l+1}\dfrac{1}{k!} \sum_{i=0}^k (-1)^{k-i}s(k,i) \sum_{j=0}^i \binom{i}{j} A^jB^{i-j}\sum_{n=l}^r(x^jy^{i-j})^n
\end{aligned}
$$

其中 $s(n,k)$ 为第一类斯特林数。

于是可以枚举 $l$ 和 $r$，然后后面 $n$ 的那个 $\sum$ 就是个等比数列求和。当然由于 $\sqrt 5$ 不存在，需要扩域计算。

而 $3\times n$ 的情况类似，首先，若 $n$ 是奇数，总块数是奇数，无解；

我们主要搞偶数的情况。设 $g(n)$ 为宽度为 $2n$ 的情况。

首先，若我们刚好填完一个 $3\times2$ 的矩形，这有 $3$ 种方法，则贡献为 $3g(n-1)$。

否则，有两种方法状态需要到前面所填的格子完成。我们枚举这样延伸需要到哪个块才能完成，则有

$$
g(n)=3g(n-1)+2\sum_{i=0}^{n-2}g(i)
$$

想办法求解它

$$
g(n-1)=3g(n-2)+2\sum_{i=0}^{n-3}g(i)
$$

两式相减得

$$
g(n)=4g(n-1)-g(n-2),g(0)=1,g(1)=3
$$

于是通项公式为

$$
g(n)=\dfrac{3+\sqrt 3}{6}\left(2+\sqrt 3\right)^n+\dfrac{3-\sqrt 3}{6}\left(2-\sqrt 3\right)^n
$$

 类似地，需要扩域计算。

