/**
 * @file mirror/get_size.hpp
 * @brief Implementation of the `get_size` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_SIZE_1105240825_HPP
#define MIRROR_GET_SIZE_1105240825_HPP

#include "integers.hpp"
#include "range.hpp"
#include "string.hpp"
#include "optional.hpp"
#include "metaobjects.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_size;

template <typename T>
struct op_get_size<optional<T>>
 : unsigned_<1u>
{ };

template <>
struct op_get_size<optional<none>>
 : unsigned_<0u>
{ };

template <typename ... P>
struct op_get_size<range<P...>>
 : unsigned_<sizeof ... (P)>
{ };

template <typename Char, Char ... C>
struct op_get_size<basic_string<Char, C...>>
 : unsigned_<sizeof ... (C)>
{ };

template <typename MO>
struct op_get_size<meta_object<MO>>
 : unsigned_<std::meta::get_size_v<MO>>
{ };

} // namespace _aux

template <typename X>
using get_size = eval<_aux::op_get_size<X>>;

} // namespace mirror

#endif //include guard
