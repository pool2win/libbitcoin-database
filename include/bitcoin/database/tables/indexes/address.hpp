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
#ifndef LIBBITCOIN_DATABASE_TABLES_INDEXES_ADDRESS_HPP
#define LIBBITCOIN_DATABASE_TABLES_INDEXES_ADDRESS_HPP

#include <bitcoin/system.hpp>
#include <bitcoin/database/define.hpp>
#include <bitcoin/database/primitives/primitives.hpp>
#include <bitcoin/database/tables/schema.hpp>

namespace libbitcoin {
namespace database {
namespace table {

/// address is a record hashmap of output fk records.
struct address
  : public hash_map<schema::height>
{
    using put = linkage<schema::put>;
    using search_key = search<schema::hash>;
    using hash_map<schema::height>::hashmap;

    struct record
      : public schema::address
    {
        inline bool from_data(reader& source) NOEXCEPT
        {
            output_fk = source.read_little_endian<put::integer, put::size>();
            return source;
        }

        inline bool to_data(writer& sink) const NOEXCEPT
        {
            sink.write_little_endian<put::integer, put::size>(output_fk);
            return sink;
        }

        inline bool operator==(const record& other) const NOEXCEPT
        {
            return output_fk == other.output_fk;
        }

        put::integer output_fk{};
    };

    struct record_with_sk
      : public record
    {
        BC_PUSH_WARNING(NO_METHOD_HIDING)
        inline bool from_data(reader& source) NOEXCEPT
        BC_POP_WARNING()
        {
            source.rewind_bytes(sk);
            key = source.read_hash();
            return record::from_data(source);
        }

        search_key key{};
    };

    struct record_sk
      : public schema::address
    {
        inline bool from_data(reader& source) NOEXCEPT
        {
            source.rewind_bytes(sk);
            key = source.read_hash();
            return source;
        }

        search_key key{};
    };
};

} // namespace table
} // namespace database
} // namespace libbitcoin

#endif
