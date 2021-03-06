/**
 * @example mirror/010_print_member_types.cpp
 * @brief Shows how to print out class member types
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/for_each.hpp>
#include <mirror/get_aliased.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_full_name.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_public_member_types.hpp>
#include <mirror/traits.hpp>
#include <mirror/c_str.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>
#include <mirror/range.hpp>
#include <mirror/unpack.hpp>
#include <iostream>

struct S {
	struct a { };
	typedef int b;
	using c = char;
};

class C {
private:
	struct _x { };
protected:
	typedef const _x _y;
public:
	using z = _y*;
};

namespace {

using namespace mirror;

template <typename T>
class print_member_types
{
private:
	struct _printer {
		std::ostream& out;

		template <typename MO>
		void operator()(MO) const
		{
			out << c_str<get_base_name<MO>>;
			if(value<reflects_alias<MO>>)
			{
				out << " -> ";
				out << c_str<get_full_name<get_aliased<MO>>>;
			}
			out << std::endl;
		}
	};
public:
	std::ostream& operator()(std::ostream& out, bool all) const
	{
		_printer print{out};

		using MT = MIRRORED(T);

		if(all) {
			for_each<get_member_types<MT>>::apply(print);
		} else {
			for_each<get_public_member_types<MT>>::apply(print);
		}
		return out;
	}
};

} // namespace

void print_S(void)
{
	print_member_types<S> pdm;

	pdm(std::cout, true) << std::endl;
	pdm(std::cout,false) << std::endl;
}

void print_C(void)
{
	print_member_types<C> pdm;

	pdm(std::cout, true) << std::endl;
	pdm(std::cout,false) << std::endl;
}

int main(void)
{
	print_S();
	print_C();

	return 0;
}
