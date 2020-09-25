#pragma once
#include <vector>
#include <iostream>
#include <exception>

template <typename T>
class Matrix {
public:
	Matrix(const size_t, const size_t);
	Matrix(const size_t, const size_t, const T&);
	Matrix(const Matrix&);
	Matrix(Matrix&&);
	T& operator()(const size_t, const size_t);
	const T& operator()(const size_t, const size_t) const;
	size_t Get_N() const noexcept;
	size_t Get_M() const noexcept;
	std::vector<T> Get_Row(size_t) const noexcept;
	size_t Size() const noexcept;
	Matrix& operator+=(const Matrix&);
	Matrix& operator*=(const double);
	Matrix& operator=(const Matrix&);
	

private:
	
	std::vector< std::vector<T> > data;
	size_t n;
	size_t m;
	

};
template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
	for (size_t i = 0; i < matrix.Get_N(); ++i) {
		for (size_t j = 0; j < matrix.Get_M(); ++j) {
			std::cout << matrix(i, j) << ' ';
		}
		std::cout << std::endl;
	}
	return (out);
}

template<typename T>
Matrix<T>& operator+(const Matrix<T>& left, const Matrix<T>& right) {
	Matrix<T> result(left);
	result += left;
	return result;
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
inline Matrix<T>::Matrix(const Matrix& rhs)
{
	data = rhs.data;
	n = rhs.Get_N();
	m = rhs.Get_M();
}

template<typename T>
inline T& Matrix<T>::operator()(const size_t i, const size_t j)
{
	if (i >= n || j >= m) {
		throw std::out_of_range("Out of range");
	}
	return data[i][j];
}

template<typename T>
inline const T& Matrix<T>::operator()(size_t i, size_t j) const
{
	if (i >= n || j >= m) {
		throw std::out_of_range("Out of range");
	}
	return data[i][j];
}

template<typename T>
inline size_t Matrix<T>::Get_N() const noexcept
{
	return n;
}

template<typename T>
inline size_t Matrix<T>::Get_M() const noexcept
{
	return m;
}

template<typename T>
inline std::vector<T> Matrix<T>::Get_Row(size_t row) const noexcept
{
	return data[row];
}

template<typename T>
inline size_t Matrix<T>::Size() const noexcept
{
	return n * m;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix& rhs)
{
	if (n != rhs.Get_N() || m != rhs.Get_M()) {
		throw std::invalid_argument("Different dimensions of matrix");
	}
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			(*this)(i, j) += rhs(i, j);
		}
	}
	return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator*=(const double value)
{
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < m; ++j) {
			(*this)(i, j) *= value;
		}
	}
	return *this;
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
	if (n != rhs.Get_N() || m != rhs.Get_M()) {
		throw std::invalid_argument("Different dimensions of matrix");
	}
	data = rhs.data;
	n = rhs.Get_N();
	m = rhs.Get_M();
	return *this;
}