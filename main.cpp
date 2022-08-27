#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "String.h"


int main()
{
	sstring base = "this is an example phrase.";
	sstring base2;
	base2.readfile("text.txt");
	cout << base2<<"\nSize: "<<base2.Size()<<endl;
	cout << "Resize\n"; 
	base2.Resize(40);
	cout << "New size\n" << base2.Size()<<endl;
	base2.Push_back('c');

	return 0;
}