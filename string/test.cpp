#include<iostream>
#include"string.h"
using namespace stringstl;


int main()
{
	string s1("hello world");
	/*s1.resize(20, '#');
	string::iterator it = s1.begin();
	while (it != s1.end())
	{
		std::cout << *it << ' ';
		it++;
	}
	std::cout << std::endl;
	std::cout <<s1.c_str()<< std::endl;
	std::cout << s1.size()<< std::endl;
	std::cout << s1.capacity() << std::endl;*/
	s1.insert(0, "hello ");
	std::cout << s1.c_str() << std::endl;
	s1.erease(1);
	std::cout << s1.c_str() << std::endl;
	return 0;
}
