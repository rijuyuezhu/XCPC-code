# 后缀自动机（SAM） 学习笔记

很久以前学过SAM，现在又忘了。

## 学习资料

[后缀自动机感性理解](https://www.cnblogs.com/Hs-black/p/12004609.html)

[史上最通俗的后缀自动机详解](https://www.luogu.com.cn/blog/Kesdiael3/hou-zhui-zi-dong-ji-yang-xie)

[后缀自动机 (SAM)](https://oi-wiki.org/string/sam/)

## SAM

如果我们把一个长度为 $n$ 的串 $S$ 的所有后缀放入同一个 trie 中，并标记结束位置`end`，可以得到一个时间、空间均为 $\mathcal O(n^2)$ 的（假）后缀树。

它具有以下几个性质：

1.  从根到任意 `end` 是一个后缀，从根到任意节点是一个子串。
2.  本质不同的子串个数就是状态（节点）个数。

但是它的时空太大，不满足我们的需求，所以我们采用它的强压缩版本——SAM。

字符串 的 SAM 是一个接受 字符串的所有后缀的最小 **DFA** （确定性有限自动机或确定性有限状态自动机）。它是一个DAG。

## SAM的构造

### 结束位置 endpos

对于一个 $S$ 的子串 $t$，我们用 $\mathrm{endpos}(t)$ 表示 $t$ 在 $S$ 中的所有 结束位置。

如果 两个子串 $t_1,t_2$ 满足 $\mathrm{endpos}(t_1)=\mathrm{endpos}(t_2)$，则称它们为 **等价类**。

除初始状态外，**每一个等价类对应SAM上的一个状态（节点）**。当然可以把初始状态看成空串。

endpos 有以下性质：

1.  如果 $t_1,t_2(|t_1|\le|t_2|)$ 的 endpos 相同，那么 $t_1$ 是 $t_2$ 的后缀，且不可能以其它形式出现。
2.  对于任意两个子串 $t_1,t_2(|t_1|\le |t2|)$：
    1.  若 $t_1$ 是 $t_2$ 的后缀，则 $\mathrm{endpos}(t_2)\subseteq\mathrm{endpos}(t_1)$
    2.  否则 $\mathrm{endpos}(t_1)\cap \mathrm{endpos}(t_2)=\emptyset$
3.  在一个等价类中存的是一系列 **长度连续** 的串，并且它们 **互为后缀**。形式化地，假设这个等价类中的最长串为 $S[x\dots y]$，则其所有串为 $S[i\dots y](x\le i\le z)$。最长串长度为 $\mathrm{maxlen}=y-x+1$，最短串长度为 $\mathrm{minlen}=y-z+1$。

### 后缀 link

设 $u$ 为一个非初始状态的状态。根据性质3，它对应一个等价类，这个等价类中的串都形如$S[i\dots y](x\le i\le z)$。这相当于将长串 $S[x\dots y]$ 一个个“削去”首字母得到的串。而这些串有什么特性呢？根据性质1，它们之间互相 **只以** 后缀形式存在。

但是，在削到最短串 $S[z\dots y]$ 后，如果我继续削，得到的串的 $\mathrm{endpos}$ 就不同了（因为不属于一个等价类了）。根据性质2，它的 $\mathrm{endpos}$ 应该“扩增了”。这个新得到的串 对应的 $\mathrm{endpos}$ 对应的状态 $v$ 叫作 $u$ 的“父亲状态” *（其实就是parent tree 上的父亲）*。我们把 后缀$\mathrm{link}(u)$ 定义为 $v$，即 $u$ 的“父亲”。

于是我们发现，所有的后缀链接会构成一棵树。这个树叫 parent tree。

>   parent tree除了按后缀链接（自底向上）构造外，还可以理解为 endpos（自上而下）的分裂。

### 具体实现

**以下不再区分 节点、状态  和  等价类，因为它们是一一对应的。**

```cpp
struct Node {
	int ch[26], fa, len;
}t[MAXN << 1];
int lst = 1, tot = 1;
void add_sam(int c) {
	int p = lst, np = lst = ++tot;
	t[np].len = t[p].len + 1;
	for(; p && !t[p].ch[c]; p = t[p].fa) t[p].ch[c] = np;
	if(!p) t[np].fa = 1;
	else {
		int q = t[p].ch[c];
		if(t[q].len == t[p].len + 1) t[np].fa = q;
		else {
			int nq = ++tot; t[nq] = t[q];
			t[nq].len = t[p].len + 1;
			t[q].fa = t[np].fa = nq;
			for(; p && t[p].ch[c] == q; p = t[p].fa) t[p].ch[c] = nq;
		}
	}
}
```

随意说两点吧，可能对理解有所帮助。

一、**跳后缀link的意义**：跳后缀link即为“压缩地”遍历当前串的全部后缀。如果从节点 p 开始跳，不妨设 p 对应的 等价类中最长串为 $S[x\dots y]$，那么跳后缀link即为 跳所有 $S[i\dots y](x\le i\le y)$ 对应的节点。

二、为什么要遍历 旧串（即加入 $c$ 之前的串）的所有后缀：加入 $c$ 后我们考虑其对所有节点的endpos的影响。会影响的只会是旧串的后缀，它们都可以+c成为新串的一个后缀。

三、`for(; p && !t[p].ch[c]; p = t[p].fa) t[p].ch[c] = np;` 这句话的意义：在跳后缀link遍历 （（旧串）的所有后缀）时，如果没有转移边，说明这个等价类中的后缀连上一个c都不曾出现在旧串中出现过。那么现在多接了一个c，可以到达一个新的状态 np（因为这些串肯定是旧串的后缀，加一个c就是新串的后缀）。

四、`if(t[q].len == t[p].len + 1) t[np].fa = q;` 这句话的意义：说明 q 中的最长串是（p中的最长串+c），所以 q中的所有串都是新串的后缀，**它们的endpos没有发生变化**，都加入了一个 $n$。所以 q 仍然保持是一个节点。np 的后缀 link 也是 q，这是因为 q 是“（最长的）（不属于np等价类的）（新串的）后缀”。

五、这一段代码：**非常重要**

```cpp
	int nq = ++tot; t[nq] = t[q];
    t[nq].len = t[p].len + 1;
	t[q].fa = t[np].fa = nq;
	for(; p && t[p].ch[c] == q; p = t[p].fa) t[p].ch[c] = nq;
```

由于不满足`t[q].len == t[p].len + 1`，说明 q 中分为两类串 $t_1$ 和 $t_2$：

-   $t_1$ 满足 $|t_1|=\mathrm{maxlen}(p)+1$，同  四、 所述，它是新串的后缀，也应同 四、中一般处理。我们把它分裂出去形成一个新的等价类 nq。
-   $t_2$ 满足 $|t_2|>\mathrm{maxlen}(p)+1$，它 **不是** 新串的后缀。那么它们的 endpos 就不能加 $n$ 。

然后调整后缀link和转移即可。



## SAM 的其它性质

1.  sam的状态数不超过$2n$，转移数小于 $3n$。

2.  如何计算endpos？对于那些是 `end`位置（这里表示原串的后缀的终点），endpos可以直接计算。还记得我们所说的 parent tree 其实是将 endpos集合分裂吗？只要建parent tree，再dfs一遍进行合并即可。

## SAM 的应用

<https://www.cnblogs.com/zjp-shadow/p/9218214.html>

<https://www.luogu.com.cn/blog/command-block/hou-zhui-zi-dong-ji-xue-xi-bi-ji-ying-yong-pian-post>

## 广义SAM

<https://www.luogu.com.cn/blog/ChenXingLing/solution-p6139>