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
#ifndef LIBBITCOIN_DATABASE_TABLES_ARCHIVES_OUTPUT_HPP
#define LIBBITCOIN_DATABASE_TABLES_ARCHIVES_OUTPUT_HPP

#include <bitcoin/system.hpp>
#include <bitcoin/database/define.hpp>
#include <bitcoin/database/tables/schema.hpp>
#include <bitcoin/database/memory/memory.hpp>

namespace libbitcoin {
namespace database {
namespace output {

BC_PUSH_WARNING(NO_METHOD_HIDING)

// Input/output can both be obtained by pk and tx_fp by navigation from tx.

struct slab
{
    // Sizes.
    static constexpr size_t pk = schema::c::put;
    static constexpr size_t size = zero;
    linkage<pk> count() const NOEXCEPT
    {
        return
            variable_size(value) +
            schema::c::foreign_point +
            script.serialized_size(true);
    }

    // Fields.
    uint32_t transaction_fk;
    uint32_t index;
    uint64_t value;
    system::chain::script script;
    bool valid{ false };

    // Serialializers.

    inline slab from_data(reader& source) NOEXCEPT
    {
        transaction_fk = source.read_4_bytes_little_endian();
        index = source.read_3_bytes_little_endian();
        value = source.read_variable();
        script = system::chain::script(source, true);
        BC_ASSERT(source.get_position() == count());
        valid = source;
        return *this;
    }

    inline bool to_data(finalizer& sink) const NOEXCEPT
    {
        sink.write_4_bytes_little_endian(transaction_fk);
        sink.write_3_bytes_little_endian(index);
        sink.write_variable(value);
        script.to_data(sink, true);
        BC_ASSERT(sink.get_position() == count());
        return sink;
    }
};

class BCD_API table : public SLABMAP { public: using SLABMAP::arraymap; };

BC_POP_WARNING()

} // namespace output
} // namespace database
} // namespace libbitcoin

#endif
