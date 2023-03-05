参考资料：

[转置原理与多点求值 Sshwy's Notes](https://notes.sshwy.name/Math/Polynomial/Multi-Point-Eval/)

[多项式多点求值 JiaZP's blog](https://www.cnblogs.com/JiaZP/p/14187120.html)

[chasedeath's blog](https://www.cnblogs.com/chasedeath/p/13073178.html)

[_rqy的博客](https://_rqy.blog.uoj.ac/blog/6202)

## 转置原理（特勒根原理）

对于矩阵 $M$ 和向量 $v$，要计算 $Mv$，我们可以先考虑计算 ${M}^{T} {v}$。若其能快速计算，我们可以通过某种（下述）方法以相同的复杂度计算 $Mv$。

## 经典问题：多项式多点求值

给出一个 $n-1$ 次多项式 $F(x)=\sum_{i=0}^{n-1}f_ix^i$ 和 $n$ 个点的横坐标 $a_0,a_1,\cdots, a_{n-1}$，要求快速求出 $F(a_i)$。

本质上，我们要计算的是

$$
\begin{bmatrix}
    1 & a_0 & a_0^2 & \cdots & a_0^{n-1}
    \\
    1 & a_1 & a_1^2 & \cdots & a_1^{n-1}
    \\
    \vdots & \vdots & \vdots & \ddots & \vdots
    \\
    1 & a_{n-1} & a_{n-1}^2 & \cdots & a_{n-1}^{n-1}
\end{bmatrix}
\begin{bmatrix}
    f_0
    \\
    f_1
    \\
    \vdots
    \\
    f_{n-1}
\end{bmatrix}
=
\begin{bmatrix}
    F(a_0)
    \\
    F(a_1)
    \\
    \vdots
    \\
    F(a_{n-1})
\end{bmatrix}
$$

记矩阵为 $M$，向量为 $v$.我们发现这是不好求的；但是若要计算 ${M}^{T}{v}$，我们看看：

$$
{M}^{T}{ v}=
\begin{bmatrix}
    1 & 1 & 1 & \cdots & 1
    \\
    a_0 & a_1 & a_2 & \cdots & a_{n-1}
    \\
    \vdots & \vdots & \vdots & \ddots & \vdots
    \\
    a_0^{n-1} & a_1^{n-1} & a_2^{n-1} & \cdots & a_{n-1}^{n-1}
\end{bmatrix}
\begin{bmatrix}
    f_0
    \\
    f_1
    \\
    \vdots
    \\
    f_{n-1}
\end{bmatrix}
$$

则结果向量第 $k$ 项为 $\sum_{i=0}^{n-1}f_ia_i^k$，不妨把结果向量的生成函数写出：

$$
\begin{aligned}
    G(z)=&\sum_{k\ge 0}\sum_{i=0}^{n-1}f_ia_i^kz^k
    \\=&\sum_{i=0}^{n-1}\dfrac{f_i}{1-a_iz}
\end{aligned}
$$

第 $k$ 个点的结果就是 $[z^k]G(z)$。这个式子可以直接分治 FFT 在 $O(n\log^2n)$ 的时间内完成。

到此我们可以快速求出 ${M}^{T} v$，那么如何求出 $Mv$ 呢？接下来涉及到一些线性代数的知识。

## 转置原理

把 $M$ 看成常矩阵，则变换 ${v}\to {M}^{T}{v}$ 是线性的 。把 $M$ 分解成若干初等行变换矩阵的乘积，即$M=E_kE_{k-1}\dots E_1$，则 $M^{T}v=E_1^{T}E_{2}^T\dots E_{k}^{T}v$。我们容易得到，求 $M^Tv$ 的操作序列为 $E_k^T\to E_{k-1}^T\to \dots \to E_1^T$，而求 $Mv$ 的操作序列为 $E_1\to E_2\to \dots \to E_k$。所以，**只要把求** $M^Tv$ **的整个过程的顺序倒过来，并且每个变换变成其逆变换即可求解** $Mv$。

把变换变成逆变换，其实只有一种需要改变：

原来的操作是 $f\gets f + c\cdot g$（其中 $c$ 认为是常数）；

逆变换是 $g\gets g + c\cdot f$。

## 转置后的数列卷积

数列卷积 $g=f*c$ 本质上是这样一个过程：（假设我们把 $c$ 看成常数列，$f$ 为 $n-1$ 次，$c$ 为 $m-1$ 次，则 $g$ 为 $n+m-2$ 次）

$$
g_{i+j}\gets g_{i+j}+f_ic_j(0\le i< n,0\le j< m)
$$

转置后为 

$$
f_i\gets f_i+g_{i+j}c_j(0\le i< n,0\le j< m)
$$

或者写好一点（注意下式中 $n,m$ 意义与上式不同）

$$
f_k=\sum_{i-j=k}g_ic_j(0\le i< n,0\le j< m)
$$

这样求出的 $f$ 只需保留到 $n-m$ 次。

不妨记这个“卷积”为 $f=g\oplus c$。

## 转置前

首先，关于 $M^Tv$ 的求解，即多项式

$$
G(z)=\sum_{i=0}^{n-1}\dfrac{f_i}{1-a_iz}
$$

的求解，使用分治 FFT 过程如下：

设 

$$
\begin{aligned}
    \varphi_{l,r}(z)=&\prod_{i=l}^r(1-a_iz)
    \\
    H_{l,r}(z)=&\sum_{i=l}^{r}\dfrac{f_i\varphi_{l,r}(z)}{1-a_iz}
\end{aligned}
$$

对于每个节点求出 $(H_{l,r},\varphi_{l,r})$：

1. 若 $l=r$，则 
   
    $$
        \begin{aligned}
        \varphi_{l,r}=&1-a_lz
        \\
        H_{l,r}=&f_i
        \end{aligned}
    $$
2. 否则设 $L=[l,m],R=(m,r]$
   $$
        \begin{aligned}
            \varphi_{l,r}=&\varphi_L\cdot \varphi_R
            \\
            H_{l,r}=&H_L\varphi_R+H_R\varphi_L
        \end{aligned}
   $$

最后，$ans=H_{0,n-1}g^{-1}_{0,n-1}$ 

## 转置后

首先，由于我们认为 $M$ 是常量，故 **仅包含** $a_i$ **的式子**不需要使用转置原理，该怎么做怎么做。对应到上面的推导就是：$\varphi$ 是常量，$\varphi^{-1}$ 的求解不需要转置，只要正常写求逆。

我们的输入为 $v$，换句话说，多项式 $F(z)=\sum_{z=0}^{n-1}f_iz^i$。

对应转置前算法的最后一步，先让 $F\gets F\oplus \varphi^{-1}$（再说一次此处 $\varphi^{-1}$ 的求解不需要转置！）

然后是分治过程，初始 $H_{l,r}\gets F$；

1. 若 $l=r$，此时我们已经得到了 $F(a_l)=[z^0]H_{l,r}$，储存即可；
2. 否则，我们从上到下计算下层节点：

    由于 $\varphi$ 是常量，故 $\varphi$ 不会在此处计算（应该提前算好）；

    计算下层的 $H$：

    $$
        \begin{aligned}
            H_L=&H_{l,r}\oplus g_R
            \\
            H_R=&H_{l,r}\oplus g_L
        \end{aligned}
    $$

如果你不知道怎么判断从哪里得到答案，牢记一句话：

**从原来得到输入的地方得到现在的输出，从原来得到输出的地方得到现在的输入。**

## 其它注意的地方

这里特别说一下转置卷积：

$$
f_k=\sum_{i-j=k}g_ic_j,(0\le i< n, 0\le j< m)
$$

令 $d_i=c_{m-i-1}$，得到

$$
f_k=h_{m+k-1}=\sum_{i+j=m+k-1}g_id_i
$$

其中显然有 $h=g*d$。

要得到 $f_k(0\le k<n-m)$ 只需得到 $h_k(m-1\le k <n-1)$。注意到若选取卷积长度为 $n$，则循环溢出的部分（即对于 $i+j\ge n$ 的 $g_id_j$，它们会贡献到 $i+j-n<m-1$ 处），不影响最后的结果。可以直接选用卷积长度为 $n$。