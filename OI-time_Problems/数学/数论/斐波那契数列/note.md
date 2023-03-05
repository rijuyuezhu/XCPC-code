<https://www.cnblogs.com/cyx0406/p/fibonacci.html>

# 斐波那契数列

## 1. 数列相关

### 1.1 递归定义

$$
\begin{gathered}
    f_0=f_1=1,f_n=f_{n-1}+f_{n-2}(n\ge 2)
\end{gathered}
$$

### 1.2 通项公式

通过生成函数、特征方程等方式，有：

令 $\phi=\dfrac{1+\sqrt 5}{2},\hat\phi=\dfrac{1-\sqrt 5}{2}$，则

$$
F_n=\dfrac{\sqrt 5}{5}(\phi^n-\hat\phi^n)
$$

### 1.3 矩阵形式

容易得到

$$
\begin{pmatrix}
    F_{n} \\ F_{n-1}
\end{pmatrix}
=
\begin{pmatrix}
    1 & 1
    \\
    1 & 0
\end{pmatrix}
\begin{pmatrix}
    F_{n-1} \\ F_{n-2}
\end{pmatrix}
$$

## 2. 数列性质

### 2.1 卡尼西恒等式

$$
F_{n-1}F_{n+1}-F_n^2=1
$$

### 2.2 附加性质

$$
F_{n+m}=F_mF_{n+1}+F_{m-1}F_n
$$

推论（令 $n=m$）

$$
F_{2n}=F_n(F_{n-1}+F_{n+1})
$$

### 2.3 求和

$$
\sum_{i=1}^nF_i=F_{n+2}-1
$$

$$
\sum_{i=1}^nF_{2i-1}=F_{2n}
$$

$$
\sum_{i=1}^nF_{2i}=F_{2n+1}-1
$$

$$
\sum_{i=1}^nF_i^2=F_nF_{n+1}
$$

### 2.4 数论性质

$$
\gcd(F_n,F_{n+1})=1
$$

$$
\gcd(F_n,F_m)=F_{\gcd(n,m)}
$$

第二条可以推出

$$
n|m\Leftrightarrow F_n|F_m
$$