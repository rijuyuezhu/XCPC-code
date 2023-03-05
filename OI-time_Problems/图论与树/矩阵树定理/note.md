<https://www.luogu.com.cn/blog/command-block/ju-zhen-shu-ding-li-xing-lie-shi-post>

# 矩阵树定理

图中**无自环**。

## 经典

给一个无向无权图， $A$ 为邻接矩阵（$A_{i,j}=[e(i,j)]$），$D$ 为其度数矩阵（$D_{i,i}=\deg(i),D_{i,j}=0(i\ne j)$）。

基尔霍夫矩阵 $K=D-A$）

令 $K'$ 是 $K$ 的一个 $n-1$ 阶主子式，即 $K$ 去掉第 $k$ 行、第 $k$ 列（$k$ 任意）得到的一个行列式。

那么该图的生成树数量则为 $\det(K')$。

## 带权

先延续上文，如果图有重边，只要把邻接矩阵和度数矩阵作修改，仍然可以用矩阵树定理求出。而如果把重边看作是图的边权，则修改邻接矩阵和度数矩阵后（$D_{i,i}$ 变为 $\sum_je(i,j)$），所求出的即为所有生成树的边权之积的总和。

## 有向图

这里 $A$ 的定义为有向图中的邻接矩阵。

若 $D$ 定义为入度矩阵，则求的是外向树；

若 $D$ 定义为出度矩阵，则求的是内向树。

（反着来）

同样可以加权。

由于是有向图，需要指定根，则 $K$ 删去第 $k$ 行第 $k$ 列就是以 $k$ 为根。

<https://www.luogu.com.cn/problem/P6178>

<https://www.luogu.com.cn/problem/P4336>

<https://www.luogu.com.cn/problem/P3317>

<https://www.luogu.com.cn/problem/P4455>

