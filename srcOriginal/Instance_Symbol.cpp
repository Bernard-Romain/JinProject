#include <sstream>
#include "Symbol.h"
#include "Instance_Symbol.h"

using namespace std;

Instance_Symbol::Instance_Symbol(const pugi::xml_node& node, SymbolTable &symbols)
: Shape{ node }
, symbol{ symbols[ node.attribute("label_symbol").as_string() ]}
{
}

Instance_Symbol::Instance_Symbol(std::string const& label, double x, double y, std::shared_ptr<Symbol> symbol)
	: Shape{ label, x, y }
	, symbol{ std::move(symbol) }
{
}

std::unique_ptr<Shape> Instance_Symbol::clone()
{
    return std::make_unique<Instance_Symbol>(get_label(), get_x(), get_y(), symbol);
}

std::string Instance_Symbol::dump(std::string const& indent) const
{
    ostringstream oss;
    oss << indent
        << "Instance_Symbol " << Shape::dump(indent)
        << symbol->dump_with_no_initial_indent(indent);
    return oss.str();

}

void Instance_Symbol::draw(SFML_output *out, double x_origin, double y_origin) const
{
    symbol->draw(out, x_origin + get_x(), y_origin + get_y() );
}

void Instance_Symbol::set_color(std::string const& aColor)
{
    symbol->set_color(aColor);
}
