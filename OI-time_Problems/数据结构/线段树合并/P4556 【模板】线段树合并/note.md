# 线段树合并

线段树合并，一般指两棵（亦可延伸为多棵）权值线段树**之间**进行横向地信息维护，比如将同一权值处的两个信息相加、取max之类的，最后得到了一棵新线段树。

为了节约空间，最好采用动态开点线段树。

## 关键代码

第一种方式是一种拆东墙补西墙的方法。

```cpp
int merge(int x, int y, int l, int r) {
		if(!x || !y) return x + y;
		if(l == r) {
			e[x].val += e[y].val;
			return x;
		}
		int m = (l + r) >> 1;
		e[x].ls = merge(e[x].ls, e[y].ls, l, m);
		e[x].rs = merge(e[x].rs, e[y].rs, m+1, r);
		pushup(x);
		return x;
}
```

在这里，把y树上的信息完全地加到x子树上。在这之后，**原来的**x树不复存在，而是被新的x树替代。另外，在合并后，y子树不可再修改！（类似于部分可持久化）

调用时写

```cpp
rt[u] = merge(rt[u], rt[v], 1, n)
```

第二种方法时类似于可持久化里的`path copying`，每次合并后新建节点。

```cpp
int merge(int x, int y, int l, int r) {
		if(!x || !y) return x + y;
   		int rt = ++tot;
		if(l == r) {
			e[rt].val = e[x].val + e[y].val;
			return rt;
		}
		int m = (l + r) >> 1;
		e[rt].ls = merge(e[x].ls, e[y].ls, l, m);
		e[rt].rs = merge(e[x].rs, e[y].rs, m+1, r);
		pushup(rt);
		return rt;
}
```

同样值得注意的是，尽管做了合并，x、y树仍然可以被询问和被合并，但是x、y树不再允许修改。（类似部分可持久化）

## 例题

[P4556 雨天的尾巴 /【模板】线段树合并 - 洛谷](https://www.luogu.com.cn/problem/P4556)

## Reference

[线段树合并：从入门到放弃 - Styx 的博客 - 洛谷博客 (luogu.com.cn)](https://www.luogu.com.cn/blog/styx-ferryman/xian-duan-shu-ge-bing-zong-ru-men-dao-fang-qi)

