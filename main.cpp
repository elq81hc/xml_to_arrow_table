#include <tinyxml2.h>
#include <arrow/api.h>

#include <iostream>
#include <stack>

#include "utils/logging.h"
#include "sampleTable.h"
#include "json.h"

using namespace logging;
using namespace tinyxml2;
using namespace std;

const std::string xmlIn = R"(
<?xml version="1.0" encoding="UTF-8"?>
<bookstore>
  <book category="cooking">
    <title lang="en">Everyday Italian</title>
    <author>Giada De Laurentiis</author>
    <year>2005</year>
    <price>30.00</price>
  </book>
  <book category="children">
    <title lang="en">Harry Potter</title>
    <author>J K. Rowling</author>
    <year>2005</year>
    <price>29.99</price>
  </book>
  <book category="web">
    <title lang="en">Learning XML</title>
    <author>Erik T. Ray</author>
    <year>2003</year>
    <price>39.95</price>
  </book>
</bookstore>
)";
void processElement(XMLElement* &element)
{
    // get the attribute
    logInfo("Element: " + string(element->Value()));
    if (auto it = element->FirstAttribute()) {
        logInfo("Attribute: ");
        while (it)
        {
            logInfo("    name:" + string(it->Name()) + ", value: " + string(it->Value()));
            it = it->Next();
        }
    }
    // get the text data
    if (auto rawPtr = element->GetText())
        logInfo("Text: " + string(rawPtr));
}
int xml2ArrowTable()
{
    // get memory data
    XMLDocument doc;
    if (doc.Parse(xmlIn.c_str()) != XML_SUCCESS) {
        logErr("can not parse the xml input string");
        return -1;
    }

    // std::vector<std::shared_ptr<arrow::Array>> arrays;
    // // create a table we need: 
    // // ArrayVector = std::vector<std::shared_ptr<arrow::Array>>
    // // ChunkedArrayVector = std::vector<std::shared_ptr<ChunkedArray>>
    // // to have ChunkedArrayVector we need ArrayVector
    // auto chunks = arrow::ChunkedArray::Make(arrays);
    // auto table = arrow::Table::FromChunkedStructArray(*chunks);
    // arrow::Table::Make()

    // root element i.g: bookstore
    auto root = doc.RootElement();
    logInfo("Root: " + string(root->Value()));

    // preorder-traverse: N L R
    // process node: attribute, text, child elements
    stack<XMLElement*> q;
    for(auto it = root->LastChildElement();
        it != nullptr; 
        it = it->PreviousSiblingElement())
    {
        q.push(it);
    }
    while (!q.empty())
    {
        auto curElement = q.top();
        q.pop();

        // process node
        processElement(curElement);
        // .....

        // iterator from first to last child node
        for(auto it = curElement->LastChildElement();
            it != nullptr;
            it = it->PreviousSiblingElement())
        {
            q.push(it);
        }
    }
    
    return 0;
}

int main()
{
    // xml2ArrowTable();
    // std::cout << jsonToArrowTable()->ToString();
    std::cout << customTable()->ToString();
    return 0;
}