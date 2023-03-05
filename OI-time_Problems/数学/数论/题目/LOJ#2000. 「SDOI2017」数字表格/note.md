<https://loj.ac/p/2000>

下文为方便描述，用 $\operatorname{pow}(a,n)$ 表示 $a^n$。
题目所求即为 

$$
\begin{aligned}
    &\prod_{i=1}^n\prod_{j=1}^mf(\gcd(i,j))
    \\
    =&\prod_{t=1}^{\min(n,m)}\operatorname{pow}\left(f(t),\sum_{i=1}^n\sum_{j=1}^m[\gcd(i,j)=t]\right)
    \\
    =&\prod_{t=1}^{\min(n,m)}\operatorname{pow}\left(f(t),\sum_{d=1}^{\min(n/t,m/t)}\mu(d)\left\lfloor\dfrac{n}{dt}\right\rfloor\left\lfloor\dfrac{m}{dt}\right\rfloor\right)
    \\
    =&\prod_{t=1}^{\min(n,m)}\operatorname{pow}\left(f(t),\sum_{t|T}\mu(\dfrac{T}{t})\left\lfloor\dfrac{n}{T}\right\rfloor\left\lfloor\dfrac{m}{T}\right\rfloor\right)
    \\
    =&\prod_{T=1}^{\min(n,m)}\operatorname{pow}\left(\prod_{t|T}\operatorname{pow}\left(f(t),\mu(\dfrac{T}{t})\right),\left\lfloor\dfrac{n}{T}\right\rfloor\left\lfloor\dfrac{m}{T}\right\rfloor\right)
\end{aligned}
$$

令 

$$
g(n)=\prod_{t|n}\operatorname{pow}\left(f(t),\mu(\dfrac{n}{t})\right)
$$

则原式即为

$$
\prod_{T=1}^{\min(n,m)}\operatorname{pow}\left(g(T),\left\lfloor\dfrac{n}{T}\right\rfloor\left\lfloor\dfrac{m}{T}\right\rfloor\right)
$$

若求出 $g(T)$ 的前缀积，该式可直接整除分块。而 $g$ 可以直接枚举倍数得到。若把求逆元等操作视为 $O(1)$，总复杂度 $O(n\log n+T\sqrt n)$