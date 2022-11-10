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
#ifndef LIBBITCOIN_DATABASE_PRIMITIVES_ARRAYMAP_IPP
#define LIBBITCOIN_DATABASE_PRIMITIVES_ARRAYMAP_IPP

#include <bitcoin/system.hpp>
#include <bitcoin/database/define.hpp>

namespace libbitcoin {
namespace database {
    
TEMPLATE
CLASS::arraymap(storage& body) NOEXCEPT
  : body_(body)
{
}

// query interface
// ----------------------------------------------------------------------------

TEMPLATE
Record CLASS::get(const Link& link) const NOEXCEPT
{
    return { at(link) };
}

TEMPLATE
bool CLASS::insert(const Record& record) NOEXCEPT
{
    // record.size() is slab/byte or record allocation.
    return record.to_data(push(record.size()));
}

// protected
// ----------------------------------------------------------------------------

TEMPLATE
reader_ptr CLASS::at(const Link& link) const NOEXCEPT
{
    if (link.is_terminal())
        return {};

    const auto ptr = body_.get(link_to_position(link));
    if (!ptr)
        return {};

    const auto source = std::make_shared<reader>(ptr);
    if constexpr (!is_slab) { source->set_limit(Record::size); }
    return source;
}

TEMPLATE
writer_ptr CLASS::push(const Link& size) NOEXCEPT
{
    using namespace system;
    BC_ASSERT(!size.is_terminal());
    BC_ASSERT(!is_multiply_overflow<size_t>(size, Record::size));

    const auto item = body_.allocate(link_to_position(size));
    if (item == storage::eof)
        return {};

    const auto ptr = body_.get(item);
    if (!ptr)
        return {};

    const auto sink = std::make_shared<writer>(ptr);
    if constexpr (is_slab) { sink->set_limit(size); }
    if constexpr (!is_slab) { sink->set_limit(size * Record::size); }
    return sink;
}

// private
// ----------------------------------------------------------------------------

TEMPLATE
constexpr size_t CLASS::link_to_position(const Link& link) NOEXCEPT
{
    using namespace system;
    const auto value = possible_narrow_cast<size_t>(link.value);

    // Iterator keys off of zero Size...
    if constexpr (is_slab)
    {
        return value;
    }
    else
    {
        // ... and there are no links or keys.
        constexpr auto element_size = Record::size;
        BC_ASSERT(!is_multiply_overflow(value, element_size));
        return value * element_size;
    }
}

} // namespace database
} // namespace libbitcoin

#endif
