#include <iostream>
#include "String.h"

int main(void)
{
	String<char> str("Example");
	cout<<str.SubStr(0,4)<<endl;
	return 0;
}