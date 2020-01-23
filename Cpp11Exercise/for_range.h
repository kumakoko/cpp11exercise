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
 * \file for_range.h
 * \date 2018/10/28 10:30
 *
 * \author www.xionggf.com
 * Contact: sun_of_lover@sina.com
 *
 * \brief
 *
 * TODO: �µ�forѭ������ʽ
 *
 * \note
*/
#ifndef for_range_h__
#define for_range_h__

#include <list>
#include <iostream>
#include <vector>

void TestForRange()
{
	std::list<double> ls = { 1.23,4.56,7.89,234532.54,8965.1223 };
	std::cout << "ʹ�ô�ͳ��begin-end��ʽ����list\n";
	for (auto iter = ls.begin(); iter != ls.end(); ++iter) {
		std::cout << *iter << " ";
	}

	std::cout << "\n\n";
	std::vector<std::string> sv = { "apple","pear","grape","peach" };
	std::cout << "ʹ�û��ڷ�Χ��forѭ������vector<std::string> sv = {apple,pear,grape,peach}\n";
	std::cout << "��ʽ�ǣ� for (auto data : sv)\n";
	std::cout << "ע�������data�ǵ�������ָ������ݣ������ǵ���������\n";

	for (auto const& data : sv)
	{
		std::cout << data.c_str() << " ";
	}
}


#endif // for_range_h__
