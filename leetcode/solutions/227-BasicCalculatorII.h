#include <algorithm>
#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <sstream>
#include <cstdlib>

using namespace std;

// https://leetcode.com/problems/basic-calculator-ii/
// http://scriptasylum.com/tutorials/infix_postfix/algorithms/infix-postfix/
// http://scriptasylum.com/tutorials/infix_postfix/algorithms/postfix-evaluation/
class BasicCalculatorII
{
public:
	struct Element
	{
		int value;
		bool isSymbol;
	};

	int getPrecedence(char op)
	{
		int precedence;
		switch (op)
		{
		case '+':
		case '-':
			precedence = 1;
			break;
		case '*':
		case '/':
			precedence = 2;
			break;
		default:
			precedence = 0;
			break;
		}
		return precedence;
	}

	int calculate(char ch, int firstOperand, int secondOperand)
	{
		switch (ch)
		{
		case '+':
			return firstOperand + secondOperand;
		case '-':
			return firstOperand - secondOperand;
		case '*':
			return firstOperand * secondOperand;
		case '/':
			return firstOperand / secondOperand;
		default:
			return -1;
		}
	}

	void infixToPostfix(string& infix, vector<Element>& postfix)
	{
		vector<char> operators;
		for (const char *ch = infix.c_str(); *ch; ch++){
			switch (*ch)
			{
			case ' ':
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				if (operators.size() == 0)
				{
					operators.push_back(*ch);
				}
				else
				{
					while (!operators.empty())
					{
						char top = operators.back();
						if (getPrecedence(top) >= getPrecedence(*ch))
						{
							operators.pop_back();
							Element e = { top, true };
							postfix.push_back(e);
						}
						else
						{
							break;
						}
					}
					operators.push_back(*ch);
				}
				break;
			default:
				char *end;
				int n = strtol(ch, &end, 10);
				Element e = { n, false };
				postfix.push_back(e);
				ch = end - 1;
				break;
			}
		}
		while (!operators.empty())
		{
			char ch = operators.back();
			Element e = { ch, true };
			postfix.push_back(e);
			operators.pop_back();
		}
	}

	int calculate(string s)
	{
		vector<Element> postfix;

		infixToPostfix(s, postfix);

		vector<int> operands;
		for (int i = 0; i < postfix.size(); ++i)
		{
			Element e = postfix[i];
			if (!e.isSymbol)
			{
				operands.push_back(e.value);
			}
			else
			{
				int secondOperand = operands.back();
				operands.pop_back();
				int firstOperand = operands.back();
				operands.pop_back();
				operands.push_back(calculate(e.value, firstOperand, secondOperand));
			}
		}

		assert(operands.size() == 1);
		return operands.back();
	}

	bool Test()
	{
		string s = "3+2*2";
		assert(calculate(s) == 7);

		s = " 3/2 ";
		assert(calculate(s) == 1);

		s = " 3+5 / 2 ";
		assert(calculate(s) == 5);
		return true;
	}
};