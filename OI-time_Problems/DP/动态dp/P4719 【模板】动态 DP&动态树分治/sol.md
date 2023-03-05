# 动态dp 学习笔记

## 例题

> <https://www.luogu.com.cn/problem/P4719>
> 
> 求树上最大权值和独立集，带修。

如果不带修，这就是一道经典题（没有上司的舞会）。带修的话怎么办呢？如果是序列上，有一种经典做法：把 dp 转移式写成矩阵，线段树维护矩阵乘积即可。

我们把树上问题化为序列问题。

## 方法1

使用链剖分，把树分成若干重链，对每个重链维护矩阵。就以本题为例：

容易写出状态转移方程：

$$
\begin{aligned}
    f(u,0)=&\sum_{v\in son(u)}\max(f(v, 0), f(v, 1))
    \\
    f(v,1)=&\sum_{v\in son(u)}f(v, 0)+a_u
\end{aligned}
$$

如果 $v$ 只有一个，我们完全可以这样转移：

$$
\begin{bmatrix}
    f(u, 0)
    \\
    f(u, 1)
\end{bmatrix}
=
\begin{bmatrix}
    0 & 0
    \\
    a_u & -\infty
\end{bmatrix}
\begin{bmatrix}
    f(v, 0)
    \\
    f(v, 1)
\end{bmatrix}
$$

我们仅记录**重儿子**转移过来的矩阵，对于轻儿子直接定义

$$
\begin{aligned}
    g(u,0)=&\sum_{v\in lightson(u)}\max(f(v, 0), f(v, 1))
    \\
    g(u, 1)=&\sum_{v\in lightson(u)}f(v, 0)+a_u
\end{aligned}
$$

把轻儿子放到矩阵里去：

$$
\begin{bmatrix}
    f(u, 0)
    \\
    f(u, 1)
\end{bmatrix}
=
\begin{bmatrix}
    g(u,0) & g(u,0)
    \\
    g(u,1) & -\infty
\end{bmatrix}
\begin{bmatrix}
    f(v, 0)
    \\
    f(v, 1)
\end{bmatrix}
$$

于是：每次修改会修改重链上的某点，进而影响到其重链顶端的节点的矩阵，于是影响其父亲的 $g$。于是对于路上的每条重链，都要进行一次修改，时间复杂度 $O(n\log^2n)$。  

## 方法2

使用全局平衡二叉树进行维护。

全局平衡二叉树（静态 TopTree？）是一堆 BST 连接而成，就类似于 LCT 的那种连法，具有与 LCT 一样的性质，但实虚边划分确定。每个重链成为一个 BST，深度是它的性质；不同的 BST 之间通过轻边相连，认子不认父。

通过以下方法可以构造出一棵树高严格 $O(\log n)$ 的二叉搜索树：对每个重链建树，给它们赋予权值 $siz_{lightsubtree}+1$，求带权中位数为当前子树的根，再递归建树。

由于树高严格 $O(\log n)$，每次修改直接往上跳；重边 update，轻边重新计算贡献。