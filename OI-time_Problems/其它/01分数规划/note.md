<https://www.luogu.com.cn/blog/yestoday/post-01-fen-shuo-gui-hua-yang-xie>

0/1 分数规划主要用来求一个最优比率。

一般形式是，给你 $(a_i, b_i)$ 共 $2n$ 个数，如果你选了 $a_i$ 就一定要选 $b_i$。把全部你选了的挑出来，重新记为 $(a'_i,b'_i),(1\le i\le k)$ 要求最大化/最小化

$$
\dfrac{\sum_{i=1}^k a'_i}{\sum_{i=1}^k b'_i}
$$

那么为啥叫它 0/1 分数规划呢？它可以用另一种方式描述这个问题：

对于 $i\in[1,n]$，钦定 $x_i$ 为0/1，要求最大化/最小化

$$
\dfrac{\sum_{i=1}^na_ix_i}{\sum_{i=1}^nb_ix_i}
$$

如何求解 0/1 规划问题呢？常用方法是二分法。

比如我们要求最小值，只要二分一个答案 $t$, 判断是否

$$
\dfrac{\sum_{i=1}^k a'_i}{\sum_{i=1}^k b'_i}\le t
$$

即

$$
\sum_{i=1}^k a'_i - t\cdot \sum_{i=1}^k b'_i \le 0
$$

再稍加变形，得到

$$
\sum_{i=1}^k \left(a'_i-tb'_i\right)\le 0
$$

那么到此为止，一般题目中还有其它的一些限制。

例题：

<http://poj.org/problem?id=2976>

裸题，二分后排序，贪心地选 $n-k$ 个最大，看看加起来是否大于0.

<https://www.luogu.com.cn/problem/P4377>

0/1分数规划+背包。

<http://poj.org/problem?id=2728>

0/1分数规划+MST

<https://www.luogu.com.cn/problem/P3199>

0/1分数规划+负环