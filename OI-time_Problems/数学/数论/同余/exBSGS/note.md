## BSGS

方程 $a^x\equiv b\pmod p$。其中 $\gcd(a, p)=1$。（$p$ 不一定是质数）

设 $x=iB+C(0\le B<C)$，则

$$
a^{iB}\equiv ba^{-C}
$$

这里取 $B=\sqrt p$，时间复杂度为 $O(\sqrt p)$。

## exBSGS

**以下用** $(a,b)$ **来表示** $a,b$ **的gcd**

仍然是 $a^x\equiv b \pmod p$，其中 $a,p$ 不一定互质。

- 当 $a,p$ 互质，直接 BSGS。
- 否则，设 $(a,p)=d$。
  - 若 $d\nmid b$，由于 $b=a^x+t\cdot p$ 而后者当 $x>0$ 一定是 $d$ 的倍数，故当 $b\ne 1$ 时无解。（注意特判）
  - 当 $d\mid b$ 时，可以化为 $a^{x-1}\frac{a}{d}\equiv \frac{b}{d}\pmod {\frac{p}{d}}$。由于 $\frac{a}{d}\perp \frac{p}{d}$，可以直接化为 $a^{x-1}\equiv \frac{b}{d}\cdot (\frac{a}{d})^{-1}\pmod {\frac{p}{d}}$。（注意特判 $a=0$）
    - 若 $a\perp\frac{p}{d}$，可以直接 BSGS。
    - 否则，我们递归进入子问题。

这部分不超过 $O(\log p)$，时复还是 $O(\sqrt p)$。