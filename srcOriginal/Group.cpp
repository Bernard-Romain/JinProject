#include <cassert>
#include <string_view> // string_view requires C++17 (either defined in CMakeLists.txt, or in Visual Studio, /Project properties -> Configuration properties->C / C++->Language->C++ Language standard / and select "ISO C++ 17 Standard"
#include <sstream>
#include "Group.h"
#include "Circle.h"
#include "Instance_Symbol.h"

using namespace std;

Group::Group(const pugi::xml_node& node, std::map<std::string, std::shared_ptr<Symbol>, std::less<>> &symbols)
	: Shape{ node }
{
    for (auto child : node.children())
    {
        assert((child.name() == "Circle"sv) || (child.name() == "Group"sv) || (child.name() == "Instance_Symbol"sv)); // "Circle"sv" equivalent to std::string_view{ "Circle" } thanks to : using namespace std::literals;
        if (child.name() == "Circle"sv)
            children.push_back(std::make_unique<Circle>(child));
        else if (child.name() == "Group"sv)
            children.push_back(std::make_unique<Group>(child, symbols));
        else // (child.name() == "Instance_Symbol"sv)
            children.push_back(std::make_unique<Instance_Symbol>(child, symbols));

    }
}

Group::Group(std::string const& label, double x, double y)
        : Shape{ label, x, y }
{
}

std::unique_ptr<Shape> Group::clone()
{
    auto g = std::make_unique<Group>(get_label(), get_x(), get_y());
    for (auto const& child : children)
    {
        children.emplace_back(child->clone());
    }
    return std::move(g);
}

std::string Group::dump(std::string const& indent) const
{
	ostringstream oss;
	oss << indent
        << "Group " << Shape::dump(indent)
        << "children: [" << endl;
    for (auto const& c : children) {
        oss << c->dump(indent + "| ");
    }
    oss << indent << "]" << endl;
    return oss.str();
}

void Group::draw(SFML_output *out, double x_origin, double y_origin) const
{
        for (auto const &child : children)
        {
                child->draw(out, x_origin + get_x(), y_origin + get_y());
        }
}

Shape * Group::find_label(std::string_view lab)
{
    if (Shape::find_label(lab) != nullptr)
        return this;
    for (auto const& c : children) {
        if (auto result = c->find_label(lab) ; result != nullptr)
            return result;
    }
    return nullptr;
}

void Group::set_color(std::string const& aColor)
{
    for (auto &child : children)
    {
        child->set_color(aColor);
    }
}

