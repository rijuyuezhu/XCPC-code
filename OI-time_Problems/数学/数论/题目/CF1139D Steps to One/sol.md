给一个数列，每次随机选一个 $1$ 到 $m$ 之间的数加在数列末尾，数列中所有数的 $\gcd=1$ 时停止，求期望长度。

设 $f(i)$ 为当序列的 $\gcd = i$ 时，使得 $\gcd=1$ 还需加的数的数量。

则答案为

$$
ans=1+\dfrac 1m \sum_{i=1}^m(f(i))
$$

而 $f$ 的转移为

$$
f(i)=1+\dfrac 1 m \sum_{j=1}^mf(\gcd(i,j))
$$

当然，$f(1)=0$。

于是开始反演大法：

先单独拎出 $\sum_{j=1}^m f(\gcd(i,j))$ 看

$$
\begin{aligned}
    g(i)=&\sum_{j=1}^m f(\gcd(i,j))
        \\=&\sum_{d=1}^mf(d)\sum_{j=1}^m[\gcd(i,j)=d]
        \\=&\sum_{d=1}^m f(d) \sum_{j=1}^m \sum_{t:dt|i,dt|j}\mu(t)
        \\=&\sum_{d=1}^m f(d) \sum_{t:dt|i} \mu(t) \left\lfloor\dfrac{m}{dt}\right\rfloor
        \\=&\sum_{T|i}\left\lfloor\dfrac{m}{T}\right\rfloor\sum_{d|T}f(d)\mu(T/d)
\end{aligned}
$$

故 

$$
\begin{aligned}
    f(i)=&1+\dfrac{1}{m}g(i)
    \\=&1+\dfrac 1 m \left(\sum_{T|i}\left\lfloor\dfrac{m}{T}\right\rfloor\sum_{d|T}f(d)\mu(T/d)\right)
\end{aligned}
$$

发现等号两边都有 $f(i)$，我们提出来

$$
\begin{aligned}
    f(i)=&1+\dfrac 1 m \left(\sum_{T|i}\left\lfloor\dfrac{m}{T}\right\rfloor\sum_{d|T}f(d)\mu(T/d)\right)
    \\=&1+\dfrac{1}{m}\left(\left\lfloor\dfrac{m}{i}\right\rfloor f(i)+\sum_{T|i}\left\lfloor\dfrac{m}{T}\right\rfloor\sum_{d|T}f(d)\mu(T/d)[T\ne i \vee d\ne T]\right)
\end{aligned}
$$

这是因为 $d|T|i$，要 $d=i$ 仅当 $d=T=i$。

简单地解个方程，得到

$$
    f(i)=\dfrac{1}{m-\lfloor\frac{m}{i}\rfloor}\left(m+\sum_{T|i}\left\lfloor\dfrac{m}{T}\right\rfloor\sum_{d|T}f(d)\mu(T/d)[T\ne i \vee d\ne T]\right)
$$

设 $F(n)=\sum_{d|n}f(d)\mu(n/d)$。我们动态维护 $F(n)$，每算出一个 $f(i)$ 就进行狄利克雷卷积的按倍数贡献，而 $f(i)$ 可以枚举因数求解。适当安排顺序，可以使得约束条件恰好满足。时间复杂度 $O(n\log n)$。