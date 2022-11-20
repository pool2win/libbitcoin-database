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
#include "../../test.hpp"
#include "../../storage.hpp"

BOOST_AUTO_TEST_SUITE(puts_tests)

using namespace database::puts;

#define DECLARE(instance_, file_) \
data_chunk file_; \
test::storage store{ file_ }; \
array_map<record> instance_{ store }

const record expected0{};
const record expected1
{
    std_vector<uint64_t>
    {
        0x0000007856341211_u64
    }
};
const record expected2
{
    std_vector<uint64_t>
    {
        0x0000007856341221_u64,
        0x0000007856341222_u64
    }
};
const record expected3
{
    std_vector<uint64_t>
    {
        0x0000007856341231_u64,
        0x0000007856341232_u64,
        0x0000007856341233_u64
    }
};
const data_chunk expected_file
{
    // record0 (empty set)

    // --------------------------------------------------------------------------------------------

    // record1
    0x11, 0x12, 0x34, 0x56, 0x78,

    // --------------------------------------------------------------------------------------------

    // record2
    0x21, 0x12, 0x34, 0x56, 0x78,
    0x22, 0x12, 0x34, 0x56, 0x78,

    // --------------------------------------------------------------------------------------------

    // record3
    0x31, 0x12, 0x34, 0x56, 0x78,
    0x32, 0x12, 0x34, 0x56, 0x78,
    0x33, 0x12, 0x34, 0x56, 0x78
};

BOOST_AUTO_TEST_CASE(puts__put__get__expected)
{
    DECLARE(instance, file);
    BOOST_REQUIRE(instance.put(expected0));
    BOOST_REQUIRE(instance.put(expected1));
    BOOST_REQUIRE(instance.put(expected2));
    BOOST_REQUIRE(instance.put(expected3));
    BOOST_REQUIRE_EQUAL(file, expected_file);

    record record0{};
    BOOST_REQUIRE(instance.get(0, record0));
    BOOST_REQUIRE(record0 == expected0);

    record record1{};
    record1.put_fks.resize(1);
    BOOST_REQUIRE(instance.get(0, record1));
    BOOST_REQUIRE(record1.put_fks == expected1.put_fks);

    record record2{};
    record2.put_fks.resize(2);
    BOOST_REQUIRE(instance.get(1, record2));
    BOOST_REQUIRE(record2.put_fks == expected2.put_fks);

    record record3{};
    record3.put_fks.resize(3);
    BOOST_REQUIRE(instance.get(3, record3));
    BOOST_REQUIRE(record3.put_fks == expected3.put_fks);
}

BOOST_AUTO_TEST_SUITE_END()
