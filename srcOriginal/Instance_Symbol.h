#pragma once
#include <string>
#include <memory>
#include  "pugixml.hpp"
#include "Shape.h"
#include "SymbolTable.h"
class Instance_Symbol :
	public Shape {
public:
    Instance_Symbol(const pugi::xml_node& node, SymbolTable &symbols);
    Instance_Symbol (std::string const& label, double x, double y, std::shared_ptr<Symbol> symbol);
    std::unique_ptr<Shape> clone() override;
    [[nodiscard]] std::string dump(std::string const& indent) const override;
    void draw(SFML_output *out, double x_origin, double y_origin) const override;
    void set_color(std::string const& aColor) override;
private:
    std::shared_ptr<Symbol> symbol;

};
