$$
\begin{aligned}
    &\sum_{i=1}^n\sum_{j=i+1}^n\operatorname{lcm}(A_i, A_j)
    \\
    =&\dfrac{1}{2}\left[\sum_{i=1}^n\sum_{j=1}^n\operatorname{lcm}(A_i,A_j)-\sum_{i=1}^n A_i\right]
\end{aligned}
$$

下面计算

$$
\begin{aligned}
    &\sum_{i=1}^n\sum_{j=1}^n\operatorname{lcm}(A_i, A_j)
    \\
    =&\sum_{i=1}^n\sum_{j=1}^n\dfrac{A_iA_j}{\gcd(A_i,A_j)}
    \\
    =&\sum_{d=1}^V\dfrac{1}{d}\sum_{i=1}^n\sum_{j=1}^nA_iA_j[\gcd(A_i,A_j)=d]
    \\
    =&\sum_{d=1}^V\dfrac{1}{d}\sum_{i=1}^n\sum_{j=1}^nA_iA_j\sum_{td|A_i,td|A_j}\mu(t)
    \\
    =&\sum_{d=1}^V\sum_{t=1}^{V/d}\dfrac{\mu(t)}{d}\left(\sum_{i=1}^nA_i[td|A_i]\right)^2
\end{aligned}
$$

设 
$$
\begin{aligned}
    f(x)&=\sum_{i=1}^n[x=A_i]A_i
    \\
    g(x)&=\sum_{i=1}^n[x|A_i]A_i
\end{aligned}
$$

则

$$
g(x)=\sum_{x|d}f(d)
$$

可 $O(n\log n)$ 求前 $n$ 项。

则原式为

$$
\sum_{d=1}^V\sum_{t=1}^{V/d}\dfrac{\mu(t)g^2(dt)}{d}
$$

可以 $O(V\log V)$ 求得。