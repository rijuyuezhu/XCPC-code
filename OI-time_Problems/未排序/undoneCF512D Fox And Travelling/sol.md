在环上的点一定没有贡献，我们只需要考虑剩余部分。剩余部分分为两种：

1. 与环相连的树，那个与环相连的点一定要最后选，可以看成有根树；
2. 单独的一棵树，可以看作无根树。

对于每种树，需要求出在它中去掉 $k$ 个叶子的方案数。有根树直接树上背包即可，而对于无根树，则以每个点为根做一次背包，将答案加和后除以 $sz-k$ 即可。

最后再用一次背包合并答案即可，复杂度 $O(n^3)$。