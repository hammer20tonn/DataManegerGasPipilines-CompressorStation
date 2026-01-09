#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
//#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl
#define INPUT_LINE(in, str) getline(in>>std::ws, str);

#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};



template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()
		|| std::cin.peek() != '\n'
		|| x < min || x > max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type number (" << min << "-" << max << "):";
	}
	//std::cerr << x << std::endl;
	return x;
}






template <typename T>
T GetCorrectNumberAllowed(const std::vector<T>& allowed_values) {
	T x;

	while ((std::cin >> x).fail() || std::cin.peek() != '\n' ||
		std::find(allowed_values.begin(), allowed_values.end(), x) == allowed_values.end()) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Type one of: ";
		for (const auto& val : allowed_values) {
			std::cout << val << " ";
		}
		std::cout << ": ";
	}
	return x;
}