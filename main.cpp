
#include <iostream>
#include "String.h"

int main()
{
	String<wchar_t> str;
	String<char> str2;
	str2.find('c', -5);
	return 0;
}