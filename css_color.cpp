#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
#define TYPE_DEMANGLE(x) (abi::__cxa_demangle(x,0,0,0))
#else
#define TYPE_DEMANGLE(x) (x)
#endif

struct css_color_real_number { using type = float; };
#include "css_color.hpp"	//include the all-in-one header file.

int main() {
	std::cout << "using " << TYPE_DEMANGLE(typeid(css_colors::details::real(0)).name()) << " as real number" << std::endl;
	css_colors::color c;
	char line[256];
	std::cin.getline(line, 256);
	c = css_colors::parse(line);
	std::cout << std::hex << c << std::dec << std::endl;


	
	std::cin >> c;
	std::cout << css_colors::clamp(c.as<css_colors::colorspaces::oklab>()) << std::endl;
	
	constexpr auto const_color = css_colors::parse("brown");
	std::cout << const_color << std::endl;
}