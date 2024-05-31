#pragma once
#include <memory>
#include <vector>
#include "Shape.h"
#include "SymbolTable.h"

class Group :
    public Shape {
public:
    Group(const pugi::xml_node& node, SymbolTable &symbols);
    Group(std::string const& label, double x, double y);
    std::unique_ptr<Shape> clone() override;
    [[nodiscard]] std::string dump(std::string const& indent) const override;
    void draw(SFML_output *out, double x_origin, double y_origin) const override;
    Shape * find_label(std::string_view lab) override;
    void set_color(std::string const& aColor) override;
private:
    std::vector<std::unique_ptr<Shape>> children;
};
