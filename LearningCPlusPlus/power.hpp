#pragma once

namespace LearningCPP
{
	// y = x^n;
	double ipower(double p_x, unsigned int p_n)
	{
		double y = 1.0;
		while (p_n != 0)
		{
			if ((p_n & 1) != 0) y *= p_x;
			p_x *= p_x;
			p_n >>= 1;
		}

		return y;
	}

	double xpower10(double p_x)
	{
		return ipower(p_x, 10);
	}

	// 10(decimal) = 1010(binary)
	// x^10 = x^8 * x^2
	// reorganize the ipower with p_n = 10;
	// how can we generate this function using ipower function (n is known at compile time) automatically (using compiler)?
	//	-- using template metaprogramming to eliminate the while loop and if statement
	// http://www.agner.org/optimize/optimizing_cpp.pdf
	double xpower10_rollout(double p_x)
	{
		double x2 = p_x * p_x;
		double x4 = x2 * x2;
		double x8 = x4 * x4;
		double x10 = x2 * x8;

		return x10;
	}

	// in C++ template metaprogramming, loops are implemented as recursive templates.
	// recursion must always end with a non-recursing template specialization, not with a branch inside the template.
	// Branches are implemented by (partial) template specialization.
	// PowerN is a class template rather than a function template because partial template specialization is allowed for classes.
	// remove right most 1 bit of N: N & (N - 1)
	// if N & (N-1) == 0, then N is a power of 2.
	// Template for power(x, N) where N is a positive integer constant.
	// General case, N is not a power of 2
	template<bool IsPowerOf2, int N>
	struct PowerN 
	{
	private:
		enum { N1 = N & (N - 1) };
	public:
		static double ipower(double p_x)
		{
			return PowerN<(N1 & (N1 - 1)) == 0, N1>::ipower(p_x) * PowerN<true, N - N1>::ipower(p_x);
		}
	};

	template<int N>
	struct PowerN<true, N>
	{
		static double ipower(double p_x)
		{
			return PowerN<true, N / 2>::ipower(p_x) * PowerN<true, N / 2>::ipower(p_x);
		}
	};

	template<>
	struct PowerN<true, 1>
	{
		static double ipower(double p_x)
		{
			return p_x;
		}
	};

	template<>
	struct PowerN<true, 0>
	{
		static double ipower(double)
		{
			return 1.0;
		}
	};

	template <int N>
	static inline double IntegerPower(double p_x)
	{
		return PowerN<(N & (N - 1)) == 0, N>::ipower(p_x);
	}
}