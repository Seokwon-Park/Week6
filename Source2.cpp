#include <iostream>
#include <string>

using namespace std;

template <class T_NAME>
class Vector2D
{
public:
	T_NAME x_, y_;

	Vector2D(const T_NAME& x_input, const T_NAME& y_input)
		: x_(x_input), y_(y_input)
	{	}

	void print()
	{
		cout << x_ << "," << y_ << endl;
	}
};

int main()
{
	Vector2D<int> int_vector(1, 1);

	int_vector.print();

	Vector2D<std::string> string_vector("Hello", "World");

	string_vector.print();
}
