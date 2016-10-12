#include <iostream>
#include <string>

using namespace std;



template<class T_CLASS>
void print(const T_CLASS& i)
{
	cout << i << endl;
}

int main()
{
	print(1);
	print(2.345f);
	print("Hello World");

	return 0;
}

