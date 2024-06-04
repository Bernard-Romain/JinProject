#include <cassert>
#include <string_view> // string_view requires C++17 (either defined in CMakeLists.txt, or in Visual Studio, /Project properties -> Configuration properties->C / C++->Language->C++ Language standard / and select "ISO C++ 17 Standard"
#include <sstream>
#include "Drawing.h"
#include "Group.h"
#include "Circle.h"
#include "Instance_Symbol.h"
#include "Symbol.h"

using namespace std;

Drawing::Drawing(pugi::xml_node node)
{
    for (auto child : node.children())
    {
        assert((child.name() == "Circle"sv) || (child.name() == "Group"sv) || (child.name() == "Instance_Symbol"sv) || (child.name() == "Symbol"sv)); // "Circle"sv" equivalent to std::string_view{ "Circle" } thanks to : using namespace std::literals;
        if (child.name() == "Circle"sv)
            children.push_back(std::make_unique<Circle>(child));
        else if (child.name() == "Group"sv)
            children.push_back(std::make_unique<Group>(child, symbols));
        else if (child.name() == "Instance_Symbol"sv)
            children.push_back(std::make_unique<Instance_Symbol>(child, symbols));
        else //  (child.name() == "Symbol"sv)
            symbols[ child.attribute("label").as_string() ] = make_shared<Symbol>(child, symbols);
    }
}

void Drawing::add(std::unique_ptr<Shape> shape)
{
    children.push_back(std::move(shape));
}

void Drawing::draw(SFML_output *out) const
{
    for (auto const& c : children) {
        c->draw(out, 0, 0);
    }
}

std::string Drawing::dump(std::string const& indent) const
{
    ostringstream oss;
    oss << indent << "Drawing [" << endl;
    for (auto const& [label, symbol] : symbols) {
        oss << "| " << symbol->dump_with_no_initial_indent("| ");
    }
    for (auto const& c : children) {
        oss << c->dump(indent + "| ");
    }
    oss << indent << "]" << endl;
    return oss.str();
}

Shape * Drawing::find_label(string_view lab) const
{
    for (auto const& [key, value] : symbols) {
        if (auto result = value->find_label(lab) ; result != nullptr)
            return result;
    }
    for (auto const& c : children) {
        if (auto result = c->find_label(lab) ; result != nullptr)
            return result;
    }
    return nullptr;
}
