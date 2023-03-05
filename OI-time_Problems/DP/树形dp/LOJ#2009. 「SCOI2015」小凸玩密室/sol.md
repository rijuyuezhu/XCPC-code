<https://blog.csdn.net/corsica6/article/details/82711433>

是这样一个过程：

假设选了 $u$ 作为起点，其到根的路径为 $a_1,a_2,\cdots,a_k,(a_1=u,a_k=rt)$ 则点灯方式如下：

1. 点亮 $a_1$ 子树，再从子树走到 $a_2$。
2. 对于 $i\in[1,k)$，
   1. 若 $bro_{a_i}$ 存在：从 $a_{i+1}$ 出发，点亮 $bro_{a_i}$ 子树，再从子树走到 $a_{i+2}$。为了方便，让 $a_{k+1}$ 为根的父亲且权值为0，不影响答案。
   2. 若 $bro_{a_i}$ 不存在：从 $a_{i+1}$ 出发直接去 $a_{i+2}$。
   
   其中 $bro_i$ 表示 $i$ 的兄弟。

容易发现，上面大多数操作是简单的，仅需要考虑优化：

- 从 $u$ 出发遍历 $u$ 子树，之后再直接去 $fa_u/fa_{fa_u}$。

这是很困难的，但若我们能把这个操作求解完成，那么我们可以枚举起点，在 $O(n\log n)$ 的时间复杂度内解决本题（注意到树高为 $\log_2 n$）。

考虑 dp。

设 $f(i,j)$ 表示遍历 $i$ 的子树，在这之后直接去 $i$ 的 $k$ 级祖先 $fa(i,k)$ 的最小花费；设 $g(i,j)$ 表示遍历 $i$ 的子树，在这之后直接去 $i$ 的 $k-1$ 级祖先的兄弟 $bro_{fa(i,k-1)}$（另记作 $br(i,k)$） 的最小花费。以上状态均假设 $i$ 已亮灯，不包括 $i$ 的花费。

于是可以转移：

- 若 $i$ 是叶子，则有
$$
\begin{aligned}
    f(i,j)&=dist(i,fa(i,j))\times A_{fa(i,j)}
    \\
    g(i,j)&=dist(i,br(i,j))\times A_{br(i,j)}
\end{aligned}
$$

- 若 $i$ 仅有左儿子，则有
$$
\begin{aligned}
    f(i,j)&=dist(i,ls_i)\times A_{ls_i}+f(ls_i, j+1)
    \\
    g(i,j)&=dist(i,ls_i)\times A_{ls_i}+g(ls_i, j+1)
\end{aligned}
$$

- 若 $i$ 既有左儿子，又有右儿子，则分类讨论：

$$
\begin{aligned}
    f(i,j)&=\min
    \begin{cases}
        g(ls_i,1) + dist(i, ls_i)\times a_{ls_i} + f(rs_i, j+1)
        \\
        g(rs_i,1) + dist(i, rs_i)\times a_{rs_i} + f(ls_i, j+1)
    \end{cases}
    \\
    g(i,j)&=\min
    \begin{cases}
        g(ls_i,1) + dist(i, ls_i)\times a_{ls_i} + g(rs_i, j+1)
        \\
        g(rs_i,1) + dist(i, rs_i)\times a_{rs_i} + g(ls_i, j+1)
    \end{cases}
\end{aligned}
$$

总时间复杂度 $O(n\log n)$。