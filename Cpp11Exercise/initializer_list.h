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
 * TODO: ��ʼ���б�����ʾ��
 *
 * \note
*/
#ifndef initializer_list_h__
#define initializer_list_h__

#include <string>
#include <iostream>

class FooA {
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

class FooB {
private:
	FooA fa;
	std::string s;
public:
	FooB(const FooA& _fa, const std::string& _s) :fa(_fa), s(_s) {}
	void Print() {
		fa.Print();
		std::cout << "s = " << s << std::endl;
	}
private:
	FooB(const FooB& rhs);
};

void TestInitializerList() {
	std::cout << "TestInitializerList function \n";
	FooA fa = { 1,2.3,4.5f }; // ʹ�ó�ʼ���б���������˳��͹��캯���Ĳ�������˳����ͬ
	FooB fb = { fa,"I am FooB" };
	fb.Print();
}


#endif // initializer_list_h__
