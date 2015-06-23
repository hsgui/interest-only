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
		operands.clear();
		operators.clear();

		for (int i = 0; i < s.size(); ++i)
		{
			char ch = s[i];
			if (ch == '(' || ch == '-' || ch == '+')
			{
				operators.push_back(ch);
			}
			else if (ch == ' ')
			{
			}
			else if (ch == ')')
			{
				operators.pop_back();
				if (!operands.empty())
				{
					int secondOperand = operands.back();
					if (!operators.empty())
					{
						char op = operators.back();
						if (op == '+')
						{
							operands.pop_back();
							int firstOperand = operands.back();
							operands.pop_back();
							operands.push_back(firstOperand + secondOperand);
							operators.pop_back();
						}
						else if (op == '-')
						{
							operands.pop_back();
							int firstOperand = operands.back();
							operands.pop_back();
							operands.push_back(firstOperand - secondOperand);
							operators.pop_back();
						}
					}
				}
			}
			else if (ch <= '9' && ch >= '0')
			{
				int number = ch - '0';
				// no number in the operands currently
				if (operands.empty())
				{
					// check the top operator if exist
					if (!operators.empty())
					{
						char op = operators.back();
						if (op == '+')
						{
							operators.pop_back();
							operands.push_back(number);
						}
						else if (op == '-')
						{
							operators.pop_back();
							operands.push_back(-number);
						}
						else
						{
							operands.push_back(number);
						}
					}
					else
					{
						operands.push_back(number);
					}
				}
				else
				{
					assert(!operators.empty());
					char op = operators.back();
					if (op == '+')
					{
						int firstOperand = operands.back();
						operands.pop_back();
						operands.push_back(firstOperand + number);
						operators.pop_back();
					}
					else if (op == '-')
					{
						int firstOperand = operands.back();
						operands.pop_back();
						operands.push_back(firstOperand - number);
						operators.pop_back();
					}
					else
					{
						operands.push_back(number);
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

		s = "(((-1)))";
		assert(calculate(s) == -1);

		s = "((( -2 + 3)) + (-1))";
		assert(calculate(s) == 0);

		return true;
	}

private:
	vector<int> operands;
	vector<char> operators;
};
