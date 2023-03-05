求序列 $\{a_i\}(1\le i\le n)$ 满足
- $1\le a_i\le m,a_i\in \mathbb Z$
- $p|(\sum a_i)$
- 至少有一个 $a_i$ 是质数。

先不管第三个条件。设 $c_i$ 为

$$
c_i=\sum_{k=1}^m [k\bmod p=i]
$$

则用一个类似于背包的东西，设 $f(i,j)$ 表示考虑完了前 $i$ 个数，$\sum_{k=1}^ia_k \equiv j\pmod p$ 的方案数。

枚举第 $i+1$ 个数选的是 $c_k$，则
$$
f(i+1,(j+k)\bmod p)\gets c_k\cdot sf(i, j)
$$
发现第二维只有 $O(p)$，而 $p\le 100$，于是可以矩阵乘法优化转移。时间复杂度 $O(p^3\log n)$。

接下来，我们发现第三个条件只需要容斥一下，即可计算。