# 类欧几里得算法

<https://www.luogu.com.cn/blog/Shuchong/qian-tan-lei-ou-ji-li-dei-suan-fa>

主要用来解决直线下整点问题。

比如

$$
    \sum_{i=0}^n \left\lfloor { \dfrac{ai+b}{c} } \right\rfloor
$$

## 前置知识

几个简易的转化：

1. “求和转化”

$$
    p = \sum_{i=1}^p 1
$$

2. “限制转化”

$$
\sum_{i=1}^n \sum_{j=1}^i f(i, j) = \sum_{j=1}^n\sum_{i=1}^n f(i,j) [j \le i]
$$

## 例题

### 例一

<https://www.luogu.com.cn/problem/P5170> 该题中的第一部分。

$$
    \begin{aligned}
    &       \sum_{i=0}^n \left\lfloor  {\dfrac{ai+b}{c} }  \right\rfloor
    \\=&    \sum_{i=0}^n \sum_{j=0}^{\lfloor  {\frac{ai+b}{c} }  \rfloor - 1} 1
    \\=&    \sum_{j=0}^{\lfloor \frac{an+b}{c} \rfloor - 1} \sum_{i=0}^n\left[j < \left\lfloor {\dfrac{ai+b}{c}} \right\rfloor  \right]
    \end{aligned}
$$

我们化简一下约束的不等式：

$$
\begin{aligned}
    &               j < \left\lfloor {\dfrac{ai+b}{c}} \right\rfloor
    \\\Rightarrow&  j+1\le \dfrac{ai+b}{c}
    \\\Rightarrow&  cj+c\le ai+b  
    \\\Rightarrow&  cj+c-1< ai+b
    \\\Rightarrow&  i > \dfrac{cj+c-b-1}{a}
    \\\Rightarrow&  i > \left\lfloor { \dfrac{cj+c-b-1}{a} } \right\rfloor
\end{aligned}
$$

把原式中的限制改成对 $i$ 的限制，有

$$
\begin{aligned}
      =&    \sum_{j=0}^{\lfloor \frac{an+b}{c}\rfloor -1}\sum_{i=0}^n \left[ i > \left\lfloor \dfrac {cj+c-b-1}{a} \right\rfloor\right]
    \\=&    \sum_{j=0}^{\lfloor \frac{an+b}{c}\rfloor-1}\sum_{i=\lfloor \frac{cj+c-b-1}{a}\rfloor+1}^n 1
    \\=&    \sum_{j=0}^{\lfloor \frac{an+b}{c}\rfloor-1} \left( {n - \left\lfloor \dfrac {cj+c-b-1}{a} \right\rfloor } \right)
    \\=&    \left\lfloor {\dfrac{an+b}{c}} \right\rfloor \cdot n - \sum_{j=0}^{\lfloor \frac{an+b}{c}\rfloor-1} {\left\lfloor \dfrac {cj+c-b-1}{a} \right\rfloor}
\end{aligned}
$$

我们发现，令 $n'=\lfloor \frac{an+b}{c}\rfloor-1$，$a'=c$，$b'=c-b-1$，$c'=a$，则后半部分为

$$
\sum_{j=0}^{n'}  \left\lfloor {\dfrac{a'j+b'}{c'}} \right\rfloor
$$

于是可以递归求解。