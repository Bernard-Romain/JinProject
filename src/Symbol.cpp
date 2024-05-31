#include <assert.h>
#include <sstream>
#include <string_view> // string_view requires C++17 (either defined in CMakeLists.txt, or in Visual Studio, /Project properties -> Configuration properties->C / C++->Language->C++ Language standard / and select "ISO C++ 17 Standard"
#include "Circle.h"
#include "Group.h"
#include "Symbol.h"

using namespace std;

Symbol::Symbol(pugi::xml_node node, SymbolTable &symbols)
        : label{ node.attribute("label").as_string() }
{
    for (auto child : node.children())
    {
        assert((child.name() == "Circle"sv) || (child.name() == "Group"sv)); // "Circle"sv" equivalent to std::string_view{ "Circle" } thanks to : using namespace std::literals;
        if (child.name() == "Circle"sv)
            children.push_back(std::make_unique<Circle>(child));
        else // child.name() == "Group"sv
            children.push_back(std::make_unique<Group>(child, symbols));
    }
}

void Symbol::draw(SFML_output * out, double x_origin, double y_origin) const
{
    for (auto const &child : children)
    {
        child->draw(out, x_origin, y_origin);
    }
}

std::string Symbol::dump_with_no_initial_indent(std::string const& indent) const
{
    ostringstream oss;
    oss << "Symbol " << "\"" << label << "\", "
        << "children: [" << endl;
    for (auto const& c : children) {
        oss << c->dump(indent + "| ");
    }
    oss << indent << "]" << endl;
    return oss.str();
}

Shape * Symbol::find_label(std::string_view lab)
{
    for (auto const& c : children) {
        if (auto result = c->find_label(lab) ; result != nullptr)
            return result;
    }
    return nullptr;
}

void Symbol::set_color(std::string const& aColor) const
{
    for (auto &child : children)
    {
        child->set_color(aColor);
    }
}

