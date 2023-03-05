<https://autumnkite.github.io/loj6059-sol/>

首先，容易写出一个 dp ：$f(i,j,k)$ 表示考虑数的前 $i$ 位，前 $i$ 位组成的数模 $p$ 余 $j$，前 $i$ 位的数的和为 $k$ 的方案数，转移为

枚举 $t\in[0,9]$，
$$
f(i+1,(10j+t)\bmod p,k+t)\gets f(i,j,k) 
$$

时间复杂度 $O(npm)$。

显然可以矩乘优化（？）到 $O(p^3m^3\log n)$。可以通过 $30 \%$ 的数据。

~~然后我就不会做了。~~

正解是倍增 NTT。倍增 NTT 需要得到 $f(i)\to f(i+1)$  的转移和 $f(i)\to f(2i)$ 的转移。上面已经写了前者。

而

$$
f(2i,(10^i j+k)\bmod p,x+y)\gets f(i, j, x)f(i,k,y)
$$

可以直接枚举 $j,k$ 进行卷积转移。时间复杂度 $O(p^2m\log m\log n)$