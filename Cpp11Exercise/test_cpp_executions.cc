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

/*
请介绍STL中的 std::execution::sequenced_policy，std::execution::parallel_policy，std::execution::parallel_unsequenced_policy三者的区别
ChatGPT
std::execution::sequenced_policy, std::execution::parallel_policy, and std::execution::parallel_unsequenced_policy are execution
policies introduced in C++17 and expanded upon in C++20. They are part of the Standard Template Library (STL) and are used to
specify the kind of parallelism that should be used in certain algorithms. Here's a brief overview of each:

std::execution::sequenced_policy:

This policy ensures that an algorithm will execute its operations in sequence, meaning one after the other, on the calling thread.
It does not introduce any parallelism.
Use this when you want to guarantee sequential execution order or when you are dealing with code that is not thread-safe.
In code, it is denoted by std::execution::seq.
std::execution::parallel_policy:

When this policy is used, the algorithm can execute its operations in parallel on multiple threads. This can speed up the
execution on multi-core processors.
It is important to ensure that operations are thread-safe when using this policy because multiple operations might be performed
at the same time.
In code, it is denoted by std::execution::par.
std::execution::parallel_unsequenced_policy:

This is a more aggressive form of parallelism than std::execution::parallel_policy. It allows not only parallel execution on
multiple threads but also permits vectorization, where a single operation is applied to multiple elements at once if the hardware supports it.
This policy should only be used when operations do not interfere with each other in any way, as there are no sequence points between operations.
In code, it is denoted by std::execution::par_unseq.

Choosing the right execution policy depends on the specifics of the problem, the algorithm, and the system on which the code is running.
For example, if you have a CPU-intensive task that can be easily divided into independent sub-tasks, std::execution::parallel_policy can
be a good fit. On the other hand, if you are performing simple operations on large data sets that could benefit from SIMD (Single Instruction,
Multiple Data) optimizations, std::execution::parallel_unsequenced_policy might offer the best performance.

It is important to note that not all algorithms in the STL support these execution policies, and the ones that do are marked as such in
the documentation. Additionally, using these policies may require linking against specific libraries that provide the parallel or vectorized
implementations.

C++标准库中的std::execution命名空间定义了三种执行策略，分别是std::execution::sequenced_policy，std::execution::parallel_policy和
std::execution::parallel_unsequenced_policy，这些策略用于指定STL算法的执行方式。这些策略是C++17引入的，并用于并行化STL算法的执行。以下是它们的主要区别：

std::execution::sequenced_policy：

该策略表示算法将以顺序的方式执行，即不会并行化。
这是默认策略，当你不指定执行策略时，STL算法通常会采用这种策略。
适用于那些不能并行执行的操作或者在并行执行时会导致竞态条件的操作。
std::execution::parallel_policy：

该策略表示算法可以并行执行，但不保证执行顺序。
算法可能会以任意顺序并行执行，具体取决于实现和硬件。
适用于那些可以安全并行执行的操作，但不关心执行顺序的情况。
std::execution::parallel_unsequenced_policy：

该策略表示算法可以以无序的、不可预测的方式并行执行。
这意味着算法不仅不保证执行顺序，而且还可能在不同的线程之间以不同的顺序执行不同的元素。
适用于那些可以并行执行且不需要特定执行顺序的操作。
这些执行策略的选择取决于你的算法和数据的特性以及性能需求。通过选择合适的执行策略，你可以在不同的场景中充分利用多核处理器和并行计算资源来加速STL算法的执行。
注意，要使用这些执行策略，你需要使用C++17或更高版本的标准，并确保你的编译器和标准库支持这些功能。
*/

#include <execution>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <windows.h>
#include <random>

using STL_TimePoint = std::chrono::steady_clock::time_point;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    STL_TimePoint start_time;
    STL_TimePoint end_time;
    std::chrono::microseconds duration;

    const std::size_t ELEM_COUNT = 1000000;
    std::vector<float> v1;//(ELEM_COUNT);
    std::vector<float> v2;//(ELEM_COUNT);
    int c = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    float mean = 0.0f;
    float stddev = 1.0f;
    std::normal_distribution<float> d(mean, stddev);

    for (std::size_t i = 0; i < ELEM_COUNT; ++i)
    {
        float f = d(gen);
        v1.push_back(f);
        v2.push_back(f);
    }

    // 以int& x的方式处理传递进来的vector元素，表示要写入值到vector中
    // 以std::execution::par方式处理for_each，表示由系统负责开启并行
    // 计算的方式去执行每一项的元素，因为每一项的元素都是各自加上5，互
    // 不影响，故而可以以这种方式去使用for_each算法
    start_time = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::par, v1.begin(), v1.end(), [](float& x) {
        x += 5.0f; });
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "std::execution::par并行执行for_each算法操作耗时: " << duration.count() << " 微秒" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::par_unseq, v1.begin(), v1.end(), [](float& x) {
        x += 6.0f; });
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "std::execution::par_unseq并行执行for_each算法操作耗时: " << duration.count() << " 微秒" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::seq, v1.begin(), v1.end(), [](float& x) {
        x += 7.0f; });
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "std::execution::seq并行执行for_each算法操作耗时: " << duration.count() << " 微秒" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    std::for_each(v1.begin(), v1.end(), [](float& x) {
        x += 8.0f; });
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "非并行执行for_each算法操作耗时: " << duration.count() << " 微秒" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    std::sort(v1.begin(), v1.end());
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "非并行执行sort算法操作耗时: " << duration.count() << " 微秒" << std::endl;

    start_time = std::chrono::high_resolution_clock::now();
    std::sort(std::execution::par_unseq, v2.begin(), v2.end());
    end_time = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "std::execution::par_unseq并行执行sort算法操作耗时: " << duration.count() << " 微秒" << std::endl;

    system("PAUSE");
    return 0;
}