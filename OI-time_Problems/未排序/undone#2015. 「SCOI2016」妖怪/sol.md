关注一个两值分别为 $u_i,v_i$ 的妖怪，它在环境 $(a, b)$ 下的战斗力为

$$
u_i+v_i+\dfrac{a}{b}u_i+\dfrac{b}{a}v_i
$$

令 $t=\dfrac{a}{b}$，则不难发现上式是一个变形了的“对勾”函数（仅有左半部分）。题目所求即为 $n$ 个对勾函数的 $\max$ 的最小值。而由于对勾函数是一个下凸函数，其 $\max$ 也是个下凸函数，故可以三分求最小值。