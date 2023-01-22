#ifndef __LAMBDA_BASED_RULE_H
#define __LAMBDA_BASED_RULE_H

#include <functional>
#include "Rule.hpp"
#include "../Cell/Cell.hpp"
#include "../CellularAutomaton/CellularAutomaton.hpp"

class LambdaBasedRule: public IRule
{
protected:
  std::function<Cell::State(const Cell&, const CellularAutomaton&)> application;
  std::function<bool()> forceRule;

public:
  LambdaBasedRule(std::function<Cell::State(const Cell&, const CellularAutomaton&)> apply): LambdaBasedRule{apply, []() { return false; }} {}
  LambdaBasedRule(
    std::function<Cell::State(const Cell&, const CellularAutomaton&)> apply,
    std::function<bool()> force
  ): application(apply), forceRule(force) {}

  Cell::State apply(const Cell& c, const CellularAutomaton& aut) override {
    return application(c, aut);
  }

  bool enforce() override {
    return forceRule();
  }
};

#endif
