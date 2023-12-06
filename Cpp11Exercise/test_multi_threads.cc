/**************************************************************************************************************************
Copyright(C) 2014-2017 www.xionggf.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute,sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM,OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**************************************************************************************************************************/
/*
参考链接：
https://blog.csdn.net/CSSS_2021/article/details/129509121
cpp execution要C++20版本才支持

C++17向标准库加入了并行算法函数，它们是多个函数的重载，如“std::fiind()、std::transform()和std::reduce()”，
其操作的目标都是容器区间，相比对应的单线程版本，并行版本具有相同的函数签名，只是新增了一个参数，该参数排在参数
列表的第一位，用于设定执行策略：
*/



#include <execution>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <random>
#include <thread>

using STL_TimePoint = std::chrono::steady_clock::time_point;

class func
{
public:
    int& i; // 这里传引用而不是复制一个副本
    func(int& i_) : i(i_) {}
    void operator() ()
    {
        for (unsigned j = 0; j < 100; ++j)
        {
            // 存在着线程还没结束所引用的i就已经失效的风险
            std::cout << i << std::endl;
        }
    }
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int some_local_state = 0;
    func my_func(some_local_state);
    std::cout << "my_thread begins and main thread stop running" << std::endl;
    std::thread my_thread(my_func);
    //my_thread.detach(); // 使用detach. 不等待线程结束。新线程可能还在运行。而局部变量some_local_state已经失效了
    my_thread.join(); // 将my_thread.detach() 替换为 my_thread.join() ，就可以确保局部变量在线程完成后，
                      // 才被销毁。join用来阻塞当前线程退出，join表示my_thread线程运行起来了。但是也阻碍了main线程的
                      // 退出。也就是说，如果 f 的执行需要 5秒钟， main也要等待5秒才能退出。
    std::cout << "my_thread ends and main thread continue running" << std::endl;
    system("PAUSE");
    return 0;
}