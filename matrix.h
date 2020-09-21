#pragma once
#include <vector>
#include <iostream>

template <typename T>
class Matrix {
public:
	Matrix();
	Matrix(size_t, size_t);
	Matrix(const size_t, const size_t, const T&);
	Matrix(const Matrix&);
	Matrix(Matrix&&);
	int& operator()(size_t, size_t);

	void Print();


private:
	
	std::vector< std::vector<T> > data;
	size_t n;
	size_t m;
	

};

template<typename T>
inline Matrix<T>::Matrix()
{
	
	
}

template<typename T>
inline Matrix<T>::Matrix(size_t rows, size_t columns){
	n = rows;
	m = columns;
	for (size_t i = 0; i < rows; ++i)
		data.push_back(std::vector<T>(columns, 0));
}

template<typename T>
inline Matrix<T>::Matrix(const size_t rows,const size_t columns, const T& value){
	n = rows;
	m = columns;
	for (size_t i = 0; i < rows; ++i)
		data.push_back(std::vector<T>(columns, value));
}

template<typename T>
inline int& Matrix<T>::operator()(size_t i, size_t j)
{
	return data[i][j];
}

template<typename T>
inline void Matrix<T>::Print(){
	for (auto& i : data) {
		for (auto& j : i) {
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}

}




