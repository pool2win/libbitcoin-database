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
#include <bitcoin/database/store/query_impl.hpp>

#include <bitcoin/database/define.hpp>
#include <bitcoin/database/store/query.hpp>
#include <bitcoin/database/store/store.hpp>

namespace libbitcoin {
namespace database {

query_implementation::query_implementation(store& store) NOEXCEPT
  : store_(store)
{
}

query_implementation::~query_implementation() NOEXCEPT
{
}

query::foo query_implementation::get_foo() const NOEXCEPT
{
	return {};
}

} // namespace database
} // namespace libbitcoin
