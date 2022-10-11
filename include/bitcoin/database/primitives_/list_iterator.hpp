/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_DATABASE_PRIMITIVES__LIST_ITERATOR_HPP
#define LIBBITCOIN_DATABASE_PRIMITIVES__LIST_ITERATOR_HPP

#include <bitcoin/system.hpp>
#include <bitcoin/database/define.hpp>
#include <bitcoin/database/primitives_/list_element.hpp>

namespace libbitcoin {
namespace database {

/// Const iterator for list_element.
/// Manager dynamically traverses store-based list.
/// Mutex provides read safety for link traversal during unlink.
template <typename Manager, typename Link, typename Key,
    if_unsigned_integer<Link> = true,
    if_integral_array<Key> = true>
class list_iterator
{
public:
    // std::iterator_traits
    using iterator_category = std::output_iterator_tag;
    using value_type = list_element<Manager, Link, Key>;
    using difference_type = ptrdiff_t;
    using pointer = const value_type&;
    using reference = const value_type&;

    /// Create a storage iterator starting at the given element.
    list_iterator(const value_type& element) NOEXCEPT;

    /// Create a storage iterator starting at first.
    list_iterator(Manager& manager, Link first,
        shared_mutex& mutex) NOEXCEPT;

    /// Operators.
    pointer operator*() const NOEXCEPT;
    reference operator->() const NOEXCEPT;
    list_iterator& operator++() NOEXCEPT;
    list_iterator operator++(int) NOEXCEPT;
    bool operator==(const list_iterator& other) const NOEXCEPT;
    bool operator!=(const list_iterator& other) const NOEXCEPT;

private:
    value_type element_;
};

} // namespace database
} // namespace libbitcoin

#define TEMPLATE \
template <typename Manager, typename Link, typename Key,\
if_unsigned_integer<Link> If1, if_integral_array<Key> If2>
#define CLASS list_iterator<Manager, Link, Key, If1, If2>

#include <bitcoin/database/impl/primitives_/list_iterator.ipp>

#undef CLASS
#undef TEMPLATE

#endif
