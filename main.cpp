#include <iostream>
#include "String.h"
#include <memory>
#include <list>
#include <vector>
#include <string>
int main()
{
	String<char> str2("1234");
	String<char> str(str2, 2, 9);
	cout << str.Capacity();
	return 0;
}