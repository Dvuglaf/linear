// linear.cpp: определяет точку входа для приложения.
//

#include "linear.h"
#include "matrix.h"
#include <iostream>


int main()
{
	Matrix<int> mat1(5, 4, 1);
	Matrix<int> mat2(5, 5, 2);
	mat1 *= 7;
	std::cout << mat1;
	return 0;
}
