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
#include "test.hpp"
#include <bitcoin/database.hpp>

BOOST_AUTO_TEST_SUITE(error_tests)

// error_t
// These test std::error_code equality operator overrides.

// memory map

BOOST_AUTO_TEST_CASE(error_t__code__success__false_exected_message)
{
    constexpr auto value = error::success;
    const auto ec = code(value);
    BOOST_REQUIRE(!ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "success");
}

BOOST_AUTO_TEST_CASE(error_t__code__unknown__true_exected_message)
{
    constexpr auto value = error::unknown;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "unknown error");
}

BOOST_AUTO_TEST_CASE(error_t__code__open_open__true_exected_message)
{
    constexpr auto value = error::open_open;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "opening open file");
}

BOOST_AUTO_TEST_CASE(error_t__code__open_failure__true_exected_message)
{
    constexpr auto value = error::open_failure;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file failed to open");
}

BOOST_AUTO_TEST_CASE(error_t__code__close_loaded__true_exected_message)
{
    constexpr auto value = error::close_loaded;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "closing loaded file");
}

BOOST_AUTO_TEST_CASE(error_t__code__close_failure__true_exected_message)
{
    constexpr auto value = error::close_failure;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file failed to close");
}

BOOST_AUTO_TEST_CASE(error_t__code__load_locked__true_exected_message)
{
    constexpr auto value = error::load_locked;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "loading locked file");
}

BOOST_AUTO_TEST_CASE(error_t__code__load_loaded__true_exected_message)
{
    constexpr auto value = error::load_loaded;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "loading loaded file");
}

BOOST_AUTO_TEST_CASE(error_t__code__load_failure__true_exected_message)
{
    constexpr auto value = error::load_failure;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file failed to load");
}

BOOST_AUTO_TEST_CASE(error_t__code__flush_unloaded__true_exected_message)
{
    constexpr auto value = error::flush_unloaded;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "flushing unloaded file");
}

BOOST_AUTO_TEST_CASE(error_t__code__flush_failure__true_exected_message)
{
    constexpr auto value = error::flush_failure;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file failed to flush");
}

BOOST_AUTO_TEST_CASE(error_t__code__unload_locked__true_exected_message)
{
    constexpr auto value = error::unload_locked;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "unloading unloaded file");
}

BOOST_AUTO_TEST_CASE(error_t__code__unload_failure__true_exected_message)
{
    constexpr auto value = error::unload_failure;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file failed to unload");
}

// store

BOOST_AUTO_TEST_CASE(error_t__code__transactor_lock__true_exected_message)
{
    constexpr auto value = error::transactor_lock;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "transactor lock failure");
}

BOOST_AUTO_TEST_CASE(error_t__code__process_lock__true_exected_message)
{
    constexpr auto value = error::process_lock;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "process lock failure");
}

BOOST_AUTO_TEST_CASE(error_t__code__flush_lock__true_exected_message)
{
    constexpr auto value = error::flush_lock;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "flush lock failure");
}

BOOST_AUTO_TEST_CASE(error_t__code__flush_unlock__true_exected_message)
{
    constexpr auto value = error::flush_unlock;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "flush unlock failure");
}

BOOST_AUTO_TEST_CASE(error_t__code__process_unlock__true_exected_message)
{
    constexpr auto value = error::process_unlock;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "process unlock failure");
}

BOOST_AUTO_TEST_CASE(error_t__code__clear_directory__true_exected_message)
{
    constexpr auto value = error::clear_directory;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "clear directory failure");
}

BOOST_AUTO_TEST_CASE(error_t__code__rename_directory__true_exected_message)
{
    constexpr auto value = error::rename_directory;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "rename directory failure");
}

BOOST_AUTO_TEST_CASE(error_t__code__missing_backup__true_exected_message)
{
    constexpr auto value = error::missing_backup;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "missing backup");
}

BOOST_AUTO_TEST_CASE(error_t__code__create_file__true_exected_message)
{
    constexpr auto value = error::create_file;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file failed to create");
}

BOOST_AUTO_TEST_CASE(error_t__code__unloaded_file__true_exected_message)
{
    constexpr auto value = error::unloaded_file;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file not loaded");
}

BOOST_AUTO_TEST_CASE(error_t__code__dump_file__true_exected_message)
{
    constexpr auto value = error::dump_file;
    const auto ec = code(value);
    BOOST_REQUIRE(ec);
    BOOST_REQUIRE(ec == value);
    BOOST_REQUIRE_EQUAL(ec.message(), "file failed to dump");
}

BOOST_AUTO_TEST_SUITE_END()
