设 $a_1,a_2,\cdots,a_n$ 分别是选出的第 $1,2,\cdots,n$ 大。二分一个 $V$，验证是否可能 $a_k\le V$ 。则

$$
a_n\le a_{n-1}\le \cdots \le a_k\le V
$$

故转为询问以这种选数方法，能否选出 $\ge n-k+1$ 个 $\le V$ 的数。

把矩阵中 $\le V$ 的数认为 1， 其余数认为 0。这是一个经典的二分图匹配的问题，若采用 $O(m\sqrt n)$ 的 dinic 算法，最终复杂度为 $O(n^2\sqrt n\log V)$。