#ifndef __LAMBDA_BASED_RULE_H
#define __LAMBDA_BASED_RULE_H

#include <functional>
#include "Rule.hpp"
#include "../Cell/Cell.hpp"
#include "../CellularAutomaton/CellularAutomaton.hpp"

typedef std::function<Cell::State(const Cell&, const CellularAutomaton&)> LambdaRuleFunction;
typedef std::function<bool()> LambdaForceRuleFunction;

class LambdaBasedRule: public IRule
{
protected:
  std::function<Cell::State(const Cell&, const CellularAutomaton&)> application;
  std::function<bool()> forceRule;

public:
  LambdaBasedRule(LambdaRuleFunction apply): LambdaBasedRule{apply, []() { return false; }} {}
  LambdaBasedRule(
    LambdaRuleFunction apply,
    LambdaForceRuleFunction force
  ): application(apply), forceRule(force) {}

  Cell::State apply(const Cell& c, const CellularAutomaton& aut) override {
    return application(c, aut);
  }

  bool enforce() override {
    return forceRule();
  }
};

#endif
