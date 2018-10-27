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
 * \file type_derivation.h
 * \date 2018/10/27 17:39
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief C++11中的一些类型推导语法
 *
 * TODO: C++11中的一些类型推导语法
 *
 * \note
*/
#ifndef type_derivation_h__
#define type_derivation_h__

#include <iostream>
#include <sstream>
#include <typeinfo>
#include <complex>

// 利用对表达式(*(T1*)0) + (*(T2*)0)的推导，得出函数的返回值类型
template<typename T1, typename T2>
decltype((*(T1*)0) + (*(T2*)0)) add(T1 param1, T2 param2) {
	return param1 + param2;
}

// C++ 11新语法支持，函数签名前使用auto关键字，函数签名后用 ->decltype(具体表达式)的方式求得类型
template<typename T1, typename T2>
auto multiply(T1 param1, T2 param2) -> decltype(param1*param2) {
	return param1 * param2;
}

template<typename T1, typename T2>
auto subtract(T1 param1, T2 param2)->decltype(param1 - param2) {
	return param1 - param2;
}

void TestTypeDerivation() {
	float t1 = 5.6f;
	float t2 = 7.8f;
	std::complex<double> c1(1.2, 3.4);
	std::complex<double> c2(3.14, 2.72);
	auto r1 = multiply(t1, t2);
	auto r2 = add(t1, t2);
	auto r3 = subtract(c1, c2);

	std::stringstream ss;
	ss << "Test type derivation: " << std::endl;
	ss << "The return type of multiply function is " << typeid(r1).name() << std::endl;
	ss << "multiply(" << t1 << "," << t2 << ") = " << r1 << std::endl << std::endl;
	std::cout << ss.str();

	ss.str(""); 
	ss << "The return type of add function is " << typeid(r2).name() << std::endl;
	ss << "add(" << t1 << "," << t2 << ") = " << r2 << std::endl << std::endl;
	std::cout << ss.str();

	ss.str("");
	ss << "The return type of subtract function is " << typeid(r3).name() << std::endl;
	ss << "subtract(" << c1 << "," << c2 << ") = " << r3 << std::endl << std::endl;
	std::cout << ss.str();
}

#endif // type_derivation_h__
