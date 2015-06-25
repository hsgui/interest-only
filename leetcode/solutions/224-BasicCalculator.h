#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>

using namespace std;

// https://leetcode.com/problems/basic-calculator/
class BasicCalculator
{
public:
	int calculate(string s)
	{
		vector<int> operands;

		for (int i = 0; i < s.size(); ++i)
		{
			char ch = s[i];
			if (ch == '(' || ch == '-' || ch == '+')
			{
				operands.push_back(ch);
			}
			else if (ch == ' ')
			{
			}
			else if (ch == ')')
			{
				// top must be a number
				int secondOperand = operands.back();
				operands.pop_back();
				assert(operands.size() > 0);
				// top must be (, 
				operands.pop_back();
				if (operands.size() > 0)
				{
					// back must be (, +, or -, or nothing
					if (operands.size() == 0 || operands.back() == '(')
					{
						operands.push_back(secondOperand);
					}
					else
					{
						// back must be + or -
						if (operands.back() == '-')
						{
							secondOperand = 0 - secondOperand;
						}
						operands.pop_back();

						// back must be ( or nothing, or number
						if (operands.size() == 0 || operands.back() == '(')
						{
							operands.push_back(secondOperand);
						}
						else
						{
							int firstOperand = operands.back();
							operands.pop_back();
							operands.push_back(firstOperand + secondOperand);
						}
					}
				}
				else
				{
					operands.push_back(secondOperand);
				}
			}
			else if (ch <= '9' && ch >= '0')
			{
				int number = 0;
				while (i < s.size() && s[i] >= '0' && s[i] <= '9')
				{
					number = number * 10 + s[i] - '0';
					i++;
				}
				i--;
				// top must be (, nothing, +, -
				if (operands.size() == 0 || operands.back() == '(')
				{
					operands.push_back(number);
				}
				else
				{
					// top must be +, or -
					if (operands.back() == '-')
					{
						number = 0 - number;
					}
					operands.pop_back();

					// top must be (, nothing, or number
					if (operands.size() == 0 || operands.back() == '(')
					{
						operands.push_back(number);
					}
					else
					{
						int firstOperand = operands.back();
						operands.pop_back();
						operands.push_back(firstOperand + number);
					}
				}
			}
		}
		assert(operands.size() == 1);
		return operands.back();
	}

	bool Test()
	{
		string s = "(1+(4+5+2)-3)+(6+8)";
		assert(calculate(s) == 23);

		s = " - 1-(((-1)))";
		assert(calculate(s) == 0);

		s = "((( -2 + 3)) + (-1))";
		assert(calculate(s) == 0);

		s = "1 - ( 2 - ((-3)))";
		assert(calculate(s) == -4);

		s = "-3 + 2";
		assert(calculate(s) == -1);

		s = "1-(2+3-(4+(5-(1-(2+4-(5+6))))))";
		assert(calculate(s) == -1);

		s = "-(2)";
		assert(calculate(s) == -2);

		s = "(-(2))";
		assert(calculate(s) == -2);

		s = "-((4) - ((5))) + (((7)))";
		assert(calculate(s) == 8);
		return true;
	}
};
