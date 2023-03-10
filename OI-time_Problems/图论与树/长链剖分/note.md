<https://www.luogu.com.cn/blog/Ynoi/zhang-lian-pou-fen-xue-xi-bi-ji>


## 长链剖分基本概念

长链剖分：根据“高度”选择“长儿子”，形成若干条不相交长链。

高度 $h_u$，就是节点 $u$ 到其子树内深度最大的节点的距离。一个节点高度最大的儿子是其长儿子。

有以下几个性质：

- 一个点到根的路径上有最多 $O(\sqrt n)$ 个长链，亦最多有 $O(\sqrt n)$ 条虚边。

    假如从 $u$ 向上跳到了链顶 $v$，而链顶的父亲 $w$ 与 $u,v$ 不在同一长链中，则 $w$ 必存在另一个子树，且其中节点数量 $\ge h_v$（不然长链不可能向那边延伸）。而每次跳父亲，$h_i$必增。故跳 $t$ 次，所在节点的子树大小是 $O(1+2+\cdots+t)=O(t^2)$。故至多跳 $O(\sqrt n)$ 次。

## 长链剖分应用

### 树上 $k$ 级祖先

使用长链剖分，我们可以得到一种 $O(n\log n)\sim O(1)$ 的树上 $k$ 级祖先算法。

首先一个结论：

- 一个点 $u$ 的 $k$ 级祖先所在长链长度 $\ge k$。

    证明显然。

对于每条长度为 $len$ 的长链，我们预处理出长链顶之上 $len$ 个节点和长链中的 $len$ 个节点，把它们放在同一个数组中。这样，我们可以轻松查表求出该长链中的任意节点的 $k(k\le len)$ 级祖先。

同时我们搞一个倍增数组。

对于一个询问 $u$ 的 $k$ 级祖先，我们先用倍增数组跳到 $u$ 的 $2^{\lfloor\log_2 k\rfloor}$ 级祖先（设为 $t$），那么 $t$ 所在长链长度 $\ge 2^{\lfloor\log_2 k\rfloor}$。我们还需要跳 $k-2^{\lfloor\log_2\rfloor}<2^{\lfloor\log_2\rfloor}$ 级，根据上段所述，可以直接查表求出。