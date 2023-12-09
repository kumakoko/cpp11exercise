/**************************************************************************************************************************
Copyright(C) 2014-2018 www.xionggf.com

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
/*!
 * \file initializer_list.h
 * \date 2018/10/27 20:58
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief
 *
 * TODO: 初始化列表的相关示例
 *
 * \note
*/
#ifndef initializer_list_h__
#define initializer_list_h__

#include <string>
#include <iostream>
#include <list>
#include <initializer_list>

class FooA
{
private:
	int i;
	double j;
	float k;
public:
	FooA(int _i, double _j, float _k) :i(_i), j(_j), k(_k) {}
	FooA(const FooA& rhs) :i(rhs.i), j(rhs.j), k(rhs.k) {}
	void Print() {
		std::cout << "i = " << i << " j = " << j << " k = " << k << std::endl;
	}
};

class FooB 
{
private:
	FooA fa;
	std::string s;
public:
	FooB(const FooA& _fa, const std::string& _s) :fa(_fa), s(_s) {}
	void Print() 
    {
		fa.Print();
		std::cout << "s = " << s << std::endl;
	}
private:
	FooB(const FooB& rhs);
};

// 自定义容器可以使用std::initializer_list容器来初始化容器的元素
template<typename T>
class MyList 
{
private:
	std::list<T> v;
public:
	MyList(std::initializer_list<T> init_list)
    {
		for (auto it = init_list.begin(); it != init_list.end(); ++it) 
        {
			v.emplace_back(*it);
		}
	}

	void Print()
    {
		for (auto it = v.begin(); it != v.end(); ++it)
        {
			std::cout << *it << " ";
		}

		std::cout << std::endl;
	}
};

void TestInitializerList()
{
	std::cout << "TestInitializerList function \n";
	FooA fa = { 1,2.3,4.5f }; // 使用初始化列表，各参数的顺序和构造函数的参数声明顺序相同
	FooB fb = { fa,"I am FooB" };
	fb.Print();

	MyList<int> ls = { 234,4325,5760,2345,84,9120 };
	ls.Print();
}


#endif // initializer_list_h__
