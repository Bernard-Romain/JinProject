#pragma once
#include <map>
#include <string>
#include <memory>

class Symbol;
using SymbolTable = std::map<std::string, std::shared_ptr<Symbol>, std::less<>>;


