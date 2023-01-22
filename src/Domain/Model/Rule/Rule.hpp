#ifndef __RULE_H
#define __RULE_H

#include "../Cell/Cell.hpp"

class CellularAutomaton; // Forward declare to avoid circular dependency

class IRule {
public:
  virtual Cell::State apply(const Cell& c, const CellularAutomaton& aut) = 0;
  virtual bool enforce() = 0;
};
#endif
