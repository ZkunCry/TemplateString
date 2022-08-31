#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "String.h"


int main()
{
	sstring s1("this");
	sstring::const_iterator it = s1.cbegin();
	sstring::const_iterator it2 = s1.cend();
	s1.Replace(it, it2,"apple");
	cout << s1;
	return 0;
}