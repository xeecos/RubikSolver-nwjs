# 解三阶魔方舵机机器人
 * nw程序通过摄像头采集图像实现魔方六面颜色识别，计算出解魔方步骤后，转换成舵机旋转指令发送给MegaPi执行。
 * **MegaPi**通过串口接收来自上位机nw程序的运动指令驱动舵机。
 * **Makeblock**材料搭建解魔方抓取和旋转机构
### 准备工作
 * 安装Node WebKit（ http://nwjs.org ）
 * ```git clone https://github.com/xeecos/RubikSolver-nwjs```
 * 将代码复制到Node WebKit文件夹中
 * 硬件组装
 ![cubes](https://github.com/xeecos/RubikSolver-nwjs/raw/master/assets/images/5.jpg)
 * 安装**Arduino IDE**（ https://arduino.cc/ ）
 * 安装**Makeblock libraries**（ https://github.com/Makeblock-official/Makeblock-Libraries ）到Arduino IDE安装目录下libraries中
 * 并通过Arduino IDE烧写**MegaPi**程序（ https://github.com/xeecos/RubikSolver-nwjs/Arduino/Arduino.ino ）
 * 连接摄像头
 * MegaPi插上12V电源适配器

### 运行
 * 运行nw.exe
 * 演示视频（ youtube - https://youtu.be/3c3i0LgJrCc ，youku - http://v.youku.com/v_show/id_XMTY2MzE5MTcwMA==.html ）

###工作原理

**魔方基本元素**
### 结构

三阶魔方由1个中心轴、6个中心块、12个边块及8个角块构成，当它们组合在一起的时候每个零件会互相牵制不会散开，并且任何一面都可水平转动而不影响到其他方块。三阶魔方的结构不只一种，例如空心魔方。
 * 中心块
  
  中心块与中心轴连接在一起，但可以顺着轴的方向自由地转动。

 * 边块
  
  边块的表面是两个正方形，结构类似一个长方体从立方体的一个边凸出来，这样的结构可以让边块嵌在两个中心块之间。

 * 角块
  
  角块的表面是三个正方形，结构类似一个小立方体从立方体的一个边凸出来，这样的结构可以让角块嵌在三个边块之间。

 * 每个块的编号
 
  ![cubes](https://github.com/xeecos/RubikCubeSolver/raw/master/images/1.jpg)

### 解魔方动作的书写方式
  U的转法，即顺时钟转动上层，为了记录下复原、转乱的过程或公式的步骤，会用Singmaster符号来书写（由David Singmaster发明）。
  
  书写方式如下：
  * R(Right)、L(Left)、U(Up)、D(Down)、F(Front)、B(Back)分别代表右、左、上、下、前、后层。
  * 若是顺时针旋转，则直接写上符号；若是逆时针旋转，则在符号后加上“'”或是“i”；若是旋转180°，则在符号后加上“2”或是“²”。
  * 若要更加详细纪录整个过程，还会使用以下符号：
    - x、y、z分别代表将整个魔方做R、U、F，因为在速解魔方的时候，并不会总是将一个面朝向自己。
    - r、l、u、d、f、b分别代表右、左、上、下、前、后两层，代表连中间层一起转。
    - M(Middle)、E(Equator)、S(Side)代表旋转中间层，相当于Rr'、Uu'、Bb'。

## 解魔方算法

 * CFOP（又称弗雷德里奇法（Fridrich Method））是速解魔方最常用的公式系统之一，由底十字（Cross）、下两层（F2L，First 2 Layers）、顶层定向（OLL，Orientation of last layer）、顶层排列（PLL，Permutation of last layer）四个步骤组成。
 * 本项目使用的算法来源：http://en.wikipedia.org/wiki/Optimal_solutions_for_Rubik's_Cube#Thistlethwaite.27s_algorithm
 * Javascript版本：https://github.com/stringham/rubiks-solver
 
## 图像采集和颜色识别
 * 使用Chrome API - Navigator.getUserMedia()获取摄像头图像，并通过canvas获取元素RGB数据。
 * 由于魔方六面中心位置颜色固定，摄像头采集到所有魔方颜色与这六种颜进行色比较，最接近的颜色可以判断为当前魔方格子的颜色。
 
