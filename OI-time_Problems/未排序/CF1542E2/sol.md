以下记号：$p_n$ 表示一个长度为 $n$ 的排列，$p_{[l,r]}$ 表示该排列的 $[l,r]$ 切片，$\sigma^p$ 表示排列的逆序对数。

所求答案为

$$
\begin{aligned}
    &
    \sum_{p_n}\sum_{q_n}[p<q][\sigma^p>\sigma^q]
    \\=&
    \sum_{p_n}\sum_{q_n}\sum_{i=1}^n[p_{[1,i-1]}=q_{[1,i-1]}][p_i<q_i][\sigma^p>\sigma^q]
    \\=&
    \sum_{i=1}^n\mathrm A_n^{i-1}\sum_{p_{n-i+1}}\sum_{q_{n-i+1}}[p_1<q_1][\sigma^p>\sigma^q]
    \\=&
    \sum_{i=1}^n\mathrm A_n^{i-1}f(n-i+1)
\end{aligned}
$$

其中 
$$
\begin{aligned}
    f(n)=
    &
    \sum_{p_n}\sum_{q_n}[p_1<q_1][\sigma^p>\sigma^q]
    \\=&
    \sum_{a=1}^n\sum_{b=a+1}^n\sum_{p_{n-1}}\sum_{q_{n-1}}[\sigma^{p}+a-1>\sigma^{q}+b-1]
    \\=&
    \sum_{a=1}^n\sum_{b=a+1}^n\sum_{p_{n-1}}\sum_{q_{n-1}}[\sigma^p-\sigma^q>b-a]
    \\=&
    \sum_{d=1}^{n-1}\sum_{p_{n-1}}\sum_{q_{n-1}}[\sigma^p-\sigma^q>d]\sum_{a=1}^n\sum_{b=a+1}^n[b-a=d]
    \\=&
    \sum_{d=1}^{n-1}(n-d)\sum_{p_{n-1}}\sum_{q_{n-1}}[\sigma^p-\sigma^q>d]
    \\=&
    \sum_{d=1}^{n-1}(n-d)g(n-1,d)
\end{aligned}
$$

其中

$$
\begin{aligned}
    g(n,d)=&
    \sum_{p_{n}}\sum_{q_{n}}[\sigma^p-\sigma^q>d]
    \\=&
    \sum_{a=1}^n\sum_{b=1}^n\sum_{p_{n-1}}\sum_{q_{n-1}}[\sigma^p+a-\sigma^q-b>d]
    \\=&
    \sum_{a=1}^n\sum_{b=1}^n\sum_{p_{n-1}}\sum_{q_{n-1}}[\sigma^p-\sigma^q>d+b-a]
    \\=&\sum_{a=1}^n\sum_{b=1}^ng(n-1,d+b-a)
    \\=&
    \sum_{a=1}^n\sum_{b=a+1}^n[g(n-1,d+b-a)+g(n-1,d+a-b)]+n\cdot g(n-1,d)
    \\=&
    \sum_{k=1}^{n-1}(n-k)[g(n-1,d+k)+g(n-1,d-k)]+n\cdot g(n-1,d)
    \\=&
    n\cdot g(n-1,d)+\sum_{k=1}^{n-1}(d-k+n-d)g(n-1,d-k)-\sum_{k=1}^{n-1}(d+k-d-n)g(n-1,d+k)
    \\=&
    n\cdot g(n-1,d)+\sum_{i=d-n+1}^{d-1}i\cdot g(n-1,i)+(n-d)\cdot \sum_{i=d-n+1}^{d-1}g(n-1,i)-\sum_{i=d+1}^{d+n-1}i\cdot g(n-1,i)+(n+d)\cdot \sum_{i=d+1}^{d+n-1}g(n-1,i)
\end{aligned}
$$

于是可以前缀和维护。

边界 

$$
\begin{gathered}
g(n,i)=0,i\ge \dfrac{n(n-1)}{2}
\\
g(n,i)=\left(\dfrac{n(n-1)}{2}+1\right)^2,i<-\dfrac{n(n-1)}{2}
\end{gathered}
$$

状态数有 $O(n^3)$，转移是 $O(1)$，总时间复杂度 $O(n^3)$。