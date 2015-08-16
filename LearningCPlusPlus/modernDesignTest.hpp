#pragma once

#include "modernDesign.hpp"
#include <iostream>
#include <vector>

namespace ModernDesign {
	void testConversion()
	{
		std::cout << "SUPERSUBCLASS(int, float): " 
			<< SUPERSUBCLASS(int, float) << std::endl;
		std::cout << "SUPERSUBCLASS(int, char): "
			<< SUPERSUBCLASS(int, char) << std::endl;
		std::cout << "SUPERSUBCLASS(float, int): "
			<< SUPERSUBCLASS(float, int) << std::endl;
		std::cout << "SUPERSUBCLASS(int, unsigned int): " 
			<< SUPERSUBCLASS(int, unsigned int) << std::endl;
		std::cout << "SUPERSUBCLASS(int, int): "
			<< SUPERSUBCLASS(int, int) << std::endl;
	}

	void testTypeTraits()
	{
		const bool iterIsPointer = TypeTraits<std::vector<int>::iterator>::isPointer;
		std::cout << "std::vector<int>::iterator is "
			<< (iterIsPointer ? "fast" : "smart") << std::endl;
	}
	void testModernDesign()
	{
		std::cout << std::endl
			<< "test conversion ..." << std::endl;
		testConversion();

		std::cout << std::endl
			<< "test type traits..." << std::endl;
		testTypeTraits();
	}
}