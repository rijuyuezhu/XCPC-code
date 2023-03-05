$$
a_n=233a_{n-1}+666a_{n-2},a_0=0,a_1=1
$$

该递推式的特征方程为

$$
\begin{aligned}
    &x^2-233x-666=0
    \\
    &x_1,x_2=\dfrac{233\pm\sqrt{56953}}{2}
    \\
    &\therefore a_n=\alpha x_1^n + \beta x_2^n
    \\
    &\because a_0=0,a_1=1
    \\
    &\therefore
    \begin{cases}
        \alpha + \beta = 0
        \\
        \alpha x_1+\beta x_2=1
    \end{cases}
    \\
    &\therefore
    \begin{cases}
        \alpha = \dfrac{1}{\sqrt {56953}}
        \\
        \beta = -\dfrac{1}{\sqrt {56953}}
    \end{cases}
    \\
    &a_n=\dfrac{1}{\sqrt{56953}}\left(\left(\dfrac{233+\sqrt{56953}}{2}\right)^n-\left(\dfrac{233-\sqrt{56953}}{2}\right)^n\right)
\end{aligned}   
$$

这个题需要用到单次询问 $O(1)$ “光速幂”：基于一种分块的思想。

若要多次求 $x^n\bmod P$ 的值，可以先预处理出

$$
f(i)=x^i,g(i)=x^{65536i}
$$

则 $x^n=g(\dfrac{n}{65536})\cdot f(n\bmod 65536)$

限定在于 $x,P$ 保持不变。