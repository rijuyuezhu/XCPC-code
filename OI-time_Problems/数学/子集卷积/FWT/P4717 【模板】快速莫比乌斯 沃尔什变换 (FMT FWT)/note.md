# OR

得到 OR 卷积，求 $C=A*B$，其中 $C_n=\sum_{i|j=n}A_iB_j$。

其中 $|$ 是按位或。

构造 $FWT(F)_n=\sum_{n\subset k}F_k$，其中 $\subset$ 表示二进制下的包含。那么 

$$
FWT(A)_nFWT(B)_n=\sum_{n\subset i}\sum_{n\subset j}A_iB_j=\sum_{i,j}\sum_{n\subset i|j}A_iB_j=FWT(C)_n
$$

想办法由 $F$ 推得 $FWT(F)$，其中 $FWT(F)_n=\sum_{n\subset k}F_k$。

我们考虑分治。这个分治可以视作：从低到高考虑每一位。我们将第 $i$ 位为 0 和第 $i$ 位为 1的分别记作 $F_0$ 和 $F_1$。然后我们要根据它们求得合并后、即计算到第 $i+1$ 位处的值。

- 对于 $F_0$，第 $i$ 位为 0，不能多出新的子集，没有贡献，故转到 $F$ 后还是 $F_0$
- 对于 $F_1$，到第 $i$ 位后多出了新的子集：$F_0$，故贡献变为了 $F_0+F_1$。

于是我们得到 $FWT(F)=merge(FWT(F_0),FWT(F_0)+FWT(F_1))$

类似 FFT 那样写即可。

而逆过程也好办，要从 $FWT(F)$ 推到 $FWT(F_0),FWT(F_1)$，容易知道

$$
\begin{gathered}
    FWT(F_0)=FWT(F)_{pre}
    \\
    FWT(F_0)=FWT(F)_{suf}-FWT(F)_{pre}
\end{gathered}
$$

即
$$
    IFWT(F')=merge(IFWT(F'_0),IFWT(F'_1)-IFWT(F'_0))
$$

# AND

同理，FWT定义为超集和。得到递推式：

$$
FWT(F)=merge(FWT(F_0)+FWT(F_1),FWT(F_1))
$$
$$
IFWT(F')=merge(IFWT(F'_0)-IFWT(F'_1),IFWT(F'_1))
$$

# XOR

这个非常重要。

令 $popcount(x\&y)$ 表示 $x\& y$ 中 1 的数量的奇偶性。那么容易发现：

$$
popcount(n\&i)\oplus popcount(n\&j)=popcount(n\& (i\oplus j))
$$  

定义 $i\otimes j=popcount(i\& j)$

$$
FWT(F)_n=\sum_{i\otimes n = 0}a_i-\sum_{i\otimes n = 1}a_i
$$

推得

$$
FWT(F)=merge(FWT(F_0)+FWT(F_1),FWT(F_0)-FWT(F_1))
$$

$$
IFWT(F')=merge\left(\dfrac{1}{2}(IFWT(F'_0)+IFWT(F'_1)),\dfrac{1}{2}(IFWT(F'_0)-IFWT(F'_1))\right)
$$