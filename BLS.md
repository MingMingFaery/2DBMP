# Breakout local search for the cyclic cutwidth minimization problem
突破性局部搜索解决循环切宽最小化问题
- 2022-7-28
- Journal of Heuristics
- JCR Q2, 2.247
## 引言
### GLP
the Graph layout problems (GLPs) 图布局问题
GLPs由寻找输入图的布局来优化某个目标函数组成。GLP具有两个映射函数。第一个函数将输入图中的每个顶点映射到宿主图中的一个顶点，第二个函数将输入图中的每条边映射到宿主图中的一条边。这些宿主图可以是线、树、网格和圈。除了不同类型的宿主图外，不同的GLP可能考虑不同的目标函数值。
### CCMP
the Cyclic Cutwidth Minimization Problem (CCMP) 循环切宽最小化问题
CCMP 与切宽最小化(CMP)问题类似，不过CCMP的宿主图是圆周。
CCMP 一个重要应用来自于环形电路布局，其中加工元件放置在一个环上，导线绕环布线。图1所示为环形电路板布局，其中所有电子元件的连接都是预定的，不同的布局导致不同的割宽分布。通过发现循环割宽，可以有效地安排电路，使导线均匀分布在整个电路中，缓解拥塞。
![CCMP](vx_images/216125515248577.png =200x)
### 本文贡献
我们提出的突破性局部搜索（BLS）在每次迭代中使用局部搜索来发现局部最优，然后在搜索空间中使用自适应多类型的(有向、基于频率和随机)扰动机制从当前局部最优移动到另一个局部最优。
局部搜索过程联合使用两个邻域，由Insert和Swap两个基本移动算子定义。在CCMP ( Jain等2016 ; Caveroetal . 2021)的其他方法中，Insert算子已被用于局部改进，而Swap算子是本文首次引入的。基于当前搜索状态的相关信息，BLS的扰动机制动态调整扰动类型和强度，不断从一个局部最优移动到另一个局部最优。此外，所提出的BLS利用禁忌搜索( Glover和Laguna 1998)中的禁忌列表思想对其进行有向扰动。
对来自文献的179个基准实例的计算评估表明，我们提出的BLS算法与当前性能最好的启发式算法竞争。特别地，BLS在139个案例上成功地改进了31个当前最知名的结果并匹配了当前最知名的结果。此外，在大多数情况下，我们提出的算法需要比当前最好的启发式算法更少的时间来获得最终解。
## CCMP问题描述
the Cyclic Cutwidth Minimization Problem 循环切宽最小化问题
对于无向图  $G = \left( {{V_C},{E_C}} \right)$ 和宿主图 $H = \left( {{V_H},{E_H}} \right)$ ,有以下性质：
- $\left\| {{V_C}} \right\| = \left\| {{V_H}} \right\| = \left\| {{E_H}} \right\|$；
- 宿主图H中每个顶点的度为2；
- H 是Eulerian and Hamiltonian图；
- （宿主图）所有相邻的点之间的距离相等。

内射函数将候选图中的所有边映射到宿主图中的路径。路径是连接两个顶点且不重复任何边或点的边的序列。令PH表示主图中所有路径的集合，因此对于EC中的每条候选边( u , v)，都存在两条潜在路径，其起点为φ ( u )或φ ( v )。我们选择较短的路径作为其路径。如果两条路径长度相同，则选择顺时针路径。
对于问题的目标函数值，将所有候选边映射到主机路径后，发送一条从圆心到主机边的散点连线，该连线所遍历的路径数即为主机边的割，割数学定义如下：
$$cut\left( {\varepsilon ,\phi ,\psi } \right) = \left\| {\left\{ {e \in {E_C}:\varepsilon  \in \psi \left( e \right)} \right\}} \right\|$$
问题的目标函数为最小化最大切：
$$F\left( \phi  \right) = \mathop {\max }\limits_{\varepsilon  \in {E_H}} \left\{ {cut\left( {\varepsilon ,\phi ,\psi } \right)} \right\}$$
> 下图为示例：
![示例1](vx_images/509041116256610.png =250x) ![示例2](vx_images/177261216249279.png =248x) ![示例2](vx_images/110123716245834.png =130x)
> 将无向图a，映射到宿主图b中，形成c
> - 映射关系：$\varphi \left( A \right) = 2,\varphi \left( B \right) = 4,\varphi \left( C \right) = 6,\varphi \left( D \right) = 5,$ $\varphi \left( E \right) = 1,\varphi \left( F \right) = 7,\varphi \left( G \right) = 3,\varphi \left( H \right) = 8$
> - 连接路径：在图d中，对于顶点EG之间的路径长度，顺时针(path1=2)，逆时针(path2=6)，选择短边作为路径长度（若相等选择顺时针路径）
> - 目标函数值：从宿主图的圆心向各边引线，目标值为切割边数量的最大值，对于示例图，$F\left( \phi  \right) = \max \left\{ {2,3,2,3,2,5,4,1} \right\} = 5$
## BLS
Breakout local search
突破性局部搜索
### 算法概况
BLS的一般思想是利用局部搜索寻找高质量的解来实现强化，然后采用自适应和多元化策略的扰动机制来跳出局部最优。
- Str 扰动强度
- Str0 初始扰动强度
- $\omega$ 截止改进的迭代次数
- K 扰动前最大截止改进次数
- T 程序终止条件：最大截止改进次数
![算法1](vx_images/567544119230151.png =495x)
### 解的表示和初始化
> 初始化：
A 表示所有已分配的顶点集合，U 表示所有未分配的顶点集合，${d_A}\left( v \right)$ 表示与顶点v相邻的已分配顶点集合，${d_U}\left( v \right)$ 表示与顶点v相邻的未分配顶点集合：
${d_A}\left( v \right) = \left\| {\left\{ {u \in A,\left( {u,v} \right) \in {E_C}} \right\}} \right\|$
${d_U}\left( v \right) = \left\| {\left\{ {u \in U,\left( {u,v} \right) \in {E_C}} \right\}} \right\|$
则，对于未分配顶点v 的评价值为：
$g\left( v \right) = {d_A}\left( v \right) - {d_U}\left( v \right)$
> 每次迭代，选择评价值g最高的点进行分配（选择的顶点更接近排列好的顶点），分配给其宿主图中顺时针的下一个位置。

算法2：
![算法2](vx_images/345700520248577.png =394x)

### 移动算子与邻域结构
两种不同的移动算子：
- Swap operator
$${N_1} = \left\{ {swap\left( {v,u} \right):v \in {V_C},u \in {V_H},u \ne \phi \left( v \right)} \right\}$$
邻域大小：$C_n^2 = {{n \times \left( {n - 1} \right)} \over 2}$
- Insert operator
$${N_2} = \left\{ {insert\left( {v,u} \right):v \in {V_C},u \in {V_H},u \ne \phi \left( v \right),u \ne \phi \left( v \right) - 1} \right\}$$
邻域大小：$n \times \left( {n - 2} \right)$
Insert：从当前解中选择一个顶点并插入到其当前位置以外的新位置，将所有受影响的顶点逆时针移动。
快速评估：主要思想是只考虑由移动算子重新分配的顶点，而不重新计算不受影响的顶点。一般来说，该方法首先删除移动后位置发生变化(宿主顶点)的所有受影响顶点相邻的路径。同时，这些路径对目标函数计算的贡献也被删除。然后，在宿主图中添加新的路径，并将这些新路径的贡献添加到目标函数中。
### 评价函数
为了引导局部搜索向更好的方向发展，在使用目标函数的基础上使用平局评价函数来更好的区分解的质量。
具体来说，通过比较了两个解中最大割出现的频率，最大割出现频率较小的解被认为是更优的解。如果最大割的频率相同，那么我们继续比较第二大割的频率。如果它们仍然相同，则重复比较，直到一个割的频率在两个解中不同。数学定义为：
$$\theta \left( {i,\phi } \right) = \left\| {\left\{ {e \in {E_H}:cut\left( {e,\phi ,\psi } \right) = i} \right\}} \right\|$$
> 对于两个目标值相同的解 $\phi ,{\phi'}$ 对于任意 $j\left( {1 \le j \le {i_{\max }}} \right)$ 满足下列条件之一，则说明${\phi'}$优于$\phi$  
> - $\theta \left( {{i_{\max }},\phi } \right) > \theta \left( {{i_{\max }},{\phi'}} \right)$
> - $\matrix{{\theta \left( {j,\phi } \right) > \theta \left( {j,{\phi'}} \right)} & {and} & \theta   \cr } \matrix{{\left( {i,\phi } \right) = \theta \left( {i,{\phi'}} \right)} & {\left( {j \le i \le {i_{\max }}} \right)}  \cr  }$
### 局部搜索
使用the first improvement 策略
进行变邻域搜索（Swap 和 Insert）
由于Insert 算子的邻域评估更复杂，因此采用邻域缩减策略
> 邻域缩减：ROI（regions of interest）
> 计算顶点v的每个邻点的ROI
> 取所有邻点ROI的并集作为顶点v的ROI

算法：
![](vx_images/391900721230151.png =400x)           ![](vx_images/532030721248577.png =328x)
### 自适应扰动机制
- Directed perturbation 定向扰动
定向扰动基于禁忌搜索。它执行Str迭代，其中每次迭代包括在N1⋃N2中选择最佳可接受的邻居解来替换当前解。每当顶点v被一个交换或插入移动算子移动时，v在接下来的tt次迭代中被禁止。
- Frequency-based perturbation 基于频率的扰动
基于频率的扰动是基于局部搜索过程中收集的顶点移动频率信息。它执行Str迭代。在每次迭代中，它选择移动最少的顶点执行随机交换或插入移动到当前解。更准确地说，如果只有一个顶点的频率最小，那么我们将该顶点插入到另一个随机位置。如果存在多个频率最小的顶点，则随机选择两个顶点进行交换。
- Random perturbation 随机扰动
随机扰动执行Str次随机交换或插入移动到当前解。
> 为了维持集中化和多样化之间的平衡（intensification and diversification），BLS使用了三种扰动算子，根据搜索状态动态改变不同的概率。我们的主要思路是以较低的概率使用定向扰动，因为它使用最佳的改进方法来寻找新的解，这是一个耗时的过程。随着访问的连续非改进局部最优值的增加，定向扰动的概率逐渐减小，而基于频率和随机扰动的概率增加，因此可以加强多样化。施加定向扰动的概率P为：
> $P = {P_0}*{e^{ - \omega /T}}$

T是终止条件（截止改进）
$\omega$ 截止改进的迭代次数
施加定向扰动的概率为P，施加频率扰动的概率为(1-P)×Q，施加随机扰动的概率为(1-P)×(1-Q)，Q为参数。
算法：
![](vx_images/279864422230151.png =444x)
在算法中，使用哈希表记录所有访问的局部最优解，
当迭代产生的局部最优解已存在于哈希表中，则扰动强度Str++；若局部最优解在哈希表中没有标注，表示搜索跳出了之前的局域，扰动强度被归于Str0。
### 讨论
BLS继承了两种元启发式算法的一些特性：迭代局部搜索(ILS)和禁忌搜索(TS)。
与ILS相同，BLS采用局部搜索寻找局部最优解和扰动跳出当前搜索空间。BLS与ILS的区别在于，在搜索过程中扰动强度是动态变化的，以不同的概率执行3种不同类型的扰动算子。此外，无论解的质量如何，局部搜索过程返回的局部最优解总是作为BLS的新起点被接受，这与ILS的接受准则完全不同。
BLS的定向扰动借鉴了TS的概念。TS的每次迭代都受到禁忌列表的约束，但BLS在其局部搜索阶段不考虑禁忌列表。因此，BLS的局部搜索和BLS的定向扰动可能会探索不同的局部最优解。而且，在传统方法中，随机移动是最常被选择的，这使得多样性非常强，导致局部搜索方法退化为多起点方法。该条件使得搜索无法搜索到局部最优解的附近区域。如果多样性太弱，则使得搜索不可能跳出当前局部最优或者在几个局部最优之间循环。
我们的BLS算法采用了基于搜索状态和运动历史的自适应扰动机制，使得搜索更加高效。
## 实验
### 实验算例
我们使用以下179个基准实例进行计算测试，这些实例最早由Jain et al ( 2016 )提出，后来由Cavero et al ( 2021 )使用。
- Small：该子集由84个图组成。顶点数为16 ~ 24，边数为18 ~ 49。
- Harwell_Boeing：该子集包括38个实例，它们来源于科学和工程领域中各种各样的问题。顶点数范围为39 ~ 685，边数范围为46 ~ 3720。
- Regular：该子集包含四种不同类型的图( Complete Split , Cones , Join Hypercubes , Toroidalmesh)，它们具有预定义和已知的结构，但具有未知的最优解。该集合包括57个图，顶点数从12到1000不等，边数从46到6225不等。
[CMPLIB_2010.zip](https://grafo.etsii.urjc.es/optsicom/cutwidth/cwp-files/CMPLIB_2010.zip)
> 部分算例和二维带宽最小化算例重复
### 实验环境
参数设置：
- T 终止条件（改进截止）：20
- K 触发扰动的改进截止：18
- Str0 初始扰动强度：0.15n
- Strmax 最大扰动强度：rand(0.4n,0.6n)
- tt 禁忌长度：0.1n
- P0 定向扰动的最大概率：0.05
- Q 施加频率扰动的概率参数：0.3
实验条件：
Java，Intel Core i5-8400 CPU 2.80 GHz 16 GB RAM
对比算法：
模因算法（MA）和多起点禁忌搜索（MTS）
每个算例运行30次
### 实验结果
BLS在31个算例上取得了突破，在139个算例得到了最好结果。

## 分析与讨论
## 总结









