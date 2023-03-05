先考虑无标号有根树计数

## 无标号有根树计数

设 $n$ 个点的无标号有根树（非空树）的 OGF 为 $F(x)=\sum_{i=1}^nf_ix^i$，则有

$$
F(x)=x\prod_{i=1}\left(\dfrac{1}{1-x^i}\right)^{f_i}
$$

解释一下：一个无标号有根树（以下简称树）由一个根节点和其下连的一片无标号有根树的森林构成。后面那部分，先是枚举大小为 $i$ 的连通块，枚举**同一种方案**的连通块个数为 $0\sim \infty$ 个，所以这部分的生成函数为 $\sum_{j=0}x^{ij}=\dfrac{1}{1-x^i}$。然后有 $f_i$ 种方案，故外面乘方 $f_i$。

定义这个操作为 Euler 变换，即

$$
\mathcal E(F(x))=\prod_{i=1}\left(\dfrac{1}{1-x^i}\right)^{f_i}
$$

它类似于有标号计数里的 Exp，是求若干个对象构成的**集合**。

我们可以把它变个形，设 $G(x)=\mathcal E(F(x))$，则

$$
\ln G(x)=-\sum_{i=1}f_i\ln(1-x^i)
$$

两边求导，得

$$
\begin{aligned}
\dfrac{G'(x)}{G(x)}=
&
\sum_{i=1}f_i\dfrac{ix^{i-1}}{1-x^i}
\\=&
\sum_{i=1}f_i\sum_{j=0}ix^{i(j+1)-1}
\end{aligned}
$$

再积分，得到

$$
\begin{aligned}
    \ln G(x)=
    &
    \sum_{i=1}f_i\sum_{j=1}\dfrac{x^{ij}}{j}
    \\=&
    \sum_{j=1}\dfrac{1}{j}\sum_{i=1}f_i(x^j)^i
    \\=&
    \sum_{j=1}\dfrac{F(x^j)}{j}
\end{aligned}
$$

所以

$$
\mathcal E(F(x))=\exp\left(\sum_{j=1}\dfrac{F(x^j)}{j}\right)
$$

---

回到本题，我们得到式子

$$
F(x)=x\cdot \mathcal E(F(x))
$$

### 思路1，分治FFT
施用 $\vartheta$ 算子，得到
$$
\begin{aligned}
    \vartheta F(x)=
    &
    x\cdot \mathcal E(f(x))\cdot \left(1+\sum_{j=1}x^jF'(x^j)\right)
    \\=&
    F(x)+F(x)\underline{\left(\sum_{j=1}x^jF'(x^j)\right)}
\end{aligned}
$$

令 $G(x)$ 为上文的划线部分，则

$$
\begin{aligned}
    G(x)=&\sum_{i=1}x^iF'(x^i)
    \\=&
    \sum_{i=1}\vartheta F(x^i)
\end{aligned}
$$

则

$$
\begin{aligned}
    g_n
    &
    =\sum_{i=1}[x^n]\sum_{j=1}jf_jx^{ij}
    \\=&
    \sum_{j|n}jf_j
\end{aligned}
$$

那么回到

$$
\vartheta F(x)=F(x)+F(x)G(x)
$$

我们得到

$$
\begin{gathered}
n\cdot f_n=f_n+\sum_{i=0}^nf_ig_{n-i}
\\
f_n=\dfrac{1}{n-1}\sum_{i=1}^{n-1}f_ig_{n-i}
\end{gathered}
$$

当然，还有

$$

\begin{gathered}
g_n=\sum_{i|n}if_i
\\
f_0=0,f_1=1   
\end{gathered}
$$
可以分治 FFT 解决，时间复杂度 $O(n\log^2n)$，常数较小。

### 思路2 牛迭

我们还是回到这个方程：

$$
F(x)=x\cdot \mathcal E(F(x))=x\cdot \exp\left(\sum_{i=1}\dfrac{F(x^i)}{i}\right)
$$
稍微变形

$$
\ln\dfrac{F(x)}{x}=\sum_{i=1}\dfrac{F(x^i)}{i}
$$
令

$$
H(F(x))=\ln\dfrac{F(x)}{x}-\sum_{i=1}\dfrac{F(x^i)}{i}
$$

比如我们已经求出了一个 $F_0(x),H(F_0(x))\equiv 0\pmod{x^n}$，
要求 $F(x),H(F(x))\equiv 0\pmod {x^{2n}}$。

我们观察到，当 $i\ge 2$ 时，因为 $F_0(x)$ 的前 $n$ 项已知，故 $F(x^i)\bmod {x^{2n}}$ 完全可以由 $F_0(x)$ 推出，故在对 $F(x)$ 求导时可以视作常数，且完全可以用 $F_0(x^i)$ 代替。故牛迭得到

$$
F(x)=F_0(x)-\dfrac{\ln\dfrac{F_0(x)}{x}-F_0(x)-\sum_{i=2}\frac{F_0(x^i)}{x}}{\frac{1}{x}\cdot \frac{x}{F_0(x)}-1}
$$

为了方便写，可以对 $F(x)/x$ 进行迭代。

时间是 $O(n\log n)$ 的，但常数巨大。
## 无标号无根树计数

我们只考虑根是重心的方案数。为什么可以这样做？这样可以保证不会重复计数。

- 每个无根树都有重心，于是都能对应上一棵以重心为根的有根树。
- 任意两棵以重心为根的有根树若本质不同，则它们对应的无根树也本质不同。

所以最后的答案就是（无标号有根树的个数）-（不以重心为根的有根树的个数）。

分两种情况：

- $n$ 是奇数，重心唯一，直接计算：

$$
f_n-\sum_{i=\lfloor n/2 \rfloor+1}^{n-1}f_if_{n-i}
$$

- $n$ 是偶数，可能存在两个重心，这时有一条边连接两个大小为 $n/2$ 的子树。如果两部分相同，则不会多少；如果不同，则会多算，于是要多减去

$$
\binom{f_{n/2}}{2}
$$