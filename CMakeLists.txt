cmake_minimum_required(VERSION 3.15)
project(web_server1_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(web_server1_1 main.cpp Server.cpp Server.h UtilFun.cpp UtilFun.h WebLimit.h Epoll.cpp Epoll.h Task.cpp Task.h Thread.cpp Thread.h ThreadPool.cpp ThreadPool.h EventLoop.cpp EventLoop.h EventLoopThread.cpp EventLoopThread.h HttpData.cpp HttpData.h)