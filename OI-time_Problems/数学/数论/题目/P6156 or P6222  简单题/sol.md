见识一下线性筛的强大之处。

惯例推式子：


$$
\begin{aligned}
    &\sum_{i=1}^n \sum_{j=1}^n (i+j)^k f(\gcd(i, j)) \gcd(i,j)
    \\=&\sum_{d=1}^n f(d) d \sum_{i=1}^n \sum_{j=1}^n (i+j)^k [\gcd(i,j)=d]
    \\=&\sum_{d=1}^n f(d) d^{k+1} \sum_{i=1}^{n/d} \sum_{j=1}^{n/d} (i+j)^k [\gcd(i,j)=1]
    \\=&\sum_{d=1}^n f(d) d^{k+1} \sum_{i=1}^{n/d} \sum_{j=1}^{n/d} (i+j)^k \sum_{t|i,t|j}\mu(t)
    \\=&\sum_{d=1}^n f(d) d^{k+1} \sum_{t=1}^{n/d} \mu(t) t^k \sum_{i=1}^{n/dt} \sum_{j=1}^{n/dt}(i+j)^k
\end{aligned}
$$

令 $S(n)=\sum_{i=1}^n \sum_{j=1}^n (i+j)^k$

则

$$
\begin{aligned}
    =&\sum_{d=1}^n f(d) d^{k+1} \sum_{t=1}^{n/d} \mu(t) t^k S(n/dt)
    \\=&\sum_{T=1}^n S(n/T) \sum_{d|T} f(d)d^{k+1} \mu(T/d) (T/d)^k
    \\=&\sum_{T=1}^n T^k S(n/T) \sum_{d|T} f(d)d\mu(T/d)
\end{aligned}
$$

令 $F(n)=\sum_{d|n} f(d)d\mu(n/d)$，则

$$
\begin{aligned}
    =&\sum_{T=1}^n F(T)T^k S(n/T)
\end{aligned}
$$

若可以预处理 $F$ 和 $S$ 的前 $n$ 项值，则可以 $O(\sqrt n)$ 整除分块完成一次询问（虽然本题没有多次询问）。

先看 $S$：

$$
    \begin{aligned}
        S(n) =& \sum_{i=1}^n \sum_{j=1}^n (i+j)^k
        \\=&S(n-1) + \sum_{i=1}^n (i+n)^k + \sum_{i=1}^{n-1} (i+n)^k
    \end{aligned}
$$

可以前缀和，设 $T(n)=\sum_{i=1}^n i^k$

则 

$$
    S(n) = S(n-1) + T(2n) - T(n) + T(2n-1) - T(n)
$$

干脆累加，设 $U(n)=\sum_{i=1}^n T(n)$，得到

$$
    S(n) = U(2n) - 2U(n)
$$

而 $i^k$ 可以线性筛得出（完全积性函数，$i^k=(i/p)^kp^k$），故 $T,U,S$ 前 $n$ 项均可 $O(n)$ 求出。

那么 $F$ 呢？

$$
    F(n)=\sum_{d|n} f(d)d\mu(n/d)
$$

注意到 $f(d)=\mu^2(d)$，得到

$$
    F(n)=\sum_{d|n} \mu^2(d)d\mu(n/d)
$$

它大体上可以看成 $\mu^2(n)n$ 和 $\mu(n)$ 卷到一起得到的。这两部分都是积性的，故得到的 $F(n)$ 也是积性的。它能不能线性筛，关键在于它素数的幂处的取值能否快速算出。

$$
    F(p^t)=\sum_{i=0}^t \mu^2(p^i)p^i\mu(p^{t-i})
$$

对于 $i\ge 2$ 或 $i\le t-2$ 的情况没有贡献。故若 $t\ge 3$，$F(p^t)=0$。

继续分类讨论：

- 若 $t=0$，$F(1)=1$；
- 若 $t=1$，$F(p)=p-1$；
- 若 $t=2$，$F(p^2)=-p$。

维护最小质因数即可
