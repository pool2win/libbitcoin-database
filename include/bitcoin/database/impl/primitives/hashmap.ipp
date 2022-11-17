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
#ifndef LIBBITCOIN_DATABASE_PRIMITIVES_HASHMAP_IPP
#define LIBBITCOIN_DATABASE_PRIMITIVES_HASHMAP_IPP

#include <bitcoin/system.hpp>
#include <bitcoin/database/define.hpp>

namespace libbitcoin {
namespace database {

TEMPLATE
CLASS::hashmap(storage& header, storage& body, const Link& buckets) NOEXCEPT
  : header_(header, buckets), manager_(body)
{
}

// not thread safe
// ----------------------------------------------------------------------------

TEMPLATE
bool CLASS::create() NOEXCEPT
{
    return header_.create() && verify();
}

TEMPLATE
bool CLASS::verify() const NOEXCEPT
{
    Link count{};
    return header_.verify() && header_.get_body_count(count) &&
        count == manager_.count();
}

TEMPLATE
bool CLASS::snap() NOEXCEPT
{
    return header_.set_body_count(manager_.count());
}

// query interface
// ----------------------------------------------------------------------------

TEMPLATE
bool CLASS::exists(const Key& key) const NOEXCEPT
{
    return !it(key).self().is_terminal();
}

TEMPLATE
typename CLASS::iterator CLASS::it(const Key& key) const NOEXCEPT
{
    return { manager_.get(), header_.top(key), key };
}

TEMPLATE
Link CLASS::allocate(const Link& size) NOEXCEPT
{
    return manager_.allocate(size);
}

TEMPLATE
bool CLASS::commit(const Key& key, const Link& link) NOEXCEPT
{
    const auto ptr = manager_.get(link);
    if (!ptr)
        return false;

    // Set element search key.
    system::unsafe_array_cast<uint8_t, array_count<Key>>(std::next(
        ptr->begin(), Link::size)) = key;

    // Commit element to search index.
    auto& next = system::unsafe_array_cast<uint8_t, Link::size>(ptr->begin());
    return header_.push(link, next, header_.index(key));
}

TEMPLATE
template <typename Element, if_equal<Element::size, Size>>
bool CLASS::get(const Key& key, Element& element) const NOEXCEPT
{
    return get(it(key).self(), element);
}

TEMPLATE
template <typename Element, if_equal<Element::size, Size>>
bool CLASS::get(const Link& link, Element& element) const NOEXCEPT
{
    auto source = streamer<reader>(link);
    return source && element.from_data(*source);
}

TEMPLATE
template <typename Element, if_equal<Element::size, Size>>
bool CLASS::set(const Link& link, const Element& element) NOEXCEPT
{
    auto sink = streamer<writer>(link);
    return sink && element.to_data(*sink);
}

TEMPLATE
template <typename Element, if_equal<Element::size, Size>>
bool CLASS::put(const Key& key, const Element& element) NOEXCEPT
{
    auto sink = creater(key, element.count());
    return sink && element.to_data(*sink) && sink->finalize();
}

////TEMPLATE
////template <typename Element, if_equal<Element::size, Size>>
////bool CLASS::put(const Key& key, const Element& element,
////    const Link& allocation) NOEXCEPT
////{
////    auto sink = putter(key, element.count(), allocation);
////    return sink && element.to_data(*sink) && sink->finalize();
////}

// protected
// ----------------------------------------------------------------------------

TEMPLATE
template <typename Streamer>
typename Streamer::ptr CLASS::streamer(const Link& link) const NOEXCEPT
{
    const auto ptr = manager_.get(link);
    if (!ptr)
        return {};

    const auto stream = std::make_shared<Streamer>(ptr);
    stream->skip_bytes(Link::size + array_count<Key>);

    // Limits to single record or eof for slab (caller can remove limit).
    if constexpr (!is_slab) { stream->set_limit(Size); }
    return stream;
}

TEMPLATE
reader_ptr CLASS::getter(const Key& key) const NOEXCEPT
{
    return streamer<reader>(it(key).self());
}

TEMPLATE
finalizer_ptr CLASS::creater(const Key& key, const Link& size) NOEXCEPT
{
    return committer(key, manager_.allocate(size));
}

TEMPLATE
finalizer_ptr CLASS::committer(const Key& key, const Link& link) NOEXCEPT
{
    const auto ptr = manager_.get(link);
    if (!ptr)
        return {};

    const auto sink = std::make_shared<finalizer>(ptr);
    sink->skip_bytes(Link::size);
    sink->write_bytes(key);

    const auto index = header_.index(key);
    sink->set_finalizer([this, link, index, ptr]() NOEXCEPT
    {
        auto& next = system::unsafe_array_cast<uint8_t, Link::size>(ptr->begin());
        return header_.push(link, next, index);
    });

    // Limits to single record or eof for slab (caller can remove limit).
    if constexpr (!is_slab) { sink->set_limit(Size); }
    return sink;
}

} // namespace database
} // namespace libbitcoin

#endif
