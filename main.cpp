#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "String.h"
#include <string>

void main()
{
	
	/*String<char> str2("alphatwo");
	String<char> str("pizda");
	str = std::move(str2);
	cout << str;*/
	String<char> str("Pizda");
	char buf[20];

	cout << str.Copy(buf, 7, 1);
	
}