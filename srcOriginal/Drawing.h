#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "Shape.h"
#include "SymbolTable.h"

class Drawing
{
public:
    explicit Drawing(pugi::xml_node node);
    void add(std::unique_ptr<Shape> shape);
    [[nodiscard]] std::string dump(std::string const& indent) const;
    void draw(SFML_output *out) const;
    Shape * find_label(std::string_view lab) const;
private:
    std::vector<std::unique_ptr<Shape>> children;
    SymbolTable symbols;
};

