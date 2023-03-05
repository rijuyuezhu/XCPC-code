<https://www.luogu.com.cn/blog/221955/san-yuan-huan-si-yuan-huan-ji-shuo>

<https://www.luogu.com.cn/blog/command-block/san-yuan-huan-xiao-ji-si-yuan-huan-post>

<https://www.cnblogs.com/Dance-Of-Faith/p/9759794.html>

三元环计数：

先给边定向。设 $d_u$ 是 $u$ 的度数。对于一条边 $e(u, v)$，将度数小的向度数大的连边（如果度数相同则比较编号），于是无向图中的三元环可以一一对应得到的有向图中的三元环。

算法如下：先枚举第一个顶点 $u$，对所有它到达的点打上标记 $u$。然后枚举 $v,e(u,v)\in E$；再枚举 $k,e(v,k)\in E$，若 $k$ 的标记为 $u$，则 $(u,v,k)$ 是一个三元环。时间复杂度为 $O(m\sqrt m)$。通过此算法也可以说明无向图的三元环个数上界是 $m\sqrt m$。

复杂度证明：

枚举 $v,e(u,v)\in E$ 的复杂度是 $O(m)$。

而剩下的复杂度在枚举 $v$ 的部分，大概是 $O(\sum_{e(u,v)}out_v)$，其中 $out_v$ 表示 $v$ 的出度。

如果 $v$ 的出度为 $out_v$，则原无向图中 $v$ 的度数 $\ge out_v$。根据我们的连边原则，$v$ 在新图连向的 $out_v$ 个点在原图中的度数都 $\ge out_v$。而无向图中节点总度数 $\le 2m$，于是有 $out_v^2\le \sum_{(v,k)\in E}\deg k\le 2m$。于是 $out_v$ 最大也就是 $O(\sqrt m)$ 级别。复杂度得证。

<https://www.luogu.com.cn/problem/P1989>
