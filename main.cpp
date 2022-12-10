
#include <iostream>
#include "String.h"

int main()
{
	String<wchar_t> str(L"x");
	String<wchar_t> str2(L"Pizda");
	str.append(L"ss", -1);
	return 0;
}