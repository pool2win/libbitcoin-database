#include <iostream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/database.hpp>

using namespace bc;
using namespace bc::database;

template <size_t N>
record_byte_pointer get0(htdb_record_header& header, record_manager& alloc,
    const data_chunk& key_data)
{
    typedef byte_array<N> hash_type;
    htdb_record<hash_type> ht(header, alloc, "test");
    hash_type key;
    BITCOIN_ASSERT(key.size() == key_data.size());
    std::copy(key_data.begin(), key_data.end(), key.begin());
    return ht.get(key);
}

int main(int argc, char** argv)
{
    if (argc != 4 && argc != 5)
    {
        std::cerr
            << "Usage: read_htdb_record_value FILENAME KEY VALUE_SIZE [OFFSET]"
            << std::endl;
        return 0;
    }
    const std::string filename = argv[1];

    data_chunk key_data;
    if (!decode_base16(key_data, argv[2]))
    {
        std::cerr << "key data is not valid" << std::endl;
        return -1;
    }

    const size_t value_size = boost::lexical_cast<size_t>(argv[3]);
    file_offset offset = 0;
    if (argc == 5)
        offset = boost::lexical_cast<file_offset>(argv[4]);

    mmfile file(filename);
    BITCOIN_ASSERT(file.data());

    htdb_record_header header(file, offset);
    header.start();

    const size_t record_size = key_data.size() + 4 + value_size;
    record_manager alloc(file, offset + 4 + 4 * header.size(), record_size);
    alloc.start();

    record_byte_pointer record = nullptr;
    if (key_data.size() == 32)
    {
        record = get0<32>(header, alloc, key_data);
    }
    else if (key_data.size() == 4)
    {
        record = get0<4>(header, alloc, key_data);
    }
    else
    {
        std::cerr << "read_htdb_record_value: unsupported key size."
            << std::endl;
        return -1;
    }
    if (!record)
    {
        std::cerr << "read_htdb_record_value: no record found" << std::endl;
        return -2;
    }
    data_chunk data(record, record + value_size);
    std::cout << encode_base16(data) << std::endl;
    return 0;
}

