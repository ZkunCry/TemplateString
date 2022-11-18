#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "String.h"
#include <string>

void main()
{
	String<char> str("alpha");
	String<char> str2("alphatwo");
	str.assign(std::move(str2));
	cout << str;
}