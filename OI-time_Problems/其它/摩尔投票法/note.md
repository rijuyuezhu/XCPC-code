# 摩尔投票法 学习笔记

参考资料：<https://www.zhihu.com/question/49973163>

## 求序列的绝对众数

绝对众数：在序列出现次数 $> \left\lfloor\dfrac n 2\right\rfloor$ 的数。

采用两两抵消的思想。因为其它所有数出现加起来都不如绝对众数多，所以两两抵消后，只有最后剩下的可能是区间众数。时间复杂度 $O(n)$，空间复杂度 $O(1)$。

## 拓展

<https://vjudge.net/problem/CodeForces-674G>

序列 $[1,n]$，两种操作：

1. 区间染色
2. 求区间出现次数大于等于 $\left\lceil \dfrac {p(r-l+1)} {100} \right\rceil$ 的数的个数。（稍有变化）
    
    数据保证 $\left\lfloor \dfrac {100}p \right\rfloor \le 5$。

参考摩尔投票法的思想，记录 $\left\lfloor \dfrac {100}p \right\rfloor$ 个互不相同的数，每次加入一个数后，若在记录的数中已存在，则该数次数加一；否则，将这个数连同每个数（一共 $\left\lfloor \dfrac {100}p \right\rfloor+1$）个数一起抵消。那么，合法的数一定会到这个序列中来。

这样想象一下：每个不同的数为一座塔，塔的高度为它的出现次数。每次可以削若干座塔的底部，则超过这个限度的塔一定削不完（反证一下，要是它削完了就没数剩下了）。