# 多项式快速插值

给出 $n$ 个点 $(x_i,y_i),0\le i < n$，插出一个 $n-1$ 次多项式 $f(x)$。

首先有 $O(n^2)$ 算法：

拉格朗日插值公式：

$$
f(x)=\sum_{i=0}^{n-1}y_i\prod_{j\ne i}\dfrac{x-x_j}{x_i-x_j}
$$

然而无法通过本题 $n\le 1\times 10^5$ 的数据。

接下来进行一通推导：

$$
\begin{aligned}
    f(x)=\sum_{i=0}^{n-1}\underbrace{\dfrac{y_i}{\prod_{j\ne i}(x_i-x_j)}}\prod_{j\ne i}(x-x_j)
\end{aligned}
$$

关注到大括号部分，分子是 $y_i$ 对于每个特定的 $i$ 是常数，而分母

$$
\prod_{j\ne i}(x_i-x_j)
$$

设

$$
g(x)=\prod_{j=0}^n(x-x_j)
$$

则分母可以写成

$$
\dfrac{g(x)}{x-x_i}\left(x\to x_i\right)
$$

是 $\frac{0}{0}$ 型，进行洛必达法则，得到上式等于

$$
\lim_{x\to x_i}\dfrac{g(x)}{x-x_i}=g'(x_i)
$$

而 $g$ 容易分治 NTT 算出，$g'$ 可以算出，再 $O(n\log^2 n)$ 多点求值即可得到 $g'(x_i)$。

接下来考虑怎么得到 $f$。

$$
f(x)=\sum_{i=0}^{n-1}\dfrac{y_i}{g'(x_i)}\prod_{j\ne i}(x-x_j)
$$

考虑用分治解决，设

$$
f_{l,r}(x)=\sum_{i=l}^{r}\dfrac{y_i}{g'(x_i)}\prod_{j=l}^r[j\ne i](x-x_j)
$$

然后，拆！（设 $L=[l,mid],R=(mid,R]$）

$$
\begin{aligned}
&f_{l,r}(x)
\\=&\sum_{i=l}^{r}\dfrac{y_i}{g'(x_i)}\prod_{j=l}^r[j\ne i](x-x_j)
\\=&\prod_{j\in R}(x-x_j)\sum_{i\in L}\dfrac{y_i}{g'(x_i)}\prod_{j\in L,j\ne i}(x-x_j)
\\+&\prod_{j\in L}(x-x_j)\sum_{i\in R}\dfrac{y_i}{g'(x_i)}\prod_{j\in R,j\ne i}(x-x_j)
\\=&g_R(x)f_L(x)+g_L(x)f_R(x)
\end{aligned}
$$

这个 $g$ 刚好废物利用qwq。

总时间复杂度为 $O(n\log^2 n)$。