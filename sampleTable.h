#pragma once 

std::shared_ptr<arrow::Table> createSimpleArrowTable()
{
    using namespace arrow;
    /// @brief require: nested type, string
    
    // create string builder
    arrow::StringBuilder strbuilder;
    strbuilder.Append("Everyday Italian");
    std::shared_ptr<arrow::Array> strarray;
    strbuilder.Finish(&strarray);

    // create nested type: 
    // { "book", { 
    //   { "title", "Everyday Italian" },
    //   { "author", "Giada De Laurentiis" } }
    // }
    // auto title = arrow::field("title", arrow::utf8());
    // auto author = arrow::field("author", arrow::utf8());
    // auto book = arrow::struct_({title, author});

    auto map_type = MapType::Make(field("some_entries",
                                           struct_({field("some_key", utf8(), false),
                                                    field("some_value", utf8())}),
                                           false)).ValueOrDie();

    auto key_builder = std::make_shared<StringBuilder>();
    auto item_builder = std::make_shared<StringBuilder>();
    MapBuilder map_builder(default_memory_pool(), key_builder, item_builder, map_type);
    std::shared_ptr<Array> actual;
    map_builder.Append();
    key_builder->AppendValues({"title", "author"});
    item_builder->AppendValues({"Everyday Italian", "Giada De Laurentiis"});
    map_builder.AppendNull();
    map_builder.Finish(&actual);

    if (!actual->ValidateFull().ok()) {
        // logErr("MapBuilder create failure");
        return nullptr;
    }

    // create schema
    auto schema = arrow::schema({
        arrow::field("str", arrow::utf8()),
        arrow::field("book", map_builder.type())
    });

    return arrow::Table::Make(schema, {strarray, actual});
}

std::shared_ptr<arrow::Table> customTable()
{
    std::vector<std::shared_ptr<arrow::Array>> arrays;
    {
        std::shared_ptr<arrow::Array> arr;

        // struct_: key=node->name, type=string
        auto type = arrow::struct_({arrow::field("rootElement", arrow::list(arrow::struct_({})))});

        arrow::StructBuilder builder(type, arrow::default_memory_pool(), {});
        builder.Finish(&arr);
        arrays.emplace_back(std::move(arr));
    }
    // create a table we need: 
    // ArrayVector = std::vector<std::shared_ptr<arrow::Array>>
    // ChunkedArrayVector = std::vector<std::shared_ptr<ChunkedArray>>
    // to have ChunkedArrayVector we need ArrayVector
    auto chunks = arrow::ChunkedArray::Make(arrays);
    auto table = arrow::Table::FromChunkedStructArray(*chunks);
    // arrow::Table::Make()
    return *table;
} 