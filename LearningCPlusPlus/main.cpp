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
#include "variadicTemplatesTest.hpp"
#include "smartPointersTest.hpp"
#include "quickTest.hpp"
#include "testlambda.hpp"
#include "testemplace.hpp"
#include "testConcurrency.hpp"
#include "testUserLiteral.hpp"

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

    LearningCPP::VariadicTemplate::test();

    LearningCPP::SmartPointers::test();

    LearningCPP::Lambda::test();

    LearningCPP::EmplaceBack::test();

    LearningCPP::Concurrency::test();

    LearningCPP::UserLiteral::test();

    LearningCPP::QuickTest::test();

    system("pause");

    return 0;
}