#pragma once 
#include <arrow/api.h>
#include <arrow/json/api.h>
#include <arrow/io/api.h>

inline std::shared_ptr<arrow::Table> jsonToArrowTable()
{
    using namespace arrow;
    arrow::Status st;
    arrow::MemoryPool* pool = default_memory_pool();

    auto input_file = arrow::io::ReadableFile::Open("G:/home/cplus/ubuntu/xml_to_arrow_table/resources/input.json").ValueOrDie();
    auto read_options = arrow::json::ReadOptions::Defaults();
    auto parse_options = arrow::json::ParseOptions::Defaults();

    // Instantiate TableReader from input stream and options
    std::shared_ptr<arrow::json::TableReader> reader;
    reader = arrow::json::TableReader::Make(pool, input_file, read_options,
                                        parse_options).ValueOrDie();
    // if (!st.ok()) {
    //     // Handle TableReader instantiation error...
    // }

    // Read table from JSON file
   return reader->Read().ValueOrDie();
}