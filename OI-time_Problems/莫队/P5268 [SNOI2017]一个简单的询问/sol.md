<https://www.luogu.com.cn/problem/P5268>

$$
\sum_{x=0}^{\infin}\mathrm{get}(l_1,r_1,x)\times \mathrm{get}(l_2,r_2,x)
$$

发现 $\mathrm{get}(l,r,x)$ 具有可减性，即得到 

$$
\mathrm{get}(l,r,x)=\mathrm{get}(1,r,x)-\mathrm{get}(1,l-1,x)
$$

定义 $q(l,r)=\sum_{x=0}^{\infin}\mathrm{get}(1,l,x)\times\mathrm{get}(1,r,x)$

则

$$
ans(l_1,r_1,l_2,r_2) = q(r1,r_2)-q(l_1-1,r_2)-q(r1,l_1-1)+q(l_1-1,l_2-1)
$$

显然可以莫队求得所有的 $q$。时间复杂度为 $O(n\sqrt m)$。
