///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2021 libbitcoin-database developers (see COPYING).
//
//        GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
//
///////////////////////////////////////////////////////////////////////////////
#ifndef LIBBITCOIN_DATABASE_HPP
#define LIBBITCOIN_DATABASE_HPP

/**
 * API Users: Include only this header. Direct use of other headers is fragile
 * and unsupported as header organization is subject to change.
 *
 * Maintainers: Do not include this header internal to this library.
 */

#include <bitcoin/system.hpp>
#include <bitcoin/database/boost.hpp>
#include <bitcoin/database/define.hpp>
#include <bitcoin/database/settings.hpp>
#include <bitcoin/database/version.hpp>
#include <bitcoin/database/locks/conditional_lock.hpp>
#include <bitcoin/database/locks/file_lock.hpp>
#include <bitcoin/database/locks/flush_lock.hpp>
#include <bitcoin/database/locks/interprocess_lock.hpp>
#include <bitcoin/database/locks/locks.hpp>
#include <bitcoin/database/locks/scope_lock.hpp>
#include <bitcoin/database/locks/sequential_lock.hpp>
#include <bitcoin/database/memory/accessor.hpp>
#include <bitcoin/database/memory/file.hpp>
#include <bitcoin/database/memory/map.hpp>
#include <bitcoin/database/memory/map_sink.hpp>
#include <bitcoin/database/memory/map_source.hpp>
#include <bitcoin/database/memory/interfaces/memory.hpp>
#include <bitcoin/database/memory/interfaces/storage.hpp>
#include <bitcoin/database/primitives/element.hpp>
#include <bitcoin/database/primitives/linkage.hpp>
#include <bitcoin/database/primitives/manager.hpp>
#include <bitcoin/database/tables/hash_table.hpp>
#include <bitcoin/database/tables/hash_table_header.hpp>

#endif
