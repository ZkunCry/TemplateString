
#include <iostream>
#include "String.h"

int main()
{
	String<wchar_t> str(L"Chlen");
	String<wchar_t> str2(L"Pizda");
	wcout<<str.SubStr(-1, 1);

	return 0;
}