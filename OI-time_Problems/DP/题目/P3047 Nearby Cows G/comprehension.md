这题主要是两种做法，一种是换根，一种是容斥。

关于容斥做法的理解：**由于是计算和，可以容斥**。遇到这种**既需要子树统计也需要父亲做贡献**的，可以两次dfs搞一搞。

关于换根做法：关键是找到方法，转移贡献，正确计算出每个点作为根的正确的dp值
