# 多项式 学习笔记

**2021/1/28** 终于下定决心学多项式了。。

[多项式与生成函数学习笔记](https://www.cnblogs.com/lsq147/p/13798943.html)

[Karry5307's Blog](https://karry5307.github.io/)

## FFT & NTT

[多项式乘法(FFT/NTT)](https://blog.csdn.net/qq_41996523/article/details/113348016)



## 任意模数NTT（MTT）

[P4245 【模板】任意模数多项式乘法](https://www.luogu.com.cn/problem/P4245)

>  给 2 个多项式 $F(x),G(x)$，求 $F(x)G(x)$。系数对 $p$ 取模，不保证 $p$ 是 NTT 模数。

也就是MTT，使用 4 次 FFT 完成任意模数的多项式乘法。

设 $K=2^{15}$，我们把多项式每项系数分为两部分（高低位）。 
$$
F(x)=K\cdot F_1(x)+F_0(x)
\\
G(x)=K\cdot G_1(x)+G_0(x)
\\
\therefore
F(x)G(x)=K^2\cdot F_1(x)G_1(x)+K\cdot [F_1(x)G_0(x)+F_0(x)G_1(x)]+F_0(x)G_0(x)
$$
如何快速得到这四个多项式的点值表示？

构造
$$
P(x)=F_0(x)+iG_0(x)
\\
Q(x)=F_0(x)-iG_0(x)
$$
我们惊奇地发现：
$$
\mathrm{DFT}(P)[j]=P(w_n^j)=F_0(w_n^j)+iG_0(w_n^j)
\\
=\sum_{k=0}^{n-1}F_0[k]w_n^{kj}+i\sum_{k=0}^{n-1}G_0[k]w_n^{kj}
\\
=\sum_{k=0}^{n-1}(F_0[k]+iG_0[k])(\cos(\dfrac {2\pi kj}{n})+i\sin(\dfrac{2\pi kj}n))
\\
=\sum_{k=0}^{n-1}(F_0[k]\cos(\dfrac{2\pi kj}n)-G_0[k]\sin(\dfrac {2\pi kj}n))+\\
i\sum_{k=0}^{n-1}(F_0[k]\sin(\dfrac {2\pi kj}n)+G_0[k]\sin(\dfrac {2\pi kj}n))
$$


同理
$$
\mathrm{DFT}(Q)[n-j]=P(w_n^{-j})=F_0(w_n^{-j})-iG_0(w_n^{-j})
\\
=\sum_{k=0}^{n-1}F_0[k]w_n^{-kj}-i\sum_{k=0}^{n-1}G_0[k]w_n^{-kj}
\\
=\sum_{k=0}^{n-1}(F_0[k]-iG_0[k])(\cos(\dfrac {2\pi kj}{n})-i\sin(\dfrac{2\pi kj}n))
\\
=\sum_{k=0}^{n-1}(F_0[k]\cos(\dfrac{2\pi kj}n)-G_0[k]\sin(\dfrac {2\pi kj}n))+\\
i\sum_{k=0}^{n-1}(F_0[k]\sin(\dfrac {2\pi kj}n)+G_0[k]\sin(\dfrac {2\pi kj}n))
$$
故 $P$ 的第 $j$ 项点值与 $Q$ 的第 $n-j$ 项点值共轭。

于是我们可以使用 1 次 FFT 得到 $P(x)$ 和 $Q(x)$ 的点值，再解方程就可得到 $F_0(x)$ 和 $G_0(x)$ 的点值。

同样地可得到 $F_1(x),G_1(x)$，使用了 2 次FFT。

然后考虑怎么求解 回系数。

构造
$$
P(x)=F_1(x)G_1(x)+i(F_1(x)G_0(x)+F_0(x)G_1(x))
\\
Q(x)=F_0(x)G_0(x)
$$
做两次 IDFT 即可。	

## 多项式乘法逆

[P4238 【模板】多项式乘法逆](https://www.luogu.com.cn/problem/P4238)

> 已知 $F(x)$，要求 $G(x)$，使得 $F(x)G(x)\equiv 1\pmod {x^n}$
>
> 保证 $F[0]\ne 0$。系数对 998244353取模。

我们采用倍增的思想。

假设我们已知多项式 $G_0(x)$ 满足：

$$
G_0(x)F(x)\equiv 1\pmod{x^{n/2}}​
$$
又 
$$
G(x)F(x)\equiv 1\pmod {x^{n/2}}​
$$
则由于 $F(x)\not\equiv 0\pmod{x^{n/2}}$，作差得

$$
G(x)-G_0(x)\equiv 0\pmod{x^{n/2}}​
$$
平方得

$$
G^2(x)-2G_0(x)G(x)+G_0^2(x)\equiv 0\pmod{x^n}​
$$
则
$$
G^2(x)\equiv 2G_0(x)G(x)-G_0^2(x)\pmod {x^n}
$$
两边同乘 $F(x)$ ,由于 $G(x)F(x)\equiv 1\pmod {x^n}$，得

$$
G(x)\equiv 2G_0(x)-F(x)G_0^2(x)\equiv G_0(x)[2-F(x)G_0(x)]\pmod {x^n}​
$$

这就是递归计算式了。使用NTT转成点值进行计算。

最后的终止条件为 $F[0]\equiv (G[0])^{-1}$。

**多项式有逆的充要条件是常数项有乘法逆。**

时间复杂度：

$$
T(n)=T(n/2)+O(n\log n)​\\
T(n)=O(n\log n)​
$$

## 多项式除法 & 取模

[P4512 【模板】多项式除法](https://www.luogu.com.cn/problem/P4512)

>  已知 $n$ 次多项式 $F(x)$ 和 $m$ 次多项式  $G(x)$ ，求 $Q(x)$，$R(x)$ 满足
>
>  1. $Q(x)$ 的度数为 $n-m$，$R(x)$ 的度数 $<m$
>  2. $F(x)=Q(x)G(x)+R(x)$
>
>  对 998244353 取模

不妨就认为 $\mathrm{deg}\ R(x)=m-1$，最高位用 $0$ 补齐。

定义 $A_T(x)=x^{\mathrm{deg}\ A(x)}A(\dfrac 1 x)$，可以发现 $A_T(x)$ 就是把 $A(x)$ 的系数反过来的多项式。

故有 
$$
F(\dfrac 1x)=Q(\dfrac 1x)G(\dfrac 1 x)+R(\dfrac 1x)
\\
x^nF(\dfrac 1x)=x^{n-m}Q(\dfrac 1x)\cdot x^mG(\dfrac 1x)+x^{n-m+1}\cdot x^{m-1}R(\dfrac 1x)
\\
F_T(x)=Q_T(x)G_T(x)+x^{n-m+1}R_T(x)
\\
F_T(X)=Q_T(x)G_T(x) \pmod{x^{n-m+1}}
\\
Q_T(x)=\dfrac {F_T(x)}{G_T(x)}\pmod {x^{n-m+1}}
$$
又由于 $\mathrm{deg}\ Q(x)=n-m<n-m+1$，所以得到的结果是正确的。

然后 $R(x)=F(x)-Q(x)G(x)$。

## 多项式ln

[P4725 【模板】多项式对数函数（多项式 ln）](https://www.luogu.com.cn/problem/P4725)

> 已知 $F(x)$，求 $G(x)\equiv\ln F(x)\pmod{x^n}$。
>
> 保证 $F[0]=1$。对 998244353 取模

这怎么求呢？我们可以先求微，得
$$
dG(x)\equiv d\ln F(x)\equiv \dfrac{F'(x)dx}{F(x)}\pmod{x^{n}}​
$$
再两边积分得 
$$
G(x)\equiv\ln F(x)\equiv\int_0^x\dfrac{F'(x)dx}{F(x)}\pmod {x^n}
$$
而 $G[0]\equiv  \ln F[0]$.

当 $F[0]=1$ 时，$G[0]\equiv0$；

当 $F[0]\ne 1$ 时，$G[0]\equiv \ln a(a\ne 1\wedge a\in\mathbb N_+)\not\in \mathbb Q$，在模意义下没有意义。

这也是题目要保证 $F[0]=1$ 的原因。

时间复杂度为 $O(n\log n)$


## 泰勒展开

在进入 exp 前，我们先来看看泰勒展开 &牛顿迭代

对于一个函数 $f(x)$，我们可以利用其在 $x=x_0$ 处的多阶导函数的值来多项式逼近 $f(x)$。
$$
f(x)=f(x_0)+\dfrac{f'(x_0)}{1!}(x-x_0)+\dfrac{f''(x_0)}{2!}(x-x_0)^2+\cdots+\dfrac{f^{(n)}(x_0)}{n!}(x-x_0)^n+\cdots
$$
怎么理解？我们不妨让右边那串为 $g(x)$，验证可知：
$$
f(x_0)=g(x_0)\\
f'(x_0)=g'(x_0)\\
\cdots\\
f^{(n)}(x_0)=g^{(n)}(x_0)\\
\cdots
$$
这就叫 “逼近”。

## 牛顿迭代（多项式复合求根）

> 已知 $G(x)$，求 $F(x)$使 $G(F(x))\equiv 0\pmod {x^n}$

考虑使用倍增法。假如我们已经知道了 $G(F_0(x))\equiv 0\pmod {x^{n/2}}$。

将 $G(F(x))$ 在 $F(x)=F_0(x)$ 处泰勒展开，有

$$
G(F(x))=G(F_0(x))+G'(F_0(x))(F(x)-F_0(x))+\dfrac{G''(F_0(x))}{2!}(F(x)-F_0(x))^2+\cdots​
$$
又因为


$$
G(F(x))\equiv 0\pmod {x^n})\\
\mathrm{and}\\
F(x)-F_0(x)\equiv0\pmod {x^{n/2}}\\\Rightarrow(F(x)-F_0(x))^2\equiv 0\pmod {x^n}​
$$
代入得
$$
0\equiv G(F_0(x))+G'(F_0(x))(F(x)-F_0(x))\pmod {x^n}​
$$
移项得
$$
F(x)\equiv F_0(x)-\dfrac{G(F_0(x))}{G'(F_0(x))}\pmod {x^n}​
$$
这便是递推公式。

## 多项式exp

>   已知 $F(x)$，求 $G(x)\equiv\exp F(x)\pmod {x^n}$
>
>   保证 $F[0]=0$。

直接求并不好求，我们不妨先取对数。

$$
\ln G(x)-F(x)\equiv0\pmod{x^n}​
$$
直接套用牛顿迭代，令 $H(X)=\ln X-F(x)$。

则求解 
$$
H(G(x))\equiv 0\pmod {x^n}​
$$
则有

$$
G(x)\equiv G_0(x)-\dfrac{H(G_0(x))}{H'(G_0(x))}\\
\equiv G_0(x)-G_0(x)[\ln G_0(x)-F(x)]\\
\equiv G_0(X)[1-\ln G_0(x)+F(x)]
$$
而又有 $G[0]\equiv \exp{F[0]}$。

可以递归求解。看起来很麻烦，但时间复杂度还是 $O(n\log n)$ （虽然比较慢）。

类似地，由于 $G[0]\equiv \exp F[0]$，当 $F[0]\ne 0$ 时在模意义下无意义，所以题目保证了 $F[0]=0$。


## 多项式快速幂 1

[P5245 【模板】多项式快速幂](https://www.luogu.com.cn/problem/P5245)

> 已知 $F(x)$， 求 $G(x)\equiv F^k(x)\pmod {x^n}$
>
> **保证** $F[0]=1$。
>
> 答案对 998244353 取模

我们根据对数恒等式，
$$
F^k(x)\equiv\exp(k\ln F(x))
$$
先求$\ln$，再做数乘，再求$\exp$ 即可。时间复杂度 $O(n\log n)$。常数巨大。

从这里我们也知道了，多项式快速幂不符合费马小定理，指数应当 $\mod P$ 才对。

## 多项式快速幂 2

[P5273 【模板】多项式幂函数 (加强版)](https://www.luogu.com.cn/problem/P5273)

>  已知 $F(x)$，求 $G(x)\equiv F^k(x)$，对 998244353 取模。

如果 $F[0]\equiv 1$，那么直接仿照上面计算即可。如果$F[0]\not\equiv 1$，则需要进行一些转化。

找到 $F(x)$ 的第一项非零项 $a_tx^t$ ，把其提出，得到

$F(x)\equiv a_tx^tH(x)$，其中 $H[n]\equiv\dfrac {F[n+t]}{a_k}$。

则 $G(x)\equiv F^k(x)\equiv a_t^kx^{tk}H^k(x)$

$H^k(x)$ 再如上计算即可。值得注意的是，$H^k(x)$ 的 $k$ 应 $\bmod P$，而 $a_t^k$ 中的 $k$ 应 $\bmod \varphi(P)$


## 多项式开根

[P5205 【模板】多项式开根](https://www.luogu.com.cn/problem/P5205)

[P5277 【模板】多项式开根（加强版）](https://www.luogu.com.cn/problem/P5277)

> 已知 $F(x)$，求 $G(x)\equiv \sqrt{F(x)}\pmod {x^n}$.
>
> 保证 $F[0]$ 是模998244353意义下的二次剩余。
>
> 答案对 998244353 取模

你当然可以向下面讲到的多项式快速幂一样计算，但是那样太慢。

原式化为$G^2(x)-F(x)\equiv 0\pmod {x^n}$

牛顿迭代可得
$$
G(x)\equiv G_0(x)-\dfrac{G^2_0(x)-F(x)}{2G_0(x)}\equiv \dfrac{G_0(x)}2+\dfrac{F(x)}{2G_0(x)}​
$$
递归终点是 
$$
G[0]\equiv \sqrt{F[0]}\pmod p​
$$
这里给出加强版的代码（其中`Sqrt_P::solve(n)` 是求 $n$ 的 [二次剩余](https://blog.csdn.net/qq_41996523/article/details/113797568)）。

时间复杂度为 $O(n\log n)$	


## 多项式多点求值

矩阵转置的做法，在另一篇笔记里。

## 多项式快速插值

另一篇笔记。

