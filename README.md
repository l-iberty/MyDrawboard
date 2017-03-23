# MyDrawboard
A simple drawing-board

# How to implements a plugin?
* 使用 Qt Creator 创建 C++ Library 工程, 子类化`Shape`, 并实现两个重要的导出函数

# 1.0
* 目前只实现了直线、矩形、椭圆、圆的绘制与拖拽, 而且直线的拖拽还存在问题(`bool Line::contains(QPoint &)` 判断点到直线的距离存在 BUG)
* 后续将添加三角形和多边形等插件
