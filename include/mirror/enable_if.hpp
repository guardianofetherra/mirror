/**
 * @file mirror/enable_if.hpp
 * @brief Compile-time enable-if operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_ENABLE_IF_1105240825_HPP
#define MIRROR_ENABLE_IF_1105240825_HPP

#include <type_traits>
#include "int_const.hpp"
#include "or.hpp"

namespace mirror {

template <typename ... Bool>
using enable_if_any = typename std::enable_if<or_<Bool...>::value>::type;

} // namespace mirror

#endif //include guard

