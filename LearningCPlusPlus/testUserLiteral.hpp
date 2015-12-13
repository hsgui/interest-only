#pragma once

#include <iostream>
#include <string>
#include <type_traits>

namespace LearningCPP
{
    // http://en.cppreference.com/w/cpp/language/user_literal
    namespace UserLiteral
    {
        // there are no negative integer literals.
        // the paraemters to operator literal is restricted:
        // 1. char const*
        // 2. unsigned long long
        // 3. long double
        // 4. char chonst*, std::size_t
        // 5. wchar_t const*, std::size_t
        // 6. char16_t const*, std::size_t
        // 7. char32_t const*, std::size_t
        constexpr unsigned long long operator "" _ULL(unsigned long long p)
        {
            return p;
        }

        constexpr long long operator "" _LL(const char* p)
        {
            return 0;
        }

        constexpr int operator "" _I(const char* p)
        {
            return 0;
        }

        constexpr long double operator "" _LD(long double p)
        {
            return 0;
        }

        constexpr double operator "" _D(const char* p)
        {
            return 0;
        }

        std::string operator "" _SS(const char* p, const size_t len)
        {
            return "";
        }

        // side effect.
        void operator"" _print(const char* str)
        {
            std::cout << str << std::endl;
        }

        template <char... digits>
        constexpr std::integer_sequence<char, digits...> operator "" _raw()
        {
            return std::integer_sequence<char, digits...>{};
        }

        template<char c>
        constexpr unsigned digitToValue(std::integral_constant<char, c>);

        template<char c>
        constexpr unsigned digitToValue(std::integral_constant<char, c>)
        {
            static_assert(c >= '0' && c <= '9', "c must between '0'-'9'");
            return digitToValue(std::integral_constant<char, c-1>()) + 1;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, '0'>)
        {
            return 0;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 0>)
        {
            return 0;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'a'>)
        {
            return 10;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'b'>)
        {
            return 11;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'c'>)
        {
            return 12;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'd'>)
        {
            return 13;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'e'>)
        {
            return 14;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'f'>)
        {
            return 15;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'A'>)
        {
            return 10;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'B'>)
        {
            return 11;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'C'>)
        {
            return 12;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'D'>)
        {
            return 13;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'E'>)
        {
            return 14;
        }
        template<>
        constexpr unsigned digitToValue(std::integral_constant<char, 'F'>)
        {
            return 15;
        }

        template<char c> struct DigitToValue;

        template<char c>
        struct DigitToValue
        {
            static constexpr unsigned value = DigitToValue<c-1>::value + 1;
        };

        template<>
        struct DigitToValue<'0'>
        {
            static constexpr unsigned value = 0;
        };
        template<>
        struct DigitToValue<'a'>
        {
            static constexpr unsigned value = 10;
        };
        template<>
        struct DigitToValue<'A'>
        {
            static constexpr unsigned value = 10;
        };
        template<>
        struct DigitToValue<'b'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'B'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'c'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'C'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'d'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'D'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'e'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'E'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'f'>
        {
            static constexpr unsigned value = 11;
        };
        template<>
        struct DigitToValue<'F'>
        {
            static constexpr unsigned value = 11;
        };

        template<typename sum, char... digits>
        struct GetDigits
        {
            using type = sum;
        };

        template<unsigned... partial,  char... xs>
        struct GetDigits<std::integer_sequence<unsigned, partial...>, '\'', xs...>
            : GetDigits<std::integer_sequence<unsigned, partial...>, 
                        xs...>
        {};

        // TODO replace DigitToValue<x>::value to digitToValue(std::integral_constant<char, x>()) won't compile
        //  -- no appropriate default constructor!
        template<unsigned... partial, char x, char... xs>
        struct GetDigits<std::integer_sequence<unsigned, partial...>, x, xs...>
            : GetDigits<std::integer_sequence<unsigned, partial..., DigitToValue<x>::value>,
                        xs...>
        {};

        template<unsigned b, char... d>
        struct BaseAndDigits
        {
            static constexpr unsigned base = b;
            using digits = typename GetDigits<
                std::integer_sequence<unsigned>,
                d...>::type;
        };

        template<char... digits>
        struct ParseNumber : BaseAndDigits<10, digits...> {};

        template<char... digits>
        struct ParseNumber<'0', 'X', digits...> : BaseAndDigits<16, digits...> {};

        template<char... digits>
        struct ParseNumber<'0', 'x', digits...> : BaseAndDigits<16, digits...> {};

        template<char... digits>
        struct ParseNumber<'0', digits...> : BaseAndDigits<8, digits...> {};

        template<char... digits>
        struct ParseNumber<'0', 'b', digits...> : BaseAndDigits<2, digits...> {};

        template<char... digits>
        struct ParseNumber<'0', 'B', digits...> : BaseAndDigits<2, digits...> {};

        template<typename T, 
            char... digits>
        struct ConstantFromString
        {
            using Number = ParseNumber<digits...>;
            using Digits = typename Number::digits;
            static constexpr unsigned base = Number::base;

            template<unsigned x, unsigned... xs>
            static constexpr unsigned long long fold(unsigned long long sum, std::integer_sequence<unsigned, x, xs...>)
            {
                return fold(x + base * sum, std::integer_sequence<unsigned, xs...>());
            }

            static constexpr unsigned long long fold(unsigned long long sum, std::integer_sequence<unsigned>)
            {
                return sum;
            }

            template<T partial, typename S, S... xs> struct Folder;

            template<T partial, typename S>
            struct Folder<partial, std::integer_sequence<S>>
            {
                static constexpr T sum = partial;
            };

            template<T partial, typename S, S x, S... xs>
            struct Folder<partial, std::integer_sequence<S, x, xs...>>
            {
                static constexpr T sum = Folder<static_cast<T>(partial * base + x), std::integer_sequence<S, xs...>>::sum;
            };

            // TODO figure out why can't replace with:
            // std::integral_constant<T, static_cast<T>(fold(0, Digits{}))>;
            using value = std::integral_constant< T, static_cast<T>(Folder<0, Digits>::sum)>;
        };

        template<int8_t x>
        using byte = std::integral_constant<int8_t, x>;

        template<char... digits>
        constexpr typename byte<0>::value_type operator "" _byte()
        {
            return typename ConstantFromString<typename byte<0>::value_type, digits...>::value();
        }

        void testLiteralOperator()
        {
            std::cout << "45_ULL=" << 45_ULL << std::endl;
            std::cout << "33_LL=" << 33_LL << std::endl;
            std::cout << "22_D=" << 22_D << std::endl;
            std::cout << "23_LD=" << 23.3_LD << std::endl;
            0x123ABC_print;

            std::cout << "std::is_same<decltype(123_raw), std::integer_sequence<char, '7', '6', '2'>>="
                << std::is_same<decltype(123_raw), std::integer_sequence<char, '1', '2', '3'>>::value << std::endl;
            std::cout << "digitToValue(std::integral_constant<char, 'a'>())=" << digitToValue(std::integral_constant<char, 'a'>()) << std::endl;
            std::cout << std::is_same < typename GetDigits<std::integer_sequence<unsigned>, '1', '2', '3'>::type,
                std::integer_sequence<unsigned, 1, 2, 3 >> ::value << std::endl;

            std::cout << std::is_same<typename ParseNumber<'1', '2', '3'>::digits,
                std::integer_sequence<unsigned, 1, 2, 3 >> ::value << std::endl;

            std::cout << std::is_same<typename ConstantFromString<unsigned, '1', '2', '3'>::Digits,
                std::integer_sequence<unsigned, 1, 2, 3 >> ::value << std::endl;

            std::cout << ConstantFromString<unsigned, '1', '2', '3'>::value::value << std::endl;
            std::cout << std::is_same<typename ConstantFromString<unsigned, '1', '2', '3'>::value,
                std::integral_constant<unsigned, 123 >> ::value << std::endl;

            std::cout << 8 * 0x20_byte << std::endl;
        }

        // this is very much like Haskell and 
        // pattern matching on values themselves instead of just on their types.
        template<typename T, 
            T x, 
            typename = std::enable_if_t<x != 0>>
            constexpr T sumN(std::integral_constant<T, x>)
        {
            return x + sumN(std::integral_constant<T, x-1>());
        }

        template<typename T>
        constexpr T sumN(std::integral_constant<T, 0>)
        {
            return 0;
        }

        // http://en.cppreference.com/w/cpp/types/integral_constant
        void testIntegralConstant()
        {
            typedef std::integral_constant<int, 2> two_t;
            typedef std::integral_constant<int, 4> four_t;

            static_assert(two_t::value * 2 == four_t::value, "2*2 != 4");

            enum class my_e
            {
                e1,
                e2
            };

            typedef std::integral_constant<my_e, my_e::e1> my_e1;
            typedef std::integral_constant<my_e, my_e::e2> my_e2;

            static_assert(my_e1::value != my_e2::value, "my_e1 == my_e2");

            std::cout << "sumN(std::integral_constant<int, 4>())=" << sumN(std::integral_constant<int, 4>()) << std::endl;
        }

        void test()
        {
            testLiteralOperator();
            testIntegralConstant();
        }
    }
}