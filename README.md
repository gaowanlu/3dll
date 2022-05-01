# 3dll 使用C++实现简单的3D渲染

## 代码

代码请见github代码仓库 [https://github.com/gaowanlu/3dll](https://github.com/gaowanlu/3dll)

## 为什么写了它

没学过计算机图形学、图像处理课程的菜鸡最近在总结线性代数、突然脑子一热代码上头了 、线代的魅力太精彩了。  
如果能够理解下面的大致过程一定会会对线性变换、基变换、以及可能我们听说过的图像坐标系、世界坐标系、摄像机坐标系。  
这不仅仅在某个方向涉及这些，例如机器人视觉定位SLAM以及3D动画、游戏开发都会与这些密切相关，以前我也接触过RoboMaster的机器人视觉开发、做过图像处理，
但这是我的一个尝试，如果你有兴趣的话可以尝试一下，我想会非常有趣，这里并没有选择专业的渲染工具，如OpenGL、以及图像处理的OpenCV，我想用一个简单的例子理解较多的知识是最重要的。
在此我们使用EasyX与Eigen3  ，有人说为什么不去学OpenGL、我只能说术业有专攻我从没接触过他，我用简单的实现原理来帮助我理解线性代数、而非为了渲染效率工程专业性上考虑。

## 实现效果

1、相机坐标系的旋转

![在这里插入图片描述](https://img-blog.csdnimg.cn/ec2443792805477ab7bcd7906cf2edca.png#pic_center)


2、鼠标点击且移动鼠标进行x与y轴的旋转、Ctrl+滚轮 支持z轴旋转

![在这里插入图片描述](https://img-blog.csdnimg.cn/f951e4aed6c342a596c64cdd4d55d9ff.png#pic_center)


3、滚轮对为相机位置向量进行放缩

![在这里插入图片描述](https://img-blog.csdnimg.cn/957d1133dfbf4405885b0a7e336588aa.png#pic_center)



## 快速开始

```shell
git clone https://hub.fastgit.xyz/gaowanlu/3dll.git
```

或在Github [https://github/gaowanlu/3dll](https://github/gaowanlu/3dll)、获取最新的工程效果  

请使用Visual Studio 2022 打开项目  ，或者自己使用其他IDE进行构建  
  
## 线性代数

课程推荐  

* Bilibili MIT线性代数课程 https://www.bilibili.com/video/BV1ix411f7Yp  
* 线性代数的本质  https://www.bilibili.com/video/BV1ib411t7YR   

## 路漫漫  

我们有时我们觉得一切东西没有太大用途、那是我们的认知水平还不够、在学习的路上、书山有路勤为径、学海无涯苦作舟。
