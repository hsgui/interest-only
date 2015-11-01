#include <iostream>
#include <string>

#include "max.hpp"
#include "factorial.hpp"
#include "bubbleSortTest.hpp"
#include "categoryTest.hpp"
#include "lrvalueTest.hpp"
#include "templatemetaTest.hpp"
#include "modernDesignTest.hpp"
#include "learningcppTest.hpp"

int main()
{
	int i = 42;
	std::cout << "max(7, i): " << TemplatePractice::max(7, i) << std::endl;

	double f1 = 3.4;
	double f2 = -6.7;
	std::cout << "max(f1, f2): " << TemplatePractice::max(f1, f2) << std::endl;

	std::string s1 = "mathematics";
	std::string s2 = "math";
	std::cout << "max(s1, s2): " << TemplatePractice::max(s1, s2) << std::endl;

	std::cout << TemplatePractice::Factorial<4>::value << std::endl;

	TemplatePractice::testBubbleSort();

	CategoryPractice::testFmap();

	C11Practice::testC11Practice();

	LearningCPP::testLearningCPP();

	TemplatePractice::testMetaTemplate();

	ModernDesign::testModernDesign();

	system("pause");

	return 0;
}