/**
 * @file puddle/meta_constant_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_META_CONSTANT_OPS_1105240825_HPP
#define PUDDLE_META_CONSTANT_OPS_1105240825_HPP

#include <mirror/get_constant.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_constant(X)
noexcept
{
	return mirror::get_constant<X>{};
}

} // namespace puddle

#endif //include guard

