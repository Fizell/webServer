### 项目简介

本项目是由C++实现的web服务器，采用高效的Reactor事件分发模式，支持高并发的http请求。

### 系统环境

- 系统：Ubuntu16.04
- 编译器：g++ 7.4.0

### 项目构建工具

cmake 3.1.5

### 项目构建方法

```
git init
git clone https://github.com/Fizell/webServer.git
cd webServer
mkdir build
cd build
cmake ..
make
./web_server1.1
```

- 端口配置在main.cpp
- 各项服务器配置在WebLimit.h
- 默认页面为build目录的index.html(手动添加)

### 主要技术：

- epoll事件驱动I/O
- 使用Reactor模型+线程池进行客户端连接任务管理
- 使用RAII方法管理内存资源。
- 使用eventfd事件进行线程唤醒
- 模仿muduo网络库实现的简单eventLoop循环
- 利用优先队列实现的定时器



### 改进方向

- 使用对象池优化掉新连接时HttpData对象和Task对象的构建消耗
- 使用log记录操作日志
- 构造应用层缓存区

参考大神代码：<https://github.com/linyacool/WebServer>
