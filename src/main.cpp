#include <iostream>
#include <memory>
#include "Domain/Model/Cell/Cell.hpp"
#include "Domain/Model/CellularAutomaton/CellularAutomaton.hpp"
#include "Domain/Model/CellularAutomatonPrinter/CellularAutomatonPrinter.hpp"
#include "Domain/Model/Rule/Rule.hpp"
#include "Domain/Model/Rule/LambdaBasedRule.hpp"

int main() {
  CellularAutomaton c;
  CellularAutomatonPrinter cp{c};

  std::cout << cp;

  LambdaBasedRule killEverything{
      [](const Cell& c, const CellularAutomaton& aut) {
          return Cell::State::DEAD;
      },
      []() { return true; }
  };

  bool force = false;
  Cell::State forcedState = Cell::State::ALIVE;

  LambdaBasedRule forceEveryThingToLiveAfter10Generations{
      [&forcedState, &force](const Cell& c, const CellularAutomaton& aut) {
          if (aut.getIteration() >= 10) {
              force = true;
          }
          return forcedState;
      },
      [&force]() {
          return force;
      }
  };

  c
    .addRule(std::make_shared<LambdaBasedRule>(forceEveryThingToLiveAfter10Generations))
    .addRule(std::make_shared<LambdaBasedRule>(killEverything));

  while (true) {
    c.update();
    std::cout << cp << std::flush;
  }

  return 0;
}
