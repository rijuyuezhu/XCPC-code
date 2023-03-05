设 $P(x, y)$，根据题意

$$
\forall i \in [1,n-1],S_{\triangle PA_0A_1}\le S_{\triangle PA_iA_{(i+1)\bmod n}}
$$

记 $A_i=(x_i,y_i)$，则对于 $i\in[1,n-1]$ 有一个方程（为了方便，以下下标默认向 $n$ 取模）。

$$
\begin{gathered}
    \overrightarrow{PA_0}\times \overrightarrow{PA_1}\le \overrightarrow{PA_i}\times \overrightarrow{PA_{i+1}}
    \\
    (x_0-x)(y_1-y)-(x_1-x)(y_0-y)\le (x_i-x)(y_{i+1}-y)-(x_{i+1}-x)(y_i-y)
    \\
    (y_0-y_1+y_{i+1}-y_i)x + (x_1-x_0+x_i-x_{i+1})y+x_0y_1-x_1y_0-x_iy_{i+1}+x_{i+1}y_i\le 0
\end{gathered}
$$

这是一个半平面，求出半平面交即可。