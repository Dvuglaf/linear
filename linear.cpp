// linear.cpp: определяет точку входа для приложения.
//

#include "linear.h"
#include "matrix.h"
#include <iostream>
#include "complex.h"
#include <complex>
#include <vector>
#include "vector.h"
#include "var.h"
#include <cstring>
#include <unordered_map>
#include <variant>
#include <stack>
#include <any>
#include <regex>
#include <type_traits>

const std::string ALPHABET = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::string OPERATIONS = { "+-*/" };
const std::string SCALAR = { "1234567890." };
std::unordered_map<std::string, std::variant<linear::complex, linear::vector, matrix, double>> map;

bool valid_name(const std::string& name) {
	for (auto& symbol : name) {
		if (ALPHABET.find(symbol) == std::string::npos) {
			return false;
		}
	}
	return true;
}

bool valid_scalar(const std::string& name) {
	for (auto& symbol : name) {
		if (SCALAR.find(symbol) == std::string::npos) {
			return false;
		}
	}
	return true;
}

std::string replace_in_string(const std::string& string, const std::regex& substring, const std::string& replacement) {
	
	return std::regex_replace(string, substring, replacement);
}

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

void delete_space_before(std::string& expression, const char symbol) {
	auto pos = expression.find(symbol);
	if (pos != std::string::npos) {
		for (size_t i = 0; i < pos; ++i) {
			if (expression[i] == ' ') {
				expression.erase(i, 1);
				--i;
			}
		}
	}
}

bool exist_name_in_map(const std::string& name) {
	return (map.find(name) == map.end()) ? false : true;
}

void split(const std::string& user_enter, std::string& left, std::string& right) {
	auto pos = user_enter.find('=');
	if (pos == std::string::npos) {
		left = user_enter.substr(0, user_enter.size());
		right = "none";
		return;
	}
	left = user_enter.substr(0, pos);
	right = user_enter.substr(pos + 1, user_enter.size() - pos - 1);
}

void count(std::stack<char>& t, std::stack<std::variant<linear::complex, linear::vector, matrix, double>>& e, const char symbol) {
	auto first = e.top();
	e.pop();
	auto second = e.top();
	e.pop();
	switch (t.top()) {
	case '+':
		if (first.index() == 0) {
			if (second.index() == 0) {
				auto result = std::get<linear::complex>(first) + std::get<linear::complex>(second);
				e.push(result);
			}
			else if (second.index() == 3) {
				auto result = std::get<linear::complex>(first) + std::get<double>(second);
				e.push(result);
			}
			else
				throw std::string("Different types!");

		}
		else if (first.index() == 1) {
			if (second.index() == 1) {
				auto result = std::get<linear::vector>(first) + std::get<linear::vector>(second);
				e.push(result);
			}
			else if (second.index() == 3) {
				auto result = std::get<linear::vector>(first) + std::get<double>(second);
				e.push(result);
			}
			else 
				throw std::string("Different types!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				auto result = std::get<matrix>(first) + std::get<matrix>(second);
				e.push(result);
			}
			else if (second.index() == 3) {

			}
			else
				throw std::string("Different types!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				auto result = std::get<double>(first) + std::get<linear::complex>(second);
				e.push(result);
			}
			else if (second.index() == 1) {
				auto result = std::get<double>(first) + std::get<linear::vector>(second);
				e.push(result);
			}
			else if (second.index() == 2) {
				//auto result = std::get<double>(first) + std::get<matrix>(second);
				//e.push(result);
			}
			else if (second.index() == 3) {
				auto result = std::get<double>(first) + std::get<double>(second);
				e.push(result);
			}
		}
		break;
	case '-':
		if (first.index() == 0) {
			if (second.index() == 0) {
				auto result = std::get<linear::complex>(second) - std::get<linear::complex>(first);
				e.push(result);
			}
			else if (second.index() == 3) {
				auto result = std::get<linear::complex>(second) - std::get<double>(first);
				e.push(result);
			}
			else
				throw std::string("Different types!");

		}
		else if (first.index() == 1) {
			if (second.index() == 1) {
				auto result = std::get<linear::vector>(second) - std::get<linear::vector>(first);
				e.push(result);
			}
			else if (second.index() == 3) {
				auto result = std::get<double>(second) - std::get<linear::vector>(first);
				e.push(result);
			}
			else
				throw std::string("Different types!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				//auto result = std::get<matrix>(first) - std::get<matrix>(second);
				//e.push(result);
			}
			else if (second.index() == 3) {

			}
			else
				throw std::string("Different types!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				auto result = std::get<linear::complex>(second) - std::get<double>(first);
				e.push(result);
			}
			else if (second.index() == 1) {
				auto result = std::get<linear::vector>(second) - std::get<double>(first);
				e.push(result);
			}
			else if (second.index() == 2) {
				//
			}
			else if (second.index() == 3) {
				auto result = std::get<double>(second) - std::get<double>(first);
				e.push(result);
			}
		}
		break;
	case '*':
		if (first.index() == 0) {
			if (second.index() == 0) {
				auto result = std::get<linear::complex>(first) * std::get<linear::complex>(second);
				e.push(result);
			}
			else if (second.index() == 3) {
				auto result = std::get<linear::complex>(first) * std::get<double>(second);
				e.push(result);
			}
			else
				throw std::string("Different types!");

		}
		else if (first.index() == 1) {
			/*if (second.index() == 1) {
				auto result = std::get<linear::vector>(first) * std::get<linear::vector>(second);
				e.push(result);
			}*/
			if (second.index() == 3) {
				auto result = std::get<linear::vector>(first) * std::get<double>(second);
				e.push(result);
			}
			else
				throw std::string("Different types!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				auto result = std::get<matrix>(first) * std::get<matrix>(second);
				e.push(result);
			}
			else if (second.index() == 3) {

			}
			else
				throw std::string("Different types!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				auto result = std::get<double>(first) * std::get<linear::complex>(second);
				e.push(result);
			}
			else if (second.index() == 1) {
				auto result = std::get<double>(first) * std::get<linear::vector>(second);
				e.push(result);
			}
			else if (second.index() == 2) {
			//
			}
			else if (second.index() == 3) {
				auto result = std::get<double>(first) * std::get<double>(second);
				e.push(result);
			}
		}
		break;
	case '/':
		if (first.index() == 0) {
			if (second.index() == 0) {
				auto result = std::get<linear::complex>(second) / std::get<linear::complex>(first);
				e.push(result);
			}
			else if (second.index() == 3) {
				auto result = std::get<linear::complex>(second) / std::get<double>(first);
				e.push(result);
			}
			else
				throw std::string("Different types!");

		}
		else if (first.index() == 1) {
			if (second.index() == 1) {
				//
			}
			else if (second.index() == 3) {
				auto result = std::get<double>(second) / std::get<linear::vector>(first);
				e.push(result);
			}
			else
				throw std::string("Different types!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				//auto result = std::get<matrix>(first) + std::get<matrix>(second);
				//e.push(result);
			}
			else if (second.index() == 3) {

			}
			else
				throw std::string("Different types!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				auto result = std::get<linear::complex>(second) / std::get<double>(first);
				e.push(result);
			}
			else if (second.index() == 1) {
				auto result = std::get<linear::vector>(second) / std::get<double>(first);
				e.push(result);
			}
			else if (second.index() == 2) {
				//
			}
			else if (second.index() == 3) {
				auto result = std::get<double>(second) / std::get<double>(first);
				e.push(result);
			}
		}
		break;
	}
	t.pop();
	if (symbol != ' ') {
		t.push(symbol);
	}
}

std::variant<linear::complex, linear::vector, matrix, double> zamelsonand_bauer(std::string& expression) {
	expression = '(' + expression + ')';
	std::stack<std::variant<linear::complex, linear::vector, matrix, double>> e;
	std::stack<char> t;
	e.push(0);
	t.push('$');
	size_t i = 0;
	char symbol = expression[i];
	char prev = ' ';
	while(true) {
		symbol = expression[i];
		if (symbol == '\0')
			symbol = '$';
		if (prev == '(' && symbol == '+' || symbol == '-') {
			if (e.top().index() == 0) {
				e.push(linear::complex(0,0));
			}
			else if (e.top().index() == 1) {
				e.push(linear::vector(0, 0));
			}
			else if (e.top().index() == 2) {
				e.push(matrix(0, 0));
			}
			else if (e.top().index() == 3) {
				e.push(0.0);
			}
		}
		if (ALPHABET.find(symbol)!=std::string::npos) {
			std::string name;
			while (ALPHABET.find(symbol) != std::string::npos) {
				name.push_back(symbol);
				++i;
				prev = symbol;
				symbol = expression[i];
			}
			if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/' && symbol != ')')
			{
				throw std::string("Error: incorrect expression!");
			}
			
			if (!exist_name_in_map(name))
				throw std::string("Unknown name!");
			e.push(map[name]);
			continue;
		}
		else if (std::string(SCALAR).find(symbol) != std::string::npos) {
			std::string number;
			while (SCALAR.find(symbol) != std::string::npos) {
				number.push_back(symbol);
				++i;
				prev = symbol;
				symbol = expression[i];
			}
			std::cout << number << std::endl;
			e.push(std::stod(number));
			continue;
		}
		else if (symbol == '+' || symbol == '-') {
			if (t.top() == '(')
				t.push(symbol);
			else if (t.top() == '+' || t.top() == '-')
				count(t, e, symbol);
			else if (t.top() == '*' || t.top() == '/') {
				count(t, e, ' ');//4
				prev = symbol;
				continue;
			}
			else if (t.top() == '(' || t.top() == '$')
				t.push(symbol);
		}
		else if (symbol == '*' || symbol == '/') {
			if (t.top() == '(' || t.top() == '+' || t.top() == '-' || t.top() == '$')
				t.push(symbol);
			else if (t.top() == '*' || t.top() == '/')
				count(t, e, symbol);
		}
		else if (symbol == '(')
			t.push(symbol);
		else if (symbol == ')') {
			if (t.top() == '$')
				throw std::string("Error!");
			else if (t.top() == '(')
				t.pop();
			else if (t.top() == '+' || t.top() == '-' || t.top() == '*' || t.top() == '/') {//4
				count(t, e, ' ');//
				prev = symbol;
				continue;
			}
		}
		else if (symbol == '$') {
			if (t.top() == '(')
				throw std::string("Error!");
			else if (t.top() == '+' || t.top() == '-' || t.top() == '*' || t.top() == '/') {//4
				count(t, e, ' ');
				prev = symbol;
				continue;
			}
			else if (t.top() == '$')
				return e.top();
		}
		else if (symbol == ' ') {
			++i;
			prev = symbol;
			continue;
		}
		else if (OPERATIONS.find(symbol) == std::string::npos) {
			throw std::string("Unknown operation!");
		}
		++i;
		prev = symbol;
	}
}

void coma_split(const std::string& expression, std::string& left, std::string& right) {
	auto pos = expression.find(',') + 1;
	auto left_begin = expression.find('(') + 1;
	auto right_end = expression.find_last_of(')') ;
	if (left_begin == std::string::npos || right_end == std::string::npos) {
		throw std::string("Invalid syntax!");
	}
	left = expression.substr(left_begin, pos - left_begin - 1);
	right = expression.substr(pos, right_end - pos );
}

bool create_double(std::string& expression, const std::string& func) {
	const std::vector<std::string> functions = { "abs", "arg" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;
}

bool create_vector(std::string& expression, const std::string& func) {
	const std::vector<std::string> functions = { "cross_product", "vector" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;

}

size_t number_of_substring_in_string(const std::string& string, const std::string& substing) {
	size_t result = 0;
	for (std::string::size_type i = 0; i < string.length(); ++i)
		if (string[i] == substing[0])
			if (string.substr(i, substing.length()) == substing)
			{
				++result;
				i += substing.length() - 1;
			}
	return result;
}

size_t number_of_space(std::string& expression, const size_t start, const size_t stop) {
	size_t result = 0;
	for (size_t i = start; i < stop; ++i) {
		if (expression[i] == ' ') {
			++result;
		}
	}
	return result;
}

std::string function_name(std::string& expression) {
	const std::vector<std::string> functions = { "abs","arg","conj","exp","log","sqrt", "pow", "transpose", "complex", "vector" };
	std::string result = "";
	for (auto& it : functions) {
		if (expression.find(it) != std::string::npos) {
			result = it;
		}
		if (number_of_substring_in_string(expression, it) > 1) {
			throw std::string("Error: more than one function!");
		}
	}
	return result != "" ? result : "none";
}

bool create_complex(const std::string& func, std::string& expression) {
	const std::vector<std::string> functions = { "conj","exp","log","sqrt", "pow", "complex" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;
}

void cout_value(const std::string& name) {
	if (!exist_name_in_map(name)) {
		throw std::string("Error: this name does not exist!");
	}
	if (map[name].index() == 0) {
		std::cout << std::endl << " " << std::get<linear::complex>(map[name]) << std::endl;
	}
	else if (map[name].index() == 1) {
		std::cout << std::endl << " " << std::get<linear::vector>(map[name]) << std::endl;
	}
	else if (map[name].index() == 2) {
		std::cout << std::endl << " " << std::get<matrix>(map[name]) << std::endl;
	}
	else if (map[name].index() == 3) {
		std::cout << std::endl << " " << std::get<double>(map[name]) << std::endl;
	}
}

void cout_expression(const std::variant<linear::complex, linear::vector, matrix, double>& value) {
	if (value.index() == 0) {
		std::cout << std::endl << " " << std::get<linear::complex>(value) << std::endl;
	}
	else if (value.index() == 1) {
		std::cout << std::endl << " " << std::get<linear::vector>(value) << std::endl;
	}
	else if (value.index() == 2) {
		std::cout << std::endl << " " << std::get<matrix>(value) << std::endl;
	}
	else if (value.index() == 3) {
		std::cout << std::endl << " " << std::get<double>(value) << std::endl;
	}
}

bool check_enter(const std::string& user_enter) {
	if (user_enter == "exit") {
		return true;
	}
	else if (user_enter == "help") {

	}

}

void check_error(std::string& user_enter) {
	size_t equality_count = number_of_substring_in_string(user_enter, "=");
	if (equality_count > 1) {
		throw std::string("Error: too many assignments!");
	}
	std::string expression = user_enter;
	if (equality_count == 1) {//оператор равно.
		std::string before;
		delete_space_before(user_enter, '=');
		split(user_enter, before, expression);
		if(!valid_name(before))
			throw std::string("Error: incorrect name!");
	}
	else {

		//
	}
	std::string function = function_name(expression);
	if (function != "none") {
		auto left = expression.find('(');
		auto right = expression.find_last_of(')');
		if (left == std::string::npos || right == std::string::npos)
			throw std::string("Error: wrong syntax!");
		if ((left != function.size() + number_of_space(expression, 0, left)) || right != expression.size() - number_of_space(expression, right, expression.size()) - 1) {
			throw std::string("Error: wrong syntax!");
		}
		auto coma_count = number_of_substring_in_string(expression, ",");
		if (coma_count > 1) {
			throw std::string("Error: too many comas!");
		}
		else if (coma_count == 0) {
			if (function == "complex" || function == "pow")
				throw std::string("Error: few parametres in function " + function);
		}
	}
}

void parser(std::string& user_enter, std::string& function, std::string& name, std::string& expression, bool& equality) {
	check_error(user_enter);
	function = function_name(user_enter);
	size_t equality_count = number_of_substring_in_string(user_enter, "=");
	std::string before;
	auto vector = split(user_enter, "=");
	if (equality_count == 1) { //есть присваивание
		name = vector[0];
		expression = vector[1];
		equality = true;
	}
	else {
		if (function == "none") {
			name = '\0';
			expression = vector[0];
		}
		else {
			expression = vector[0];
		}
		equality = false;
	}
}

linear::vector vector_help(std::string& left) {
	auto vector_of_value = split(left, " ");
	linear::vector vector(0);
	try {
		for (auto& str : vector_of_value) {
			if (!exist_name_in_map(str) && valid_scalar(str)) {
				vector.push_back(std::stod(str));
			}
			else if (exist_name_in_map(str)) {
				vector.push_back(std::get<double>(map[str]));
			}
			else {
				throw;
			}

		}
	}
	catch (...) {
		throw std::string("Error: incorrect expression!");
	}
	return vector;
}

std::variant < linear::complex, linear::vector, matrix, double> execute_function(std::string& expression, const std::string& function_name, const bool function) {
	if (function) {
		expression.erase(expression.find('('), 1);
		expression.erase(expression.find_last_of(')'), 1);
		expression = replace_in_string(expression, std::regex('(' + function_name + ')' + '+'), "");

		if (create_complex(function_name, expression)) {
			auto vector = split(expression, ",");
			std::string left = vector[0], right = "none";
			linear::complex z;
			if (function_name == "pow") {
				right = vector[1];
				auto vec = split(expression, ",");
				double pow = std::get<double>(zamelsonand_bauer(left));
				z = std::get<linear::complex>(zamelsonand_bauer(right));
				return linear::pow(pow, z);
			}
			if (function_name == "complex") {
				right = vector[1];
				z.real(std::get<double>(zamelsonand_bauer(left)));
				z.imag(std::get<double>(zamelsonand_bauer(right)));
				return z;

			}
			if (right != "none") {
				throw std::string("Error: too many parameters in function!");
			}
			z = std::get<linear::complex>(map[left]);
			if (function_name == "conj") {
				auto value = linear::conj(z);
				return value;
			}
			else if (function_name == "exp") {
				auto value = linear::exp(z);
				return value;
			}
			else if (function_name == "log") {
				auto value = linear::log(z);
				return value;
			}
			else if (function_name == "sqrt") {
				auto value = linear::sqrt(z);
				return value;
			}
		}
		else if (create_double(expression, function_name)) {
			auto vector = split(expression, ",");
			if (function_name == "none") {
				auto value = std::stod(vector[0]);
				return value;
			}
			else if (function_name == "abs") {
				auto value = linear::abs(std::get<linear::complex>(zamelsonand_bauer(vector[0])));
				return value;
			}
			else if (function_name == "arg") {
				auto value = linear::arg(std::get<linear::complex>(zamelsonand_bauer(vector[0])));
				return value;
			}
		}
		else if (create_vector(expression, function_name)) {
			if (number_of_substring_in_string(expression, ",") > 0)
				throw std::string("Error: must no coma in vector declaration!");
			auto vector = split(expression, ",");
			auto value = vector_help(vector[0]);
			return value;


		}
	}
	auto value = zamelsonand_bauer(expression);
	cout_expression(value);
	return value;

}

void new_cycle() {
	while (true) {
		try {
			std::string user_enter;
			while (user_enter.size() == 0) {

				std::cout << ">> ";
				std::getline(std::cin, user_enter);
			}
			if (check_enter(user_enter))
				break;
			bool equality = false;
			std::string function, expression;
			std::string name;
			parser(user_enter, function, name, expression, equality);
			if (equality) {
				auto value = function == "none" ? execute_function(expression, function, false) : execute_function(expression, function, true);
				map[name] = value;
				cout_value(name);
			}
			else {
				if (function != "none") {
					cout_expression(execute_function(expression, function, true));
					
					continue;
				}
				if (!exist_name_in_map(name)) {
					cout_expression(execute_function(expression, function, false));
					continue;
				}
				else
					cout_value(name);
			}
		}

		catch (std::string& error) {
			std::cout << std::endl << error << std::endl;
		}
	
	}
}

//user_enter - все, что ввел пользователь
//function - название функции
//expression - выражение после названия функции в скобках или весь ввод слева.

int main()
{
	/*
		TODO: СДЕЛАТЬ ОБЩИЙ ДЛЯ complex, vector, matrix НУЛЕВОЙ ЭЛЕМЕНТ!!!!!!и заменить в строке e.push(0);
	*/
	new_cycle();
	return 0;
}
