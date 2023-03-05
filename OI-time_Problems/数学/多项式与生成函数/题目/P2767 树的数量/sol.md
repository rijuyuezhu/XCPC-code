# 做法1

设 $F(x)$ 是以节点个数为组合对象时树个数的 OGF，则有

$$
F(x)=xF^m(x)+1
$$

得到 $xF^m(x)-F(x)+1=0$。

如果你不认得这个东西，那你可以牛迭求 $F(x)$。

# 做法2

前置知识：拉格朗日反演公式。

若 $F,G$ 两个形式幂级数的常数项为 0 且有 $F(G(x))=G(F(x))=x$，则称它们互为复合逆。我们可以用公式：

$$
[x^n]G(x)=\dfrac{1}{n}[x^{n-1}]\left(\dfrac{x}{F(x)}\right)^n
$$

当然还有拓展拉格朗日公式：

$$
[x^n]H(G(x))=\dfrac{1}{n}[x^{n-1}]H'(x)\left(\dfrac{x}{F(x)}\right)^n
$$

---

回到该题

我们想办法把 $F(x)$ 的常数项置为 0。改变定义，假设 $F(x)$ 不包括空树，则有

$$
F(x)=x(1+F^m(x))
$$
得到

$$
x=\dfrac{F(x)}{(1+F(x))^m}
$$
发现我们已经完成了反解。于是很容易求得该函数的复合逆为

$$
G(x)=\dfrac{x}{(1+x)^m}
$$

所以

$$
\begin{aligned}
    [x^n]F(x)=
    &
    \dfrac{1}{n}[x^{n-1}]\left( \dfrac{x}{G(x)} \right)^n
    \\=&
    \dfrac{1}{n}[x^{n-1}](1+x)^{mn}
    \\=&
    \dfrac{1}{n}\binom{mn}{n-1}
\end{aligned}
$$