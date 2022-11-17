#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "String.h"
#include <string>
void main()
{

	
	wsstring str(L"aalpha");
	wsstring str2(L"alpha");
	str.Push_front(L'c');
	wcout << str[0];
}