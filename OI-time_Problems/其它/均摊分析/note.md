# 均摊分析 学习笔记

## 阅读材料

资料1 ：<http://ljt12138.github.io/2019/08/05/potential_analysis/>

资料2：陈胤伯ppt 《均摊分析简介》，uoj群里有。

## 均摊分析

三种方法：累积分析，会计分析，势能分析。重点讲讲势能分析。

在物理学中，对于做功与路径无关的力（保守力）可以定义势能 $\Phi$，对于势能的变化量，有：

$\Delta\Phi=\Phi_1-\Phi_0=-W$

均摊分析中我们引入 “势能” 的概念：对于一个数据结构 $D$，定义势函数 $\Phi(i)$ 表示当数据结构处于状态 $D_i$ 时的 “势能”。

第 $i$ 次操作由状态 $D_{i-1}$ 得到状态 $D_i$ 的均摊时间花费为

$$
\begin{aligned}
\alpha(i)+W&=c(i)
\\
\alpha(i)&=c(i)+\Phi(i)-\Phi(i-1)
\end{aligned}
$$

其中 $c(i)$ 是实际花费，$W$ 可以理解成额外花费。

对于上式两边求和，得到

$$
\begin{aligned}
    \sum \alpha(i)&=\sum c(i)+\Phi(n)-\Phi(0)
\end{aligned}
$$

$$
\begin{aligned}
    T(n)&=\sum c(i)
    \\&=\sum \alpha(i)+\Phi(0)-\Phi(n)
    \\&\le \sum \alpha(i)
\end{aligned}
$$

于是我们可以用 $\sum \alpha(i)$ 估计 $T(n)$ 的上界。
    
~~其实上面的东西可能并没什么用~~

## 一些使用均摊分析得到正确复杂度的数据结构

- Splay双旋（单次操作均摊 $O(\log n)$）
- LCT（单次操作均摊 $O(\log n)$）
- 并查集（路径压缩 **或** 按秩合并）（单次操作均摊 $O(\log n)$）
- 并查集（完全体）（单次操作均摊 $O(\alpha(n))$
- 替罪羊树（以及类似的结构）（单次操作均摊 $O(\log n)$）

## 一些常用的均摊分析结论

1. 一个数 $V$ 不停地被取 $\gcd$，只有 $O(\log V)$ 个取值。
    
    例题：<https://vjudge.net/problem/LibreOJ-576>

2. 一个数不停地开平方并下取整， $O(\log\log V)$ 次就会变为 1 或 0。
    
    例题：
    
    <https://www.luogu.com.cn/problem/P4145>
    
    <https://loj.ac/p/6281>
