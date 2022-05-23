/**

Complete C++ Project,

Load a XML file into arrow::Table

* Input:
<?xml version="1.0" encoding="UTF-8"?>
<bookstore>
  <book category="cooking">
    <title lang="en">Everyday Italian</title>
    <author>Giada De Laurentiis</author>
    <editions>
      <edition>
        <isbn>a12d27ae-c539-11ec-9d64-0242ac120002</isbn>
        <year>2005</year>
        <price>30.00</price>
      </edition>
      <edition>
        <isbn>b8b1824e-c539-11ec-9d64-0242ac120002</isbn>
        <year>2018</year>
        <price>29.00</price>
      </edition>
    </editions>
  </book>
  <book category="children">
    <title lang="en">Harry Potter</title>
    <author>J K. Rowling</author>
    <editions>
      <edition>
        <year>2005</year>
        <price>29.99</price>
      </edition>
    </editions>
  </book>
  <book category="web">
    <title lang="en">Learning XML</title>
    <author>Erik T. Ray</author>
    <editions>
      <edition>
        <year>2003</year>
        <price>39.95</price>
      </edition>
    </editions>
  </book>
</bookstore>

* Output: an arrow::Table object

Requirements:
* Without information loss (except the xml header line)
* With stable/modern C++ standard
* Build script

Plus point:
* Document/Improvement Notes
* Unit-Test
* Linter

References:
* arrow::Table: https://arrow.apache.org/docs/cpp/api/table.html#_CPPv4N5arrow5TableE
* Dependencies: https://github.com/apache/arrow/tree/master/cpp
* Input XML (with modification): https://www.w3schools.com/xml/xml_tree.asp

*/