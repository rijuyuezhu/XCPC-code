容易发现，首先我们需要构造一个全 1 的行，用它来染色列这样才能满足矩阵变为全 1。

如何构造一个全 1 的行？假如我选择的是第 $i$ 行，若它还有 $k$ 个位置是 0，这些位置可以记为 $(i, \cdot)$，我们需要选择一个第 $i$ 列为 1 的行，做 $k$ 次染色。于是我们贪心地选择 $k$ 最小的、第 $i$ 列不为全 0 的行 $i$。另外，请注意细节（特别是存在行、列全 1 的情况）。