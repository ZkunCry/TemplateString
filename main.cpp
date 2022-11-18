#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "String.h"
#include <string>

void main()
{
	String<wchar_t> str(L"alpha");
	String<char> str2("bga");
	str.Replace(0, str.Size()-2, L"Pizda");
	wcout << str;
}