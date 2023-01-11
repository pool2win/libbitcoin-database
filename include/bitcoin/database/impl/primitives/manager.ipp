/**
 * Copyright (c) 2011-2022 libbitcoin developers (see AUTHORS)
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
#ifndef LIBBITCOIN_DATABASE_PRIMITIVES_MANAGER_IPP
#define LIBBITCOIN_DATABASE_PRIMITIVES_MANAGER_IPP

#include <bitcoin/system.hpp>
#include <bitcoin/database/define.hpp>

namespace libbitcoin {
namespace database {
    
TEMPLATE
CLASS::manager(storage& file) NOEXCEPT
  : file_(file)
{
}

TEMPLATE
Link CLASS::count() const NOEXCEPT
{
    return position_to_link(file_.size());
}

TEMPLATE
bool CLASS::truncate(const Link& count) NOEXCEPT
{
    if (count.is_terminal())
        return false;

    return file_.truncate(link_to_position(count));
}

TEMPLATE
Link CLASS::allocate(const Link& size) NOEXCEPT
{
    if (size.is_terminal())
        return size;

    const auto start = file_.allocate(link_to_position(size));

    if (start == storage::eof)
        return Link::terminal;

    return position_to_link(start);
}

TEMPLATE
memory_ptr CLASS::get() const NOEXCEPT
{
    return file_.get();
}

TEMPLATE
memory_ptr CLASS::get(const Link& value) const NOEXCEPT
{
    if (value.is_terminal())
        return nullptr;

    // memory.size() may be negative (stream treats as exhausted).
    return file_.get(link_to_position(value));
}

// private
// ----------------------------------------------------------------------------

TEMPLATE
constexpr size_t CLASS::link_to_position(const Link& link) NOEXCEPT
{
    using namespace system;
    const auto value = possible_narrow_cast<size_t>(link.value);

    if constexpr (is_slab)
    {
        // Slab implies link/key incorporated into size.
        return value;
    }
    else if constexpr (!is_zero(array_count<Key>))
    {
        // Record implies link/key independent of Size.
        constexpr auto element_size = Link::size + array_count<Key> + Size;
        BC_ASSERT(!is_multiply_overflow(value, element_size));
        return value * element_size;
    }
    else
    {
        // No key implies no linked list.
        BC_ASSERT(!is_multiply_overflow(value, Size));
        return value * Size;
    }
}

TEMPLATE
constexpr Link CLASS::position_to_link(size_t position) NOEXCEPT
{
    using namespace system;
    using integer = typename Link::integer;

    if constexpr (is_slab)
    {
        // Slab implies link/key incorporated into size.
        return { possible_narrow_cast<integer>(position) };
    }
    else if constexpr (!is_zero(array_count<Key>))
    {
        // Record implies link/key independent of Size.
        constexpr auto element_size = Link::size + array_count<Key> + Size;
        return { possible_narrow_cast<integer>(position / element_size) };
    }
    else
    {
        // No key implies no linked list.
        static_assert(!is_zero(Size));
        return { possible_narrow_cast<integer>(position / Size) };
    }
}

} // namespace database
} // namespace libbitcoin

#endif