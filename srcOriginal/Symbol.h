#pragma once
#include <map>
#include <memory>
#include <string>
#include "pugixml.hpp"
#include "Group.h"
#include "SymbolTable.h"

class Symbol
{
public:
	Symbol(pugi::xml_node node, SymbolTable &symbols);
	void draw(SFML_output *out, double x_origin, double y_origin) const;
    [[nodiscard]] std::string dump_with_no_initial_indent(std::string const& indent) const;
    Shape * find_label(std::string_view lab);
    void set_color(std::string const& aColor) const;

private:
	std::string label;
    std::vector<std::unique_ptr<Shape>> children;
};

