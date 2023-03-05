# 线性基 学习笔记

## 学习资料

[线性基详解_a_forever_dream的博客-CSDN博客](https://blog.csdn.net/a_forever_dream/article/details/83654397)

[线性基 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/math/basis/)

## 线性基

线性基（简称基）是线性空间（可以看作 $n$ 维向量组成的集合）的一组基底。

何为基底？假如我们的线性空间 $\Omega=\{\mathbf a_1,\mathbf a_2,\cdots,\mathbf a_m\}$，我们有一个基为 $\{\mathbf b_1,\mathbf b_2,\cdots,\mathbf b_k\}$

1.  所有线性空间中的 $\mathbf a_i$ 都可以由多个 $\mathbf b_k$ 线性组合（加、减、数乘），且方案唯一。
2.  任意两个 $\mathbf b_i,\mathbf b_j$ 的线性组合不为 $\mathbf 0$。
3.  基是满足上述条件最小的，基里的元素个数是固定的，叫做该线性空间的 **维数**。

我们可以考虑高斯消元得到一个基，我们向基中一个一个插入元素，然后化成类似于 **上三角矩阵** 的东西即可。（这里的上三角矩阵不一定是一个三角，可能是一个阶梯）

这里有一道例题:[P3265 [JLOI2015]装备购买](https://www.luogu.com.cn/problem/P3265)

然而，在OI中，用得最多的是 **异或空间** 中的线性基。

## 异或空间中的线性基

如果我们把一个最多 $w$ 位的整数看成一个 $w$ 维的01向量，比如：

$(101011001)_{(2)}$ 看作 $\mathbf a=(1,0,1,0,1,1,0,0,1)$

那么我们使用异或操作进行 **高斯消元** 得到上三角，就成为了异或空间中的线性基。接下来若无特殊说明， 基/线性基均指异或空间中的线性基。

在这个意义下，我们定义了每一维的偏序。所以我们可以有一些问题（求异或最大值、最小值、$k$ 小值）。

[线性基练习题](https://www.luogu.com.cn/training/11251)

### 线性基的建立

```cpp
const int B = 51;
ll t[B];
void ins(ll x) {
	for(int i = B-1; i >= 0; i--)
		if((x >> i) & 1) {
			if(!t[i]) {
				t[i] = x;
				break;
			} else x ^= t[i];
		}
}
```

### 最大值

只要从高到低按位贪心即可。

```cpp
ll qry() {
	ll ans = 0;
	for(int i = B-1; i >= 0; i--) 
		ans = max(ans, ans ^ t[i]);
	return ans;
}

```



### 最小值

分两种情况：

1.  如果有元素不能插入线性基，那么肯定可以异或出0来。
2.  否则就是最小的 插入基中的元素。

