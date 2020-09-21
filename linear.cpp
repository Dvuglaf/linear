// linear.cpp: определяет точку входа для приложения.
//

#include "linear.h"
#include "matrix.h"

using namespace std;

int main()
{
	Matrix<int> mat(5,5, 1);
	mat.Print();
	mat(0, 0) = 0;
	mat.Print();
	return 0;
}
